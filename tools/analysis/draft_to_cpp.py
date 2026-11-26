#!/usr/bin/env python3
"""Turn m2c sweep drafts into C++ in src/game/blocks/Block_<16 KB block>.cpp, in batches.

Usage:
  draft_to_cpp.py plan [--range A B | --region R] [--status match,regs] [--write FILE] [--list]
  draft_to_cpp.py emit (ADDR... | --from FILE)
  draft_to_cpp.py fixcompile
  draft_to_cpp.py syms [--drop-stale]
  draft_to_cpp.py prune
  draft_to_cpp.py status

The drafts are the ones `m2c_sweep.py run` writes (../whirl-tour-work/sweep/drafts, WHIRL_SWEEP). This
tool handles drafts that read no struct fields (no M2C_FIELD): free functions, wrappers, functions on
globals, strings and float constants. Drafts that read fields need struct types first, by hand.

plan        For each unmatched draft of the given status (default: match and regs) without M2C_FIELD,
            says whether `emit` converts it, why not, and which traps the draft shows (below).
            --write FILE writes the convertible addresses, one per line, for `emit --from FILE`.
emit        Appends the functions to their block file (a section "Converted from m2c sweep drafts"),
            with the declarations of their callees and globals. Strings and floats of .rodata become
            literals (rebuild.py checks them against the game's bytes); other globals become typed
            `extern`s named data_<addr> (or their symbol). Callees are declared with the parameters of
            their symbol when it is mangled. The batch is recorded in <sweep>/draft_to_cpp.json.
fixcompile  Builds each file of the batch and removes the new functions that hold a compile error, until
            it builds.
syms        Adds to config/symbols.txt the func_<addr> functions and callees the batch's objects define or
            use, and the data symbols. --drop-stale also removes the lines this working tree added to
            symbols.txt (git diff) whose name no object under build/ uses any more, after renames.
prune       Runs verify.py on the batch's files and removes the new functions that differ from the game;
            then the declarations nothing uses any more. Run `syms` before (verify needs the names).
status      The batch: functions per file, and what was skipped and why.

Usual order: plan --write F, emit --from F, fixcompile, syms, prune, syms --drop-stale, then
tools/check_all.py. Then fix by hand what fixcompile and prune removed (see the traps).

Never converted: addresses 4 mod 8 (rebuild.py cannot place them: cc1plus aligns functions to 8; they are
usually the cases of a switch the function list split, see docs/MATCHING.md), the sound library
(0x001A5998..0x001AC000, an open decision in TODO.md), and RTTI vtable slots (write them in their class).

Traps in m2c drafts (`plan` warns about them; see docs/MATCHING.md):
- byte-offsets: m2c adds byte offsets to typed pointers (`s32 *p; p + 4` means 4 bytes, not 16). The
  sweep's `regs` status allows different immediates, so such a draft can be `regs`; use a struct.
- params: m2c leaves out parameters the body does not name (`f(s32 arg1)` still receives $a0), and a
  function that forwards $a0 to its callee shows the call without it.
- int pointers: strings, buffers and allocations come out as s32; the C++ will not compile until typed.
"""
import argparse
import json
import os
import re
import struct
import subprocess
import sys
from collections import Counter
from pathlib import Path

import whirl_paths
from whirl_paths import REPO, SLUS
import verify  # noqa: E402
import extract_rtti as e  # noqa: E402
import inspect_tu as itu  # noqa: E402
import m2c_sweep  # noqa: E402

DRAFTS = m2c_sweep.OUT / 'drafts'
STATE = m2c_sweep.OUT / 'draft_to_cpp.json'
BLOCKS = REPO / 'src' / 'game' / 'blocks'
SYMS = REPO / 'config' / 'symbols.txt'
LIBC_H = REPO / 'include' / 'common' / 'libc.h'
SOUND_LIBRARY = (0x001A5998, 0x001AC000)
SECTION = ('// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants\n'
           '// are literals, variables are data_<addr> in config/symbols.txt.\n')
SECTION_MARKERS = ('// Converted from m2c sweep drafts', '// Matched from the second m2c sweep')
SYMS_HEADER = '# Block files, m2c sweep drafts (draft_to_cpp.py): functions and callees, and the data they use'
SYMS_MARKERS = (SYMS_HEADER, '# Block files, second m2c sweep')
BASIC = {'v': 'void', 'i': 'int', 'Ui': 'u32', 's': 's16', 'Us': 'u16', 'c': 'char', 'Uc': 'u8',
         'Sc': 's8', 'f': 'f32', 'd': 'f64', 'l': 's64', 'Ul': 'u64', 'b': 'bool'}
ELEMENT_SIZE = {'s8': 1, 'u8': 1, 'char': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'int': 4, 'f32': 4,
                's64': 8, 'u64': 8, 'f64': 8}


class Image:
    """The game's ELF: section of an address, file offset, strings."""

    def __init__(self, path):
        self.data = data = Path(path).read_bytes()
        shoff, = struct.unpack_from('<I', data, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from('<HHH', data, 0x2E)
        secs = []
        for i in range(shnum):
            name, typ, _flags, addr, off, size = struct.unpack_from('<6I', data, shoff + i * shentsize)
            secs.append([name, typ, addr, off, size])
        stroff = secs[shstrndx][3]
        for s in secs:
            s[0] = data[stroff + s[0]:data.index(b'\0', stroff + s[0])].decode()
        self.secs = secs

    def section_of(self, addr):
        """(section name, file offset or None for NOBITS)."""
        for name, typ, base, off, size in self.secs:
            if base and base <= addr < base + size:
                return name, (off + addr - base if typ != 8 else None)
        return '?', None

    def string_at(self, off):
        if off is None:
            return None
        end = self.data.find(b'\0', off, off + 400)
        s = self.data[off:end]
        return s if end > off and all(32 <= c < 127 or c in (9, 10) for c in s) else None


def load_syms():
    n2a, a2n = {}, {}
    for line in SYMS.read_text().splitlines():
        p = line.split()
        if len(p) >= 2 and p[0].startswith('0x'):
            n2a[p[1]] = int(p[0], 16)
            a2n.setdefault(int(p[0], 16), p[1])
    return n2a, a2n


def libc_names():
    return set(re.findall(r'\b(\w+)\s*\(', re.sub(r'/\*.*?\*/', '', LIBC_H.read_text(), flags=re.S))) - {'if'}


def demangle_params(code):
    """'iPvPC7TextObj' -> (['int', 'void *', 'const TextObj *'], {'TextObj'}); None if unsupported."""
    out, classes, i = [], set(), 0
    if code == 'v':
        return [], classes
    while i < len(code):
        ptr, const = '', ''
        while i < len(code) and code[i] in 'PC':
            if code[i] == 'P':
                ptr += '*'
            else:
                const = 'const '
            i += 1
        if i < len(code) and code[i].isdigit():
            m = re.match(r'\d+', code[i:])
            n = int(m.group(0))
            name = code[i + len(m.group(0)):i + len(m.group(0)) + n]
            i += len(m.group(0)) + n
            classes.add(name)
            base = name
        else:
            for k in ('Ui', 'Us', 'Uc', 'Sc', 'Ul', 'v', 'i', 's', 'c', 'f', 'd', 'l', 'b'):
                if code.startswith(k, i):
                    base = BASIC[k]
                    i += len(k)
                    break
            else:
                return None
        out.append((const + base + (' ' + ptr if ptr else '')).strip())
    return out, classes


def c_string(b):
    s = ''
    for ch in b:
        if ch == 0x22:
            s += '\\"'
        elif ch == 0x5C:
            s += '\\\\'
        elif ch == 10:
            s += '\\n'
        elif 32 <= ch < 127:
            s += chr(ch)
        else:
            s += '\\%03o' % ch
    return '"%s"' % s


def f32_literal(bits):
    v = struct.unpack('<f', struct.pack('<I', bits))[0]
    for n in range(1, 10):
        t = '%.*g' % (n, v)
        if struct.unpack('<I', struct.pack('<f', float(t)))[0] == bits:
            break
    if 'e' not in t and '.' not in t:
        t += '.0'
    return t + 'f'


def f64_literal(raw):
    v = struct.unpack('<d', raw)[0]
    for n in range(1, 18):
        t = '%.*g' % (n, v)
        if float(t) == v:
            break
    return t if ('.' in t or 'e' in t) else t + '.0'


def ctype(t):
    t = t.strip()
    t = re.sub(r'\bs32\b', 'int', t)
    return re.sub(r'\bM2C_UNK\b', 'int', t)


def call_arg_counts(name, body):
    """The number of arguments of every call to `name` in body."""
    counts = []
    for m in re.finditer(r'(?<![\w.])%s\(' % re.escape(name), body):
        depth, i, n, empty = 1, m.end(), 1, True
        while i < len(body) and depth:
            c = body[i]
            if c in '([':
                depth += 1
            elif c in ')]':
                depth -= 1
            elif c == ',' and depth == 1:
                n += 1
            if depth and not c.isspace():
                empty = False
            i += 1
        counts.append(0 if empty else n)
    return counts


def traps(head, body):
    """Warnings for the m2c habits that make a converted draft wrong (see the module docstring)."""
    out = []
    decls = re.findall(r'\b(s8|u8|char|s16|u16|s32|u32|int|f32|s64|u64|f64|void)\s*\*\s*(\w+)', head + '\n' + body)
    for typ, var in decls:
        size = ELEMENT_SIZE.get(typ, 0)
        for m in re.finditer(r'\b%s\s*([+-])=?\s*(0x[0-9A-Fa-f]+|\d+)\b' % re.escape(var), body):
            n = int(m.group(2), 0)
            if size != 1 and n not in (0, 1):
                out.append('byte-offsets: `%s %s %s` is %d bytes in m2c, not %d %s elements'
                           % (var, m.group(1), m.group(2), n, n, typ))
                break
    ints = re.findall(r'\b(?:s32|int|u32)\s+(\w+)\b(?!\s*\()', head + '\n' + body)
    for var in ints:
        if re.search(r'\*\s*\(?\s*%s\b' % re.escape(var), body):
            out.append('int pointers: `%s` is an int the draft dereferences (type it as a pointer)' % var)
            break
    params = re.search(r'\((.*)\)\s*$', head)
    if params:
        regs = sorted(int(x) for x in re.findall(r'\barg(\d+)\b', params.group(1)))
        if regs and regs != list(range(len(regs))):
            out.append('params: the draft names arg%s only; the function also receives the arguments '
                       'before them' % ', arg'.join(map(str, regs)))
    return out


class Converter:
    def __init__(self):
        self.image = Image(SLUS)
        self.n2a, self.a2n = load_syms()
        self.libc = libc_names()
        _, text, rodata = itu.load_binary()
        vtables = e.find_vtables(rodata, e.find_tf_functions(text, e.find_rtti_strings(rodata)))
        self.slots = {s['func']: (v['class_name'], s['slot']) for v in vtables for s in v['slots']}

    def skip_reason(self, addr):
        if addr % 8 == 4:
            return '4 mod 8 (rebuild.py cannot place it; a switch case piece?)'
        if SOUND_LIBRARY[0] <= addr < SOUND_LIBRARY[1]:
            return 'sound library (open decision)'
        if addr in self.slots:
            return 'vtable slot %d of %s (write it in its class)' % (self.slots[addr][1], self.slots[addr][0])
        return None

    def convert(self, addr):
        """(result dict, None) or (None, reason)."""
        d = (DRAFTS / ('%08X.c' % addr)).read_text()
        if 'M2C_FIELD' in d:
            return None, 'reads struct fields'
        lines = d.split('\n')
        protos, externs, i = [], [], 0
        while i < len(lines) and lines[i].strip():
            m = re.match(r'^(.+?)\b(\w+)\((.*)\);\s*/\* extern \*/$', lines[i])
            ex = re.match(r'^extern (.+?)\s*\b(\w+);$', lines[i])
            if m:
                protos.append((m.group(1).strip(), m.group(2), m.group(3)))
            elif ex:
                externs.append((ex.group(1), ex.group(2)))
            else:
                break
            i += 1
        func = '\n'.join(lines[i:]).strip() + '\n'
        if not func.startswith(('void', 's32', 'u32', 'f32', 's16', 'u16', 's8', 'u8', 'M2C', 's64', 'f64')):
            return None, 'unexpected layout'
        fname = 'func_%08X' % addr
        head, body = func.split('\n', 1)
        m = re.match(r'^(.*?)\b%s\((.*)\)$' % fname, head)
        if not m:
            return None, 'head'
        ret, params = m.group(1).strip(), m.group(2)
        warnings = traps(head, body)
        own = self.a2n.get(addr)
        name = fname
        if own and own != fname:
            if '__F' not in own or re.search(r'__\d', own):
                return None, 'named %s (write it by hand)' % own
            base, code = own.split('__F', 1)
            dp = demangle_params(code)
            if dp is None or dp[1]:
                return None, 'own params %s' % own
            mparams = [] if params.strip() == 'void' else [p.strip() for p in params.split(',')]
            if len(dp[0]) != len(mparams):
                return None, 'own arity %s (the symbol has another parameter count)' % own
            for k, (t, mp) in enumerate(zip(dp[0], mparams)):
                if '*' in mp and '*' not in t:
                    return None, 'own types %s (its symbol says %s for parameter %d, the draft a pointer)' % (
                        own, t, k)
            params = ', '.join('%s arg%d' % (t, k) for k, t in enumerate(dp[0])) or 'void'
            name = base
        out = {'decls': {}, 'externs': {}, 'libc': False, 'classes': set(), 'datasyms': {}}
        for typ, g in externs:
            gm = re.match(r'^D_([0-9A-F]{8})$', g)
            ga = int(gm.group(1), 16) if gm else self.n2a.get(g)
            if ga is None:
                return None, 'global %s' % g
            sec, off = self.image.section_of(ga)
            if sec == '.text':
                return None, 'text address'
            s = self.image.string_at(off) if typ == 'char' and sec == '.rodata' else None
            if s is not None:
                if re.search(r'(?<!&)\b%s\b' % g, body):
                    return None, 'string used without &'
                body = re.sub(r'&%s\b' % g, lambda _: c_string(s), body)
            elif typ == 'f32' and sec == '.rodata':
                if re.search(r'&%s\b' % g, body):
                    return None, 'float address'
                bits = struct.unpack_from('<I', self.image.data, off)[0]
                body = re.sub(r'\b%s\b' % g, f32_literal(bits), body)
            elif typ == 'f64' and sec == '.rodata':
                body = re.sub(r'\b%s\b' % g, f64_literal(self.image.data[off:off + 8]), body)
            elif typ == 'char' or sec == '.rodata':
                return None, 'global %s %s (a table: type it first)' % (sec, typ)
            else:
                sym = self.a2n.get(ga)
                nm = g if not gm else (sym if sym and re.fullmatch(r'[A-Za-z_]\w*', sym) else 'data_%08X' % ga)
                body = re.sub(r'\b%s\b' % g, nm, body)
                out['externs'][nm] = 'extern %s %s;' % (ctype(typ), nm)
                if nm not in self.n2a:
                    out['datasyms'][nm] = ga
        for pret, cname, pparams in protos:
            if cname in self.libc:
                out['libc'] = True
                continue
            uses_value = bool(re.search(r'(?<![\w.])%s\(' % cname, re.sub(r'(?m)^\s*%s\(' % cname, '', body)))
            if re.search(r'__\d', cname):
                return None, 'method callee %s' % cname
            if '__F' in cname:
                base, code = cname.split('__F', 1)
                dp = demangle_params(code)
                if dp is None:
                    return None, 'callee params %s' % cname
                out['classes'] |= dp[1]
                ptypes = dp[0]
                counts = set(call_arg_counts(cname, body))
                if counts - {len(ptypes)}:
                    return None, 'callee arity %s (called with %s arguments; its symbol has %d)' % (
                        cname, '/'.join(map(str, sorted(counts))), len(ptypes))
                body = re.sub(r'\b%s\(' % re.escape(cname), base + '(', body)
                cn, ca = base, self.n2a.get(cname)
            else:
                if cname in self.n2a and not cname.startswith('func_'):
                    return None, 'C callee %s' % cname
                ptypes = [] if pparams.strip() in ('', 'void') else [ctype(p) for p in pparams.split(',')]
                cn = cname
                cm = re.match(r'func_([0-9A-F]{8})$', cname)
                ca = int(cm.group(1), 16) if cm else self.n2a.get(cname)
            r = ctype(pret) if pret != 'M2C_UNK' else ('int' if uses_value else 'void')
            out['decls'][cn] = ('%s%s%s(%s);' % (r, '' if r.endswith('*') else ' ', cn, ', '.join(ptypes)), ca)
        if 'M2C' in body or re.search(r'\bsp\b', body):
            return None, 'macro left'
        rt = ctype(ret)
        text = '%s%s%s(%s)\n%s' % (rt, '' if rt.endswith('*') else ' ', name,
                                   ctype(params) if params.strip() != 'void' else '', body)
        out['text'] = re.sub(r'\bs32\b', 'int', text)
        out['name'] = name
        out['warnings'] = warnings
        return out, None


def reason_key(why):
    """The kind of a skip reason, for the summary ('C callee strcpy' -> 'C callee')."""
    why = why.split(' (')[0]
    for prefix in ('vtable slot', 'C callee', 'named', 'method callee', 'own arity', 'own params',
                   'callee params', 'callee arity', 'own types', 'global'):
        if why.startswith(prefix):
            return ' '.join(why.split()[:3]) if prefix == 'global' else prefix
    return why


def candidates(args):
    results = m2c_sweep.load_results()
    sym_to_addr = verify.load_symbols()
    matched = whirl_paths.matched_addresses({a: s for s, a in sym_to_addr.items()})
    lo, hi = ((int(args.range[0], 16), int(args.range[1], 16)) if args.range
              else m2c_sweep.REGIONS[args.region] if args.region != 'all' else (0, 1 << 32))
    want = set(args.status.split(','))
    for addr, row in sorted(results.items()):
        if lo <= addr < hi and addr not in matched and row['status'] in want:
            yield addr, row


def cmd_plan(args):
    conv = Converter()
    reasons, ok, rows = Counter(), [], []
    for addr, row in candidates(args):
        if 'M2C_FIELD' in (DRAFTS / ('%08X.c' % addr)).read_text():
            reasons['reads struct fields'] += 1
            continue
        why = conv.skip_reason(addr)
        res = None
        if not why:
            res, why = conv.convert(addr)
        if res is None:
            reasons[reason_key(why)] += 1
            rows.append('%08X %5s %-6s skip: %s' % (addr, row['size'], row['status'], why))
        else:
            ok.append(addr)
            rows.append('%08X %5s %-6s ok%s' % (addr, row['size'], row['status'],
                                                 ''.join('\n    trap ' + w for w in res['warnings'])))
    print('%d convertible, %d not' % (len(ok), sum(reasons.values())))
    for k, v in reasons.most_common():
        print('  %4d  %s' % (v, k))
    if args.list:
        print('\n'.join(rows))
    if args.write:
        Path(args.write).write_text(''.join('%08X\n' % a for a in ok))
        print('wrote %d addresses to %s' % (len(ok), args.write))
    return 0


def emit(addrs):
    conv = Converter()
    state = {'files': {}, 'skipped': {}}
    by_block = {}
    for a in addrs:
        why = conv.skip_reason(a)
        res = None
        if not why:
            res, why = conv.convert(a)
        if res is None:
            state['skipped']['%08X' % a] = why
            continue
        for w in res['warnings']:
            print('%08X trap %s' % (a, w))
        by_block.setdefault(a & ~0x3FFF, []).append((a, res))
    for blk, items in sorted(by_block.items()):
        path = BLOCKS / ('Block_%08X.cpp' % blk)
        if path.exists():
            src = path.read_text()
        else:
            src = ('#include "common/types.h"\n\n// Functions of 0x%08X..0x%08X whose class and translation unit '
                   'are not known yet.\n// Names are address based; move each function to its file once its '
                   'TU is identified.\n' % (blk, blk + 0x3FFF))
        decls, externs, classes, libc, funcs = {}, {}, set(), False, []
        for a, r in sorted(items):
            for cn, (decl, ca) in r['decls'].items():
                if re.search(r'(?m)^[^\n(]*\b%s\(' % re.escape(cn), src):
                    continue  # the file declares it already
                decls.setdefault(cn, (decl, ca))
            externs.update({k: v for k, v in r['externs'].items()
                            if not re.search(r'(?m)^extern [^\n]*\b%s;' % re.escape(k), src)})
            classes |= r['classes']
            libc |= r['libc']
            funcs.append((a, r['name'], r['text']))
        add = '\n' + SECTION + '\n' if not any(m in src for m in SECTION_MARKERS) else '\n'
        for c in sorted(classes):
            if not re.search(r'\b(struct|class) %s\b' % c, src):
                add += 'struct %s;\n' % c
        dl = [(decl, ca) for decl, ca in decls.values()] + [(x, None) for x in externs.values()]
        if dl:
            width = max(len(x) for x, _ in dl)
            for decl, ca in sorted(dl, key=lambda x: (x[1] is None, x[1] or 0, x[0])):
                add += decl + ((' ' * (width - len(decl)) + ' // 0x%08X' % ca) if ca else '') + '\n'
            add += '\n'
        add += '\n'.join(t for _, _, t in funcs)
        if libc and '#include "common/libc.h"' not in src:
            src = src.replace('#include "common/types.h"\n', '#include "common/types.h"\n#include "common/libc.h"\n', 1)
        path.write_text(src.rstrip('\n') + '\n' + add)
        info = state['files'][path.name] = {'funcs': {('%08X' % a): (n, t) for a, n, t in funcs},
                                            'decls': {cn: d for cn, (d, _) in decls.items()},
                                            'externs': externs, 'datasyms': {}}
        for a, r in items:
            info['datasyms'].update(r['datasyms'])
    STATE.write_text(json.dumps(state, indent=1))
    print('emitted %d functions in %d files, skipped %d' % (
        sum(len(f['funcs']) for f in state['files'].values()), len(state['files']), len(state['skipped'])))
    for k, v in Counter(reason_key(v) for v in state['skipped'].values()).most_common():
        print('  %4d  %s' % (v, k))


def cmd_emit(args):
    addrs = [int(x, 16) for x in args.addrs]
    if args.from_file:
        addrs += [int(x, 16) for x in Path(args.from_file).read_text().split()]
    emit(addrs)
    return 0


def run_verify(paths):
    env = dict(os.environ)
    env.setdefault('WHIRL_COMPILERS', str(whirl_paths.COMPILERS))
    env.setdefault('WHIRL_SLUS', str(SLUS))
    p = subprocess.run([sys.executable, str(REPO / 'tools' / 'verify.py')] + [str(x) for x in paths],
                       cwd=REPO, capture_output=True, text=True, env=env)
    return p.stdout + p.stderr


def remove_unused_decls(src, info):
    """Drop the declarations this batch added that nothing in the file uses any more."""
    for n in list(info['decls']) + list(info['externs']):
        for mm in re.finditer(r'(?m)^[^\n]*\b%s\b[^\n]*;[^\n]*\n' % re.escape(n), src):
            line = mm.group(0)
            if line.startswith('extern ') or re.match(r'^[\w ]+\**\s*%s\(' % re.escape(n), line):
                rest = src[:mm.start()] + src[mm.end():]
                if not re.search(r'\b%s\b' % re.escape(n), rest):
                    src = rest
                break
    return re.sub(r'\n{3,}', '\n\n', src)


def cmd_fixcompile(args):
    state = json.loads(STATE.read_text())
    removed = 0
    for fname, info in state['files'].items():
        path = BLOCKS / fname
        for _ in range(60):
            out = run_verify([path])
            if 'failed' not in out:
                break
            errs = {int(n) for n, msg in re.findall(r'%s:(\d+): (.*)' % re.escape(fname), out)
                    if not msg.startswith('warning')}
            src = path.read_text()
            hit = False
            for a, (n, t) in list(info['funcs'].items()):
                start = src.find(t)
                if start < 0:
                    continue
                l0 = src[:start].count('\n') + 1
                if any(l0 <= x <= l0 + t.count('\n') for x in errs):
                    src = src.replace(t, '', 1)
                    del info['funcs'][a]
                    state['skipped'][a] = 'C++ compile error'
                    removed += 1
                    hit = True
            if not hit:
                print('%s: error outside the new functions:\n%s' % (fname, '\n'.join(out.splitlines()[-6:])))
                break
            path.write_text(remove_unused_decls(src, info))
    STATE.write_text(json.dumps(state, indent=1))
    print('removed %d for compile errors' % removed)
    return 0


def object_symbols(paths):
    names = set()
    for obj in paths:
        try:
            names |= {s[0] for s in verify.Elf32(obj).symbols()}
        except (OSError, ValueError, struct.error):
            pass
    return names


def cmd_syms(args):
    state = json.loads(STATE.read_text())
    n2a, _ = load_syms()
    new = {}
    for fname, info in state['files'].items():
        for n in object_symbols([verify.BUILD / 'game' / 'blocks' / (fname[:-4] + '.o')]):
            fm = re.match(r'^func_([0-9A-F]{8})__', n)
            if fm and n not in n2a:
                new[n] = int(fm.group(1), 16)
        for nm, ga in info['datasyms'].items():
            if nm not in n2a:
                new[nm] = ga
    text = SYMS.read_text().rstrip('\n')
    if new:
        if not any(m in text for m in SYMS_MARKERS):
            text += '\n\n' + SYMS_HEADER
        text += '\n' + ''.join('0x%08X %s\n' % (a, n) for n, a in sorted(new.items(), key=lambda x: (x[1], x[0])))
    SYMS.write_text(text.rstrip('\n') + '\n')
    print('added %d symbols' % len(new))
    if args.drop_stale:
        used = object_symbols(verify.BUILD.rglob('*.o'))
        diff = subprocess.run(['git', 'diff', '-U0', '--', str(SYMS)], cwd=REPO, capture_output=True,
                              text=True).stdout
        added = [l[1:] for l in diff.splitlines() if l.startswith('+0x')]
        stale = [l for l in added if len(l.split()) >= 2 and l.split()[1] not in used]
        text = SYMS.read_text()
        for l in stale:
            text = text.replace(l + '\n', '', 1)
        SYMS.write_text(text)
        print('dropped %d stale symbols%s' % (len(stale), ''.join('\n  ' + l for l in stale)))
    return 0


def cmd_prune(args):
    state = json.loads(STATE.read_text())
    out = run_verify([BLOCKS / f for f in state['files']])
    bad = set(re.findall(r'^\s*FAIL (\S+?): (?:\d+ of \d+ words differ|matches as far)', out, re.M))
    missing = re.findall(r'^\s*FAIL (\S+?): not in', out, re.M)
    if missing:
        print('note: %d functions are not in symbols.txt (run syms first): %s' % (len(missing), ' '.join(missing[:5])))
    removed = 0
    for fname, info in state['files'].items():
        path = BLOCKS / fname
        src = path.read_text()
        for a, (n, t) in list(info['funcs'].items()):
            if any(b == n or b.startswith(n + '__') for b in bad):
                src = src.replace(t, '', 1)
                del info['funcs'][a]
                state['skipped'][a] = 'differs from the game'
                removed += 1
        path.write_text(remove_unused_decls(src, info))
    STATE.write_text(json.dumps(state, indent=1))
    print('removed %d that differ' % removed)
    return 0


def cmd_status(args):
    state = json.loads(STATE.read_text())
    for fname, info in sorted(state['files'].items()):
        print('%s: %s' % (fname, ' '.join(sorted(info['funcs']))))
    print('skipped:')
    for a, why in sorted(state['skipped'].items(), key=lambda x: (x[1], x[0])):
        print('  %s  %s' % (a, why))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = ap.add_subparsers(dest='cmd', required=True)
    p = sub.add_parser('plan')
    p.add_argument('--region', choices=list(m2c_sweep.REGIONS) + ['all'], default='game')
    p.add_argument('--range', nargs=2, metavar=('START', 'END'))
    p.add_argument('--status', default='match,regs', help='comma-separated sweep statuses')
    p.add_argument('--write', metavar='FILE', help='write the convertible addresses here')
    p.add_argument('--list', action='store_true', help='one line per draft, with its reason and traps')
    p = sub.add_parser('emit')
    p.add_argument('addrs', nargs='*')
    p.add_argument('--from', dest='from_file', metavar='FILE')
    sub.add_parser('fixcompile')
    p = sub.add_parser('syms')
    p.add_argument('--drop-stale', action='store_true')
    sub.add_parser('prune')
    sub.add_parser('status')
    args = ap.parse_args()
    try:
        return {'plan': cmd_plan, 'emit': cmd_emit, 'fixcompile': cmd_fixcompile, 'syms': cmd_syms,
                'prune': cmd_prune, 'status': cmd_status}[args.cmd](args)
    except verify.VerifyError as exc:
        print('error: %s' % exc, file=sys.stderr)
        return 1


if __name__ == '__main__':
    sys.exit(main())
