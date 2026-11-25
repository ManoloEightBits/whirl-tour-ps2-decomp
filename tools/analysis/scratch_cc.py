#!/usr/bin/env python3
"""Compile a loose C++ snippet with the game's toolchain and show what it turns into.

Usage:
  scratch_cc.py <file.cpp|-> [--func SUBSTR] [--asm] [--regs] [--vs ADDR] [-D NAME]

The snippet ("-" reads it from stdin) is copied to <repo>/build/scratch/ and built the way
verify.py builds src/: cpp -Iinclude -Isrc, cc1plus -O2 -G0 -fno-exceptions -ffast-math, SN's ps2eeas.
It can therefore #include "game/....h". Nothing needs to be listed in config/symbols.txt.

  --func SUBSTR  only show functions whose mangled or demangled name contains SUBSTR
  --asm          also print GCC's assembly (.s) for those functions
  --regs         register allocation per function: refs, live length, local/global,
                 global-alloc priority floor_log2(refs)*refs/live, allocation order, hard register
  --vs ADDR      compare the selected function (exactly one) with the game at ADDR, side by side
  -D NAME        preprocessor define (repeatable)

Run it with the analysis venv (tools/analysis/requirements.txt), e.g. ../whirl-tour-work/venv/bin/python3.
"""
import argparse
import re
import shutil
import struct
import sys
from pathlib import Path

import rabbitizer

from whirl_paths import REPO, SLUS, COMPILERS  # noqa: E402,F401

import verify  # noqa: E402

SCRATCH = verify.BUILD / 'scratch'
GPR = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
       's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9', 'k0', 'k1', 'gp', 'sp', 'fp', 'ra']


def reg_name(n):
    if n < 0:
        return 'stack'
    if n < 32:
        return '$' + GPR[n]
    if n < 64:
        return '$f%d' % (n - 32)
    return 'hard%d' % n


def dis(word, pc):
    return rabbitizer.Instruction(word, vram=pc, category=rabbitizer.InstrCategory.R5900).disassemble()


def build(src_text, stem, defines, regs):
    SCRATCH.mkdir(parents=True, exist_ok=True)
    src, ii, asm, obj = (SCRATCH / (stem + e) for e in ('.cpp', '.ii', '.s', '.o'))
    for old in SCRATCH.glob(stem + '.ii.*'):
        old.unlink()
    src.write_text(src_text)
    comp = Path(ARGS.compilers).resolve()
    tool_dir = comp / verify.COMPILER / verify.TOOL_DIR
    r = lambda p: p.relative_to(verify.ROOT).as_posix()
    verify.run_tool(tool_dir, 'cpp.exe', verify.CPPFLAGS + ['-D' + d for d in defines] + [r(src), r(ii)])
    verify.run_tool(tool_dir, 'cc1plus.exe', verify.CFLAGS + ARGS.cflag + (['-dl', '-dg'] if regs else []) + [r(ii), '-o', r(asm)])
    verify.assemble(comp, asm, obj)
    return ii, asm, obj


def functions(obj_path):
    """[(name, start, end, words, {index: reloc symbol})] for every function in .text."""
    obj = verify.Elf32(obj_path)
    ti, text = obj.section('.text')
    code = obj.contents(text)
    relocs = obj.relocations(ti)
    symbols = obj.symbols()
    funcs = sorted((v, s, n) for n, v, s, k, sh in symbols if sh == ti and k == verify.STT_FUNC)
    starts = [v for v, _, _ in funcs] + [len(code)]
    out = []
    for i, (start, size, name) in enumerate(funcs):
        end = start + size if size else starts[i + 1]
        # drop the alignment nop after "jr $ra; delay slot", as verify.py does
        if end - start > 8 and struct.unpack_from('<I', code, end - 4)[0] == 0 \
                and struct.unpack_from('<I', code, end - 12)[0] == 0x03E00008:
            end -= 4
        words = [struct.unpack_from('<I', code, p)[0] for p in range(start, end, 4)]
        notes = {(p - start) // 4: (relocs[p][0], symbols[relocs[p][1]][0]) for p in range(start, end, 4) if p in relocs}
        out.append((name, start, end, words, notes))
    return out


def split_dump(path):
    """{demangled function name: dump text} for a -dl/-dg dump file."""
    out = {}
    if not path.is_file():
        return out
    parts = re.split(r'^;; Function (.*)$', path.read_text(errors='replace'), flags=re.M)
    for i in range(1, len(parts) - 1, 2):
        out[parts[i].strip()] = parts[i + 1]
    return out


def show_regs(lreg, greg, wanted):
    used = re.compile(r'^Register (\d+) used (\d+) times? across (\d+) insns?( in block \d+)?;(.*)$', re.M)
    for fname, ltext in lreg.items():
        if not wanted(fname):
            continue
        gtext = greg.get(fname, '')
        order = []
        m = re.search(r'^;; \d+ regs to allocate:(.*)$', gtext, re.M)
        if m:
            order = [int(x) for x in m.group(1).split()]
        hard = {}
        m = re.search(r'^;; Register dispositions:\n(.*?)\n\s*\n', gtext, re.M | re.S)
        if m:
            for pseudo, h in re.findall(r'(\d+) in (-?\d+)', m.group(1)):
                hard[int(pseudo)] = int(h)
        for pseudo, h in re.findall(r'^;; Register (\d+) in (\d+)\.', ltext, re.M):
            hard.setdefault(int(pseudo), int(h))
        print('regs: %s' % fname)
        print('  %-6s %5s %5s  %-7s %8s  %-5s %-7s %s' % ('pseudo', 'refs', 'live', 'alloc', 'priority', 'order', 'hard', 'notes'))
        for m in used.finditer(ltext):
            pseudo, refs, live = int(m.group(1)), int(m.group(2)), int(m.group(3))
            local = m.group(4) is not None
            prio = '' if local else '%.3f' % ((refs.bit_length() - 1) * refs / float(max(live, 1)))
            pos = str(order.index(pseudo) + 1) if pseudo in order else ''
            notes = ', '.join(t.strip().rstrip('.') for t in m.group(5).split(';')
                              if t.strip() and ('user var' in t or 'pointer' in t or 'call' in t))
            print('  %-6d %5d %5d  %-7s %8s  %-5s %-7s %s' % (pseudo, refs, live, 'local' if local else 'global',
                                                             prio, pos, reg_name(hard[pseudo]) if pseudo in hard else '?', notes))
        print('  (refs are weighted by loop depth; global pseudos are allocated in "order", highest priority first)')


def show_asm(asm_path, name):
    text = asm_path.read_text(errors='replace')
    m = re.search(r'^\s*\.ent\s+%s\n.*?^\s*\.end\s+%s\n' % (re.escape(name), re.escape(name)), text, re.M | re.S)
    if m:
        print('asm: %s' % name)
        print(m.group(0).rstrip())


def compare_with_game(name, words, notes, address):
    import diff_func  # noqa: E402  (work dir tool; reuses its side-by-side printer)
    slus = verify.Elf32(ARGS.slus)
    _, text = slus.section('.text')
    game, base = slus.contents(text), text['addr']
    addresses = verify.load_symbols()
    offset = address - base
    if offset < 0 or offset + 4 * len(words) > len(game):
        raise verify.VerifyError('0x%08X is outside the game .text' % address)
    game_words, reloc_notes, diffs = [], {}, []
    for i, ours in enumerate(words):
        theirs, = struct.unpack_from('<I', game, offset + 4 * i)
        mask = 0
        if i in notes:
            kind, sym = notes[i]
            reloc_notes[i] = sym
            mask = verify.RELOC_MASK.get(kind, verify.RELOC_MASK_DEFAULT)
            target = addresses.get(sym)
            if kind == verify.R_MIPS_26 and target is not None:
                ours, mask = (ours & ~mask) | (target >> 2 & mask), 0
        if (ours ^ theirs) & ~mask & 0xFFFFFFFF:
            diffs.append(i)
        game_words.append(theirs)
    diff_func.print_side_by_side(address, name, words, game_words, reloc_notes, diffs, True)
    return 1 if diffs else 0


def main():
    global ARGS
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('source', help='snippet .cpp file, or - for stdin')
    ap.add_argument('--func', help='only functions whose name contains this')
    ap.add_argument('--asm', action='store_true', help="print GCC's .s for the selected functions")
    ap.add_argument('--regs', action='store_true', help='print the register allocation dump')
    ap.add_argument('--vs', type=lambda s: int(s, 16), metavar='ADDR', help='compare with the game at this hex address')
    ap.add_argument('-D', dest='defines', action='append', default=[])
    ap.add_argument('--cflag', action='append', default=[],
                    help='extra cc1plus flag, for experiments only (verify.py never uses it)')
    ap.add_argument('--compilers', default=str(COMPILERS))
    ap.add_argument('--slus', default=str(SLUS))
    ARGS = ap.parse_args()
    verify.enter_sandbox()  # before reading stdin: it re-executes the script inside the namespace
    if ARGS.source == '-':
        src_text, stem = sys.stdin.read(), 'stdin'
    else:
        path = Path(ARGS.source)
        src_text, stem = path.read_text(), path.stem
    try:
        ii, asm, obj = build(src_text, stem, ARGS.defines, ARGS.regs)
    except verify.VerifyError as e:
        print('scratch_cc: ' + str(e), file=sys.stderr)
        return 2
    sub = ARGS.func
    funcs = [f for f in functions(obj) if not sub or sub in f[0]]
    if ARGS.vs is not None:
        if len(funcs) != 1:
            print('scratch_cc: --vs needs exactly one function, --func selects %d: %s'
                  % (len(funcs), ', '.join(f[0] for f in funcs)), file=sys.stderr)
            return 2
        name, _, _, words, notes = funcs[0]
        status = compare_with_game(name, words, notes, ARGS.vs)
    else:
        status = 0
        for name, start, end, words, notes in funcs:
            print('%s:  (%d instructions)' % (name, len(words)))
            for i, w in enumerate(words):
                note = '  [%s]' % notes[i][1] if i in notes else ''
                print('  %04X  %08X  %-36s%s' % (start + 4 * i, w, dis(w, start + 4 * i), note))
    if ARGS.asm:
        for f in funcs:
            show_asm(asm, f[0])
    if ARGS.regs:
        show_regs(split_dump(Path(str(ii) + '.lreg')), split_dump(Path(str(ii) + '.greg')),
                  lambda fname: not sub or sub in fname)
    return status


if __name__ == '__main__':
    sys.exit(main())
