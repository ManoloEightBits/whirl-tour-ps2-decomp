#!/usr/bin/env python3
"""Which field each script keyword is read into: names for fields from the game's own parsers.

Usage:
  keyword_fields.py [--range A B | --func A] [--class C] [--all] [--tables]

The game's script parser (UnkParser in src/game/Parser.h) reads values with
  0x001C3270  UnkParser::func_001C3270(const char *key, f32 *out)   a float
  0x001C2C78  UnkParser::func_001C2C78(const char *key, char *out)  a string
and the key is the name the value has in the script ("speed", "radius", "accmax", ...). For every
such call this tool finds the key string ($a1) and where the value goes ($a2), following the
registers of the calling function in address order: "arg1+0x2C" is the second incoming argument (or a
register copied from it) plus 0x2C; for a method arg0 is `this`. The parser itself is one of the
arguments too (the one passed on as $a0), so the object is the other one. A value read into a stack buffer is
followed to the store that copies it into the object a few instructions later. The output is one line
per call: function (with its symbol when we have one), value type, key, destination. Destinations
the straight-line tracking cannot resolve are printed as the raw instruction (hidden without --all).

--tables also lists the keyword tables given to UnkParser::func_001C1D28 (pairs {id, "name"}),
which name the cases of the switch on UnkParser::mToken14 that follows.
--class C keeps the functions whose symbol belongs to class C (from config/symbols.txt).

It is a hint for names, not proof of a layout: check the function before renaming a field, and keep
the offset in the name when the key is generic ("value", "name", "type").
"""
import argparse
import bisect
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

import rabbitizer

sys.path.insert(0, str(Path(__file__).resolve().parent))
import whirl_paths  # noqa: E402,F401
import inspect_tu as itu  # noqa: E402
import extract_rtti as e  # noqa: E402
import verify  # noqa: E402

READERS = {0x001C3270: 'f32', 0x001C2C78: 'string'}
NEXT_KEYWORD = 0x001C1D28
LOOKAHEAD = 10  # instructions after the call searched for the copy out of a stack buffer


def ins_at(text, pc):
    w, = struct.unpack_from('<I', text, pc - e.TEXT_BASE)
    return rabbitizer.Instruction(w, vram=pc, category=rabbitizer.InstrCategory.R5900)


def ops(ins):
    """('addiu', ['$a2', '$s1', '0x2C']) with offsets of memory operands split: lw $v0, 0x8($s0) ->
    ['$v0', '0x8', '$s0']."""
    d = ins.disassemble().split(None, 1)
    args = [] if len(d) < 2 else [a.strip() for a in re.split(r'[,()]', d[1]) if a.strip()]
    return d[0], args


def imm(s):
    return int(s, 16) if s.lstrip('-').startswith('0x') else int(s)


class Tracker:
    """Straight-line register values: 'argN+K' (an incoming argument plus K), 'sp+K', ('hi', K), ('addr', A)."""

    def __init__(self):
        self.v = {'$a0': 'arg0', '$a1': 'arg1', '$a2': 'arg2', '$a3': 'arg3', '$sp': 'sp+0'}

    def step(self, ins):
        op, a = ops(ins)
        if not a:
            return
        rd = a[0]
        if rd == '$sp':
            return  # offsets stay relative to the current frame, as the loads and stores use them
        new = None
        if op in ('daddu', 'addu', 'or') and len(a) == 3 and a[2] == '$zero':
            new = self.v.get(a[1])
        elif op in ('move',) and len(a) == 2:
            new = self.v.get(a[1])
        elif op in ('addiu', 'daddiu') and len(a) == 3:
            base = self.v.get(a[1])
            if isinstance(base, str):
                kind, off = base.split('+') if '+' in base else (base, '0')
                new = '%s+%d' % (kind, int(off) + imm(a[2]))
            elif isinstance(base, tuple) and base[0] == 'hi':
                new = ('addr', base[1] + imm(a[2]))
        elif op == 'lui':
            new = ('hi', imm(a[1]) << 16)
        elif op in ('jal', 'jalr'):
            for r in ('$v0', '$v1', '$a0', '$a1', '$a2', '$a3', '$t0', '$t1', '$t2', '$t3'):
                self.v.pop(r, None)
            return
        if ins.isBranch() or ins.isJump() or op.startswith(('s', 'c.')) and op not in ('sll', 'srl', 'sra', 'slt',
                                                                                        'sltu', 'slti', 'sltiu',
                                                                                        'sub', 'subu', 'sllv',
                                                                                        'srlv', 'srav'):
            return
        if rd.startswith('$') and rd != '$zero':
            if new is None:
                self.v.pop(rd, None)
            else:
                self.v[rd] = new


SEGMENTS = []


def file_offset(data, addr):
    """File offset of a virtual address, from the ELF program headers (PT_LOAD), or None."""
    if not SEGMENTS:
        phoff, = struct.unpack_from('<I', data, 0x1C)
        phentsize, phnum = struct.unpack_from('<HH', data, 0x2A)
        for i in range(phnum):
            p_type, p_offset, p_vaddr, _, p_filesz = struct.unpack_from('<5I', data, phoff + i * phentsize)
            if p_type == 1:
                SEGMENTS.append((p_vaddr, p_offset, p_filesz))
    for vaddr, off, size in SEGMENTS:
        if vaddr <= addr < vaddr + size:
            return addr - vaddr + off
    return None


def string_at(data, addr):
    off = file_offset(data, addr)
    if off is None:
        return None
    end = data.find(b'\0', off, off + 256)
    s = data[off:end] if end >= 0 else b''
    return s.decode('latin-1') if s and all(32 <= c < 127 for c in s) else None


def fmt_dest(v):
    if isinstance(v, str):
        kind, off = v.split('+') if '+' in v else (v, '0')
        return kind if int(off) == 0 else '%s+0x%X' % (kind, int(off))
    return None


def analyse(data, text, starts, lo, hi):
    """[(call pc, function start, type, key, destination, raw)] and {function: [table addresses]}."""
    rows, tables = [], defaultdict(list)
    words = struct.unpack_from('<%dI' % (len(text) // 4), text)
    calls = defaultdict(list)
    for i, w in enumerate(words):
        if w >> 26 == 3:
            t = (w & 0x03FFFFFF) << 2
            pc = e.TEXT_BASE + i * 4
            if (t in READERS or t == NEXT_KEYWORD) and lo <= pc < hi:
                calls[starts[bisect.bisect_right(starts, pc) - 1]].append((pc, t))
    for fstart, fcalls in sorted(calls.items()):
        tr = Tracker()
        pc = fstart
        for call_pc, target in fcalls:
            while pc < call_pc + 8:  # through the delay slot
                if pc != call_pc:
                    tr.step(ins_at(text, pc))
                pc += 4
            # the delay slot ran after the jal in step order above; registers it set are valid at the call
            key_reg, dest_reg = tr.v.get('$a1'), tr.v.get('$a2')
            if target == NEXT_KEYWORD:
                if isinstance(key_reg, tuple) and key_reg[0] == 'addr':
                    tables[fstart].append(key_reg[1])
                tr.step(ins_at(text, call_pc))
                continue
            key = string_at(data, key_reg[1]) if isinstance(key_reg, tuple) and key_reg[0] == 'addr' else None
            dest = fmt_dest(dest_reg)
            raw = None
            if dest and dest.startswith('sp'):
                # follow the copy out of the stack buffer: load from the same slot, store through this
                slot = int(dest_reg.split('+')[1])
                loaded = {}
                for k in range(2, 2 + LOOKAHEAD):
                    ins = ins_at(text, call_pc + 4 * k)
                    op, a = ops(ins)
                    if op in ('lw', 'lwc1') and len(a) == 3 and a[2] == '$sp' and imm(a[1]) == slot:
                        loaded[a[0]] = True
                    elif op in ('sw', 'swc1') and len(a) == 3 and a[0] in loaded:
                        base = tr.v.get(a[2])
                        if isinstance(base, str) and base.startswith('arg'):
                            kind, off = base.split('+') if '+' in base else (base, '0')
                            dest = '%s+0x%X (via stack)' % (kind, int(off) + imm(a[1]))
                        break
                    if ins.isJump() or op.startswith('jal'):
                        break  # conditional branches are fine: the copy is usually under "if it was read"
            elif dest is None:
                raw = ins_at(text, call_pc + 4).disassemble()
            rows.append((call_pc, fstart, READERS[target], key, dest, raw))
            tr.step(ins_at(text, call_pc))
    return rows, tables


def keyword_table(data, addr, limit=200):
    """[(id, name)] of a {int id; const char *name;} table ending with a null name."""
    out, off = [], file_offset(data, addr)
    if off is None:
        return out
    for _ in range(limit):
        ident, name = struct.unpack_from('<iI', data, off)
        s = string_at(data, name) if name else None
        if not s:
            break
        out.append((ident, s))
        off += 8
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--range', nargs=2, metavar=('START', 'END'))
    ap.add_argument('--func', help='one function (an address inside it is enough)')
    ap.add_argument('--class', dest='cls', help='only functions whose symbol belongs to this class')
    ap.add_argument('--all', action='store_true', help='also print calls whose destination is unresolved')
    ap.add_argument('--tables', action='store_true', help='also print the keyword tables')
    args = ap.parse_args()

    data, text, _ = itu.load_binary()
    starts = itu.parse_func_boundaries(text)
    sym = verify.load_symbols()
    a2s = {a: s for s, a in sym.items()}
    lo, hi = e.TEXT_BASE, e.TEXT_BASE + e.TEXT_SIZE
    if args.range:
        lo, hi = int(args.range[0], 16), int(args.range[1], 16)
    if args.func:
        a = int(args.func, 16)
        lo = starts[bisect.bisect_right(starts, a) - 1]
        hi = starts[bisect.bisect_right(starts, lo)] if lo != starts[-1] else hi
    rows, tables = analyse(data, text, starts, lo, hi)
    if args.cls:
        keep = {a for s, a in sym.items() if re.search(r'__\d+%s(?:\b|[A-Z0-9P])' % re.escape(args.cls), s)
                or re.match(r'_\$_\d+%s$' % re.escape(args.cls), s)}
        rows = [r for r in rows if r[1] in keep]
        tables = {f: t for f, t in tables.items() if f in keep}
    funcs = sorted({r[1] for r in rows} | set(tables))
    resolved = sum(1 for r in rows if r[4] and r[4].startswith('arg'))
    print('%d reads in %d functions: %d into an argument+offset, %d into a stack buffer or other, %d unresolved'
          % (len(rows), len(funcs), resolved, sum(1 for r in rows if r[4] and not r[4].startswith('arg')),
             sum(1 for r in rows if not r[4])))
    by_func = defaultdict(list)
    for r in rows:
        by_func[r[1]].append(r)
    for f in funcs:
        name = a2s.get(f, 'func_%08X' % f)
        shown = [r for r in by_func[f] if args.all or (r[4] and r[4].startswith('arg'))]
        if not shown and not (args.tables and tables.get(f)):
            continue
        print('0x%08X %s' % (f, name))
        if args.tables:
            for t in tables.get(f, []):
                entries = keyword_table(data, t)
                print('    keywords @0x%08X: %s' % (t, ', '.join('%d=%s' % kv for kv in entries) or '?'))
        for pc, _, typ, key, dest, raw in shown:
            print('    %-6s %-20s -> %s' % (typ, '"%s"' % key if key else '?', dest or 'unresolved: ' + raw))
    return 0


if __name__ == '__main__':
    sys.exit(main())
