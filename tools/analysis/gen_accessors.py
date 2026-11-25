#!/usr/bin/env python3
"""Draft C++ for the trivial methods of a class in an address range (accessor batches).

Usage:
  gen_accessors.py --range A B --class NAME [--data-start OFF] [--all]

Reads the unmatched functions in [A, B) and recognises leaf patterns on `this` ($a0):
getters (`return mFieldXX;`), address getters (`return &mFieldXX;`), setters, float add/subtract
(`mFieldXX += v;`), empty methods and constant returns. It prints three blocks to paste and review:
the method declarations with the field layout implied by the accesses (from --data-start, the size
of the base class, with char padding in between), the definitions, and the config/symbols.txt lines
(GCC 2.95 mangling). Functions it does not recognise are listed at the end for manual work, and functions that sit in
an RTTI vtable are marked so they get declared virtual in slot order.
Names are offset-based (GetField128, SetField128, AddField128, GetPtr110, ...); rename what has
evidence. Field types come from the instructions, so check them against other users of the class.
"""
import argparse
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

import inspect_tu as itu  # noqa: E402
import extract_rtti as e  # noqa: E402
import verify  # noqa: E402
import whirl_paths  # noqa: E402

JR_RA = 0x03E00008
LOADS = {0x23: 'int', 0x24: 'u8', 0x20: 's8', 0x25: 'u16', 0x21: 's16', 0x31: 'f32'}
STORES = {0x2B: 'int', 0x28: 'u8', 0x29: 'u16', 0x39: 'f32'}
SIZE = {'int': 4, 'u8': 1, 's8': 1, 'u16': 2, 's16': 2, 'f32': 4}
MANGLE = {'int': 'i', 'u8': 'Uc', 's8': 'Sc', 'u16': 'Us', 's16': 's', 'f32': 'f'}


def fields_of(w):
    return w >> 26, (w >> 21) & 0x1F, (w >> 16) & 0x1F, w & 0xFFFF


def classify(words):
    """Return (kind, offset, type, extra) for a recognised leaf pattern, or None."""
    if len(words) == 2 and words[0] == JR_RA:
        op, rs, rt, imm = fields_of(words[1])
        off = imm - 0x10000 if imm & 0x8000 else imm
        if words[1] == 0:
            return ('empty', None, None, None)
        if op in LOADS and rs == 4 and (rt == 2 or (op == 0x31 and rt == 0)):
            return ('get', off, LOADS[op], None)
        if op in STORES and rs == 4 and (rt == 5 or (op == 0x39 and rt == 12)):
            return ('set', off, STORES[op], None)
        if op == 0x09 and rs == 4 and rt == 2:
            return ('addr', off, None, None)
        if op == 0x09 and rs == 0 and rt == 2:
            return ('const', None, 'int', off)
    if len(words) == 4 and words[2] == JR_RA:
        op0, rs0, rt0, imm0 = fields_of(words[0])
        op3, rs3, rt3, imm3 = fields_of(words[3])
        fmt, func = (words[1] >> 21) & 0x1F, words[1] & 0x3F
        if op0 == 0x31 and op3 == 0x39 and rs0 == 4 and rs3 == 4 and imm0 == imm3 and (words[1] >> 26) == 0x11 \
                and fmt == 0x10 and func in (0, 1):
            off = imm0 - 0x10000 if imm0 & 0x8000 else imm0
            return ('add' if func == 0 else 'sub', off, 'f32', None)
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--range', nargs=2, required=True, metavar=('A', 'B'))
    ap.add_argument('--class', dest='cls', required=True)
    ap.add_argument('--data-start', type=lambda s: int(s, 16), default=0,
                    help='first offset of the class\'s own data (hex), e.g. A0 after AI_Agent')
    ap.add_argument('--all', action='store_true', help='include matched functions (to check the tool)')
    args = ap.parse_args()
    lo, hi = int(args.range[0], 16), int(args.range[1], 16)

    _, text, rodata = itu.load_binary()
    slots = {}
    for vt in e.find_vtables(rodata, e.find_tf_functions(text, e.find_rtti_strings(rodata))):
        for slot in vt['slots']:
            slots.setdefault(slot['func'], []).append('slot %d of %s' % (slot['slot'], vt['class_name']))
    addr_to_sym = {a: s for s, a in verify.load_symbols().items()}
    matched = whirl_paths.matched_addresses(addr_to_sym)
    starts = itu.parse_func_boundaries(text)
    cls = args.cls
    methods, manual, fields, names = [], [], {}, set()

    for i, a in enumerate(starts):
        if not lo <= a < hi or (a in matched and not args.all):
            continue
        end = starts[i + 1] if i + 1 < len(starts) else hi
        words = list(struct.unpack_from('<%dI' % ((end - a) // 4), text, a - e.TEXT_BASE))
        while len(words) > 2 and words[-1] == 0 and words[-3] == JR_RA:
            words.pop()
        c = classify(words)
        if c is None:
            manual.append((a, len(words)))
            continue
        kind, off, typ, extra = c
        if off is not None and off >= args.data_start:
            if typ and not fields.get(off):
                fields[off] = typ  # a typed access wins over an address-of
            else:
                fields.setdefault(off, None)
        f = 'Field%X' % off if off is not None else ''
        if kind == 'get':
            decl, body, params = '%s Get%s()' % (typ, f), 'return m%s;' % f, ''
        elif kind == 'set':
            decl, body, params = 'void Set%s(%s v)' % (f, typ), 'm%s = v;' % f, MANGLE[typ]
        elif kind == 'addr':
            decl, body, params = '@ *GetPtr%X()' % off, 'return &m%s;' % f, ''
        elif kind in ('add', 'sub'):
            decl = 'void %s%s(f32 v)' % ('Add' if kind == 'add' else 'Sub', f)
            body, params = 'm%s %s= v;' % (f, '+' if kind == 'add' else '-'), 'f'
        elif kind == 'empty':
            decl, body, params = 'void func_%08X()' % a, '', ''
        else:
            decl, body, params = 'int func_%08X()' % a, 'return %d;' % extra, ''
        name = decl.split('(')[0].split()[-1].lstrip('*')
        while name in names:  # two functions with the same shape (e.g. two getters of one field)
            name += 'b'
        names.add(name)
        decl = decl.split('(')[0].rsplit(' ', 1)[0] + ' ' + ('*' if '*' in decl.split('(')[0] else '') + name + \
            '(' + decl.split('(', 1)[1]
        decl = decl.replace(' **', ' *')
        methods.append((a, kind, off, decl, body, name, params))

    def ftype(off):
        return fields.get(off) or 'int'

    print('// ---- %s: declarations (in the class) ----' % cls)
    for a, kind, off, decl, body, name, params in methods:
        d = decl.replace('@', ftype(off)) if kind == 'addr' else decl
        note = (' (vtable %s: declare it virtual, in slot order)' % ', '.join(slots[a])) if a in slots else ''
        print('    %-36s// 0x%08X%s' % (d + ';', a, note))
    print('\n    // fields implied by the accesses (types from the instructions)')
    pos = args.data_start
    for off in sorted(o for o in fields if o >= args.data_start):
        if off < pos:
            print('    // overlap at 0x%X: check the types' % off)
            continue
        if off > pos:
            print('    char field_0x%X[0x%X];' % (pos, off - pos))
        t = ftype(off)
        print('    %-26s// 0x%X' % ('%s mField%X;' % (t, off), off))
        pos = off + SIZE[t]
    print('\n// ---- %s: definitions ----' % cls)
    for a, kind, off, decl, body, name, params in methods:
        d = decl.replace('@', ftype(off)) if kind == 'addr' else decl
        ret, rest = d.split(' ', 1)
        if rest.startswith('*'):
            ret, rest = ret + ' *', rest[1:]
        print('%s %s::%s\n{\n%s}\n' % (ret, cls, rest, ('    %s\n' % body) if body else ''))
    print('// ---- config/symbols.txt ----')
    for a, kind, off, decl, body, name, params in methods:
        print('0x%08X %s__%d%s%s' % (a, name, len(cls), cls, params))
    if manual:
        print('\n// ---- not recognised (write by hand): %d ----' % len(manual))
        for a, n in manual:
            print('//   0x%08X %d insns' % (a, n))
    return 0


if __name__ == '__main__':
    sys.exit(main())
