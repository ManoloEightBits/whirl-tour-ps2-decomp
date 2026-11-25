#!/usr/bin/env python3
"""Compile m2c's draft of every unmatched function with the game's compiler and rank how close it gets.

Usage:
  m2c_sweep.py run    [--region game|physics|runtime|all] [--range A B] [--max-size N] [-j N] [--redo]
  m2c_sweep.py report [--region ...] [--range A B] [--max-size N] [--status S] [--top N]
  m2c_sweep.py show ADDR

`run` is meant to be left alone for a while (the whole binary takes tens of minutes). For each
unmatched function it runs m2c (`--valid-syntax`, target mipsee-gcc-c) in a subprocess, writes the
draft to <out>/drafts/<ADDR>.c, compiles it with the game's cc1 at verify.py's flags (inside the same
network sandbox), and compares the result with the game. One line per function goes to
<out>/results.tsv as soon as it is done, so the run can be stopped and resumed: functions already in
the file are skipped unless --redo. <out> defaults to ../whirl-tour-work/sweep (WHIRL_SWEEP), outside
the repository, because the drafts are derived from the game.

Status of a function:
  match      the raw draft compiles to the game's bytes (relocated fields masked unless resolvable)
  regs       same length and the same mnemonics: only registers, immediates or offsets differ
  diff       compiles; the score is the mnemonic similarity (difflib ratio, 0..1) to the game
  asm        m2c met instructions it cannot express (VU0 macro mode, MMI, COP2): needs inline asm
  m2c-error  m2c failed or left an error marker (often a switch whose jump table it was not given)
  cc-error   the draft does not compile as C (first error line kept)

`report` reads the results, drops functions that have matched since (build/matched.txt), and prints
the counts per status and the best candidates (match, then regs by size, then diff by score).
`show ADDR` prints one function's result line and its draft.

The draft is C with m2c's macros, not code for the repository: names, types and the C++ form still
come from evidence and from diff_func.py. A good score says the control flow and operations are
right, so the function is a cheap target.
"""
import argparse
import collections
import difflib
import os
import re
import struct
import subprocess
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import rabbitizer

from whirl_paths import REPO, WORK, COMPILERS  # noqa: E402,F401
import whirl_paths  # noqa: E402
import extract_rtti as e  # noqa: E402
import inspect_tu as itu  # noqa: E402
import verify  # noqa: E402

OUT = Path(os.environ.get('WHIRL_SWEEP', WORK / 'sweep'))
TMP = verify.BUILD / 'sweep'
REGIONS = {'game': (0x00100000, 0x001C62D0), 'physics': (0x001C62D0, 0x00228F30),
           'runtime': (0x00228F30, e.TEXT_BASE + e.TEXT_SIZE)}
COLUMNS = ['addr', 'size', 'status', 'score', 'ndiff', 'ours', 'game', 'name', 'note']
STATUS_ORDER = ['match', 'regs', 'diff', 'cc-error', 'm2c-error', 'asm']
M2C_TIMEOUT = 120

# Our own minimal versions of the macros m2c's --valid-syntax output uses.
PRELUDE = r'''typedef signed char s8; typedef unsigned char u8; typedef short s16; typedef unsigned short u16;
typedef int s32; typedef unsigned int u32; typedef long long s64; typedef unsigned long long u64;
typedef float f32; typedef double f64;
#define M2C_UNK int
#define M2C_FIELD(expr, type, offset) (*(type)((char *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_STRUCT_COPY(dst, src, size) __builtin_memcpy((dst), (src), (size))
#define M2C_ERROR(x) 0
#define NULL ((void *)0)
#define M2C_BREAK(x) ((void)0)
#define M2C_TRAP_IF(x) ((void)0)
'''
# GCC emits the division-by-zero "break 7" itself, so M2C_BREAK/M2C_TRAP_IF compile to nothing.
UNSUPPORTED = re.compile(r'\bM2C_(?!UNK\b|FIELD\b|BITWISE\b|STRUCT_COPY\b|ERROR\b|BREAK\b|TRAP_IF\b)\w+')
VOID_PTR = re.compile(r'\bvoid \*')
# m2c's own copy of the check GCC already emits around a div: drop it so the draft does not get two.
DIV_CHECK = re.compile(r'\n\s*if \(\w+ == 0\)\s*\{\s*M2C_BREAK\(\w*\);\s*\}')
FUNC_NAME = re.compile(r'^func_([0-9A-Fa-f]{8})$')


def region_of(addr):
    for name, (lo, hi) in REGIONS.items():
        if lo <= addr < hi:
            return name
    return '?'


def trim(words, pc):
    """Drop alignment nops after the last instruction (a nop in a delay slot stays)."""
    words = list(words)
    while len(words) > 1 and words[-1] == 0:
        prev = rabbitizer.Instruction(words[-2], vram=pc + 4 * (len(words) - 2),
                                      category=rabbitizer.InstrCategory.R5900)
        if prev.hasDelaySlot():
            break
        words.pop()
    return words


def mnemonic(word):
    return rabbitizer.Instruction(word, category=rabbitizer.InstrCategory.R5900).getOpcodeName()


def run_quiet(tool_dir, exe, args):
    """verify.run_tool without printing warnings: returns (ok, stderr)."""
    env = dict(os.environ, WINEPREFIX=str(Path.home() / '.wine-ps2'), WINEDEBUG='-all', WINEARCH='win32')
    try:
        p = subprocess.run(['wine', str(tool_dir / exe), *args], cwd=verify.ROOT, env=env,
                           capture_output=True, text=True, errors='replace', timeout=verify.TOOL_TIMEOUT)
    except subprocess.TimeoutExpired:
        return False, '%s timed out' % exe
    ok = p.returncode == 0 and 'error' not in p.stderr.lower()
    return ok, p.stderr


def first_error(stderr):
    """The first diagnostic that is not a warning nor GCC's 'undeclared identifier' footnote."""
    for line in stderr.splitlines():
        m = re.match(r'^\S+:\d+:\s*(.*)', line.strip())
        if m and not m.group(1).startswith('warning') and not re.search(
                r'Each undeclared|for each function it appears', m.group(1)):
            return m.group(1)[:120]
    lines = [l for l in stderr.strip().splitlines() if 'warning' not in l]
    return lines[-1][:120] if lines else 'failed'


class Sweep:
    def __init__(self, args):
        _, self.text, _ = itu.load_binary()
        self.sym_to_addr = verify.load_symbols()
        self.addr_to_sym = {a: s for s, a in self.sym_to_addr.items()}
        self.matched = whirl_paths.matched_addresses(self.addr_to_sym)
        starts = itu.parse_func_boundaries(self.text)
        end = e.TEXT_BASE + e.TEXT_SIZE
        self.sizes = {a: (starts[i + 1] if i + 1 < len(starts) else end) - a for i, a in enumerate(starts)}
        self.args = args

    def selected(self):
        a = self.args
        lo, hi = (int(a.range[0], 16), int(a.range[1], 16)) if a.range else \
            (REGIONS[a.region] if a.region != 'all' else (e.TEXT_BASE, e.TEXT_BASE + e.TEXT_SIZE))
        return [s for s in sorted(self.sizes) if lo <= s < hi and s not in self.matched
                and (not a.max_size or self.sizes[s] <= a.max_size)]

    def game_words(self, addr):
        off = addr - e.TEXT_BASE
        return trim(struct.unpack_from('<%dI' % (self.sizes[addr] // 4), self.text, off), addr)

    def target_of(self, name):
        m = FUNC_NAME.match(name)
        return int(m.group(1), 16) if m else self.sym_to_addr.get(name)

    def m2c(self, addr, words):
        asm = TMP / ('%08X.m2c.s' % addr)
        asm.write_text(itu.m2c_asm(addr, words, self.addr_to_sym, 'func_%08X' % addr))
        cmd = [sys.executable, '-m', 'm2c.main', '-t', 'mipsee-gcc-c', '--valid-syntax', '--allman',
               '--pointer-style', 'right', '--globals', 'none', str(asm)]
        try:
            p = subprocess.run(cmd, capture_output=True, text=True, errors='replace', timeout=M2C_TIMEOUT)
        except subprocess.TimeoutExpired:
            return None, 'm2c timed out'
        finally:
            asm.unlink(missing_ok=True)
        if p.returncode != 0 or not p.stdout.strip():
            return None, (p.stderr.strip().splitlines() or ['m2c failed'])[-1][:120]
        return p.stdout, None

    def compile(self, addr, draft):
        """Returns (words, relocs {index: (kind, symbol)}, None) or (None, None, error)."""
        comp = Path(self.args.compilers).resolve()
        tool_dir = comp / verify.COMPILER / verify.TOOL_DIR
        stem = TMP / ('%08X' % addr)
        c, i, s, o = (stem.with_suffix(x) for x in ('.c', '.i', '.s', '.o'))
        files = [c, i, s, o, s.with_name(s.stem + '.as.s')]
        r = lambda p: p.relative_to(verify.ROOT).as_posix()
        try:
            c.write_text(PRELUDE + draft)
            for exe, args in (('cpp.exe', ['-nostdinc', r(c), r(i)]),
                              ('cc1.exe', verify.CFLAGS + [r(i), '-o', r(s)])):
                ok, err = run_quiet(tool_dir, exe, args)
                if not ok:
                    return None, None, first_error(err)
            asm_dir, asm_exe = verify.resolve_assembler(comp)
            fixed = files[4]
            fixed.write_text(verify.mtc1_pair_nops(s.read_text(encoding='latin-1')), encoding='latin-1')
            ok, err = run_quiet(asm_dir, asm_exe, verify.ASFLAGS + ['-o', r(o), r(fixed)])
            if not ok:
                return None, None, 'as: ' + first_error(err)
            obj = verify.Elf32(o)
            ti, text = obj.section('.text')
            code = obj.contents(text)
            relocs = obj.relocations(ti)
            symbols = obj.symbols()
            want = 'func_%08X' % addr
            for name, value, size, kind, shndx in symbols:
                if name == want and shndx == ti:
                    break
            else:
                return None, None, 'function not in object'
            words = list(struct.unpack_from('<%dI' % (size // 4), code, value))
            notes = {}
            for pos, (kind, sym) in relocs.items():
                if value <= pos < value + size:
                    notes[(pos - value) // 4] = (kind, symbols[sym][0])
            return trim(words, 0), notes, None
        finally:
            if not self.args.keep:
                for f in files:
                    f.unlink(missing_ok=True)

    def compare(self, addr, ours, relocs, game):
        ndiff = 0
        if len(ours) == len(game):
            for idx, (w, g) in enumerate(zip(ours, game)):
                mask = 0
                if idx in relocs:
                    kind, name = relocs[idx]
                    mask = verify.RELOC_MASK.get(kind, verify.RELOC_MASK_DEFAULT)
                    target = self.target_of(name)
                    if kind == verify.R_MIPS_26 and target is not None:
                        w, mask = (w & ~mask) | (target >> 2 & mask), 0
                if (w ^ g) & ~mask & 0xFFFFFFFF:
                    ndiff += 1
        a, b = [mnemonic(w) for w in ours], [mnemonic(w) for w in game]
        score = difflib.SequenceMatcher(None, a, b, autojunk=False).ratio()
        if len(ours) == len(game) and ndiff == 0:
            return 'match', 1.0, 0
        if a == b:
            return 'regs', 1.0, ndiff
        return 'diff', score, (ndiff if len(ours) == len(game) else '')

    def one(self, addr):
        game = self.game_words(addr)
        row = {'addr': '%08X' % addr, 'size': self.sizes[addr], 'game': len(game), 'ours': '',
               'score': '', 'ndiff': '', 'name': self.addr_to_sym.get(addr, ''), 'note': ''}
        draft, err = self.m2c(addr, game)
        if draft is None:
            row.update(status='m2c-error', note=err)
            return row
        draft = DIV_CHECK.sub('', draft)
        (OUT / 'drafts' / ('%08X.c' % addr)).write_text(draft)
        if 'unknown instruction' in draft:
            insns = sorted(set(re.findall(r'unknown instruction: (\S+)', draft)))
            row.update(status='asm', note=' '.join(insns)[:120])
            return row
        if 'M2C_ERROR' in draft or UNSUPPORTED.search(draft):
            m = re.search(r'M2C_ERROR\(/\* (.*?) \*/\)', draft) or UNSUPPORTED.search(draft)
            row.update(status='m2c-error', note=(m.group(1) if m.groups() else m.group(0))[:120])
            return row
        ours, relocs, err = self.compile(addr, draft)
        if ours is None and VOID_PTR.search(draft):
            # m2c sometimes dereferences a void * it could not type; as char * it compiles (with byte
            # loads where the game has words, which the score shows).
            ours, relocs, err2 = self.compile(addr, VOID_PTR.sub('char *', draft))
            row['note'] = 'void* compiled as char*'
        if ours is None:
            row.update(status='cc-error', note=err)
            return row
        status, score, ndiff = self.compare(addr, ours, relocs, game)
        row.update(status=status, score='%.3f' % score, ndiff=ndiff, ours=len(ours))
        return row


def load_results():
    path = OUT / 'results.tsv'
    rows = {}
    if path.is_file():
        lines = path.read_text().splitlines()
        for line in lines[1:]:
            parts = line.split('\t')
            if len(parts) == len(COLUMNS):
                rows[int(parts[0], 16)] = dict(zip(COLUMNS, parts))
    return rows


def cmd_run(args):
    verify.enter_sandbox()
    sweep = Sweep(args)
    (OUT / 'drafts').mkdir(parents=True, exist_ok=True)
    TMP.mkdir(parents=True, exist_ok=True)
    done = {} if args.redo else load_results()
    todo = [a for a in sweep.selected() if a not in done]
    # Large functions last, so most of the table fills early.
    todo.sort(key=lambda a: sweep.sizes[a])
    path = OUT / 'results.tsv'
    if args.redo and path.is_file():
        kept = [r for a, r in load_results().items() if a not in set(todo)]
        path.write_text('\t'.join(COLUMNS) + '\n' + ''.join('\t'.join(str(r[c]) for c in COLUMNS) + '\n'
                                                             for r in kept))
    if not path.is_file():
        path.write_text('\t'.join(COLUMNS) + '\n')
    print('%d functions to do (%d already in %s), %d jobs' % (len(todo), len(done), path, args.jobs),
          flush=True)
    lock, counts, start = threading.Lock(), collections.Counter(), time.time()

    def work(addr):
        try:
            row = sweep.one(addr)
        except Exception as exc:  # keep going; the line records what broke
            row = {'addr': '%08X' % addr, 'size': sweep.sizes[addr], 'status': 'm2c-error', 'score': '',
                   'ndiff': '', 'ours': '', 'game': '', 'name': '', 'note': ('tool: %r' % exc)[:120]}
        row['note'] = re.sub(r'[\t\n]', ' ', str(row['note']))
        with lock:
            with path.open('a') as f:
                f.write('\t'.join(str(row[c]) for c in COLUMNS) + '\n')
            counts[row['status']] += 1
            n = sum(counts.values())
            if n % args.every == 0 or n == len(todo):
                print('%5d/%d  %s  %.0f s' % (n, len(todo), '  '.join('%s %d' % (s, counts[s])
                      for s in STATUS_ORDER if counts[s]), time.time() - start), flush=True)

    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        list(pool.map(work, todo))
    return 0


def cmd_report(args):
    sweep = Sweep(args)
    wanted = set(sweep.selected())
    rows = [r for a, r in load_results().items() if a in wanted]
    if not rows:
        print('no results for this selection in %s (run "m2c_sweep.py run" first)' % (OUT / 'results.tsv'))
        return 1
    counts = collections.Counter(r['status'] for r in rows)
    bytes_ = collections.Counter()
    for r in rows:
        bytes_[r['status']] += int(r['size'])
    print('%d unmatched functions with results (%d not swept yet)' % (len(rows), len(wanted) - len(rows)))
    print('  ' + '  '.join('%s %d (%d B)' % (s, counts[s], bytes_[s]) for s in STATUS_ORDER if counts[s]))
    for lo, hi in ((0.9, 1.01), (0.75, 0.9), (0.5, 0.75)):
        n = sum(1 for r in rows if r['status'] == 'diff' and lo <= float(r['score']) < hi)
        print('  diff with score %.2f-%.2f: %d' % (lo, min(hi, 1.0), n))
    pick = [r for r in rows if not args.status or r['status'] == args.status]
    rank = {s: i for i, s in enumerate(STATUS_ORDER)}
    pick.sort(key=lambda r: (rank[r['status']], -float(r['score'] or 0), int(r['size'])))
    for r in pick[:args.top]:
        print('  %s %5s B  %-9s %5s  %s%s' % (r['addr'], r['size'], r['status'], r['score'] or '-',
              (r['name'] + ' ') if r['name'] else '', r['note'] or
              ('%s diffs' % r['ndiff'] if r['ndiff'] != '' else '%s vs %s insns' % (r['ours'], r['game']))))
    return 0


def cmd_show(args):
    addr = int(args.addr, 16)
    row = load_results().get(addr)
    print('\t'.join('%s=%s' % (c, row[c]) for c in COLUMNS) if row else 'no result for %08X' % addr)
    draft = OUT / 'drafts' / ('%08X.c' % addr)
    if draft.is_file():
        print(draft.read_text().rstrip())
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = ap.add_subparsers(dest='cmd', required=True)
    for name in ('run', 'report'):
        p = sub.add_parser(name)
        p.add_argument('--region', choices=list(REGIONS) + ['all'], default='all')
        p.add_argument('--range', nargs=2, metavar=('START', 'END'))
        p.add_argument('--max-size', type=int, default=0, help='only functions up to this many bytes')
        p.add_argument('--compilers', default=str(COMPILERS))
        if name == 'run':
            p.add_argument('-j', '--jobs', type=int, default=os.cpu_count() or 4)
            p.add_argument('--redo', action='store_true', help='redo functions already in results.tsv')
            p.add_argument('--keep', action='store_true', help='keep the build files in build/sweep')
            p.add_argument('--every', type=int, default=100, help='progress line every N functions')
        else:
            p.add_argument('--status', choices=STATUS_ORDER)
            p.add_argument('--top', type=int, default=25)
    p = sub.add_parser('show')
    p.add_argument('addr')
    args = ap.parse_args()
    try:
        return {'run': cmd_run, 'report': cmd_report, 'show': cmd_show}[args.cmd](args)
    except verify.VerifyError as exc:
        print('error: %s' % exc, file=sys.stderr)
        return 1


if __name__ == '__main__':
    sys.exit(main())
