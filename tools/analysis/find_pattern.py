#!/usr/bin/env python3
"""Search the game's .text for a sequence of instructions.

Usage:
  find_pattern.py "<insn1>; <insn2>; ..." [--range START END] [--limit N] [--context N] [--count]

Each element is a Python regex matched against the start of one instruction's disassembly
(rabbitizer, R5900; spaces collapsed, e.g. "sw $v0, 0x4($a0)"). An element cannot end in the
middle of a mnemonic, so "sw" does not match "swc1" and "add" does not match "add.s".
Escape "$" as "\\$". "*" alone matches any one instruction.

Examples:
  find_pattern.py "sw; nop; jr \\$ra; nop"            # the do/while(0) return of DD_Event_Listener
  find_pattern.py "mtc1 \\$zero; nop; c\\." --count    # how often a hazard nop shows up
  find_pattern.py "lw \\$a0, 0xA8\\(" --range 117000 118000

Every hit is shown with the nearest preceding symbol from config/symbols.txt (only when it is
less than 0x400 bytes away, otherwise "?"). Run it with the analysis venv (tools/analysis/requirements.txt).
"""
import argparse
import bisect
import re
import struct
import sys
from pathlib import Path

import rabbitizer

from whirl_paths import REPO, SLUS  # noqa: E402,F401

import verify  # noqa: E402


def compile_pattern(text):
    out = []
    for part in text.split(';'):
        part = part.strip()
        if not part:
            continue
        out.append(None if part == '*' else re.compile('(?:%s)(?![\\w.])' % part))
    if not out:
        raise SystemExit('find_pattern: empty pattern')
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('pattern', help='instruction regexes separated by ";"')
    ap.add_argument('--range', nargs=2, metavar=('START', 'END'), type=lambda s: int(s, 16),
                    help='hex address range to search (default: all of .text)')
    ap.add_argument('--limit', type=int, default=30, help='hits to print (default 30)')
    ap.add_argument('--context', type=int, default=0, help='extra instructions to show before and after')
    ap.add_argument('--count', action='store_true', help='only print the number of hits')
    ap.add_argument('--slus', default=str(SLUS))
    args = ap.parse_args()

    slus = verify.Elf32(args.slus)
    _, text = slus.section('.text')
    code, base = slus.contents(text), text['addr']
    n = len(code) // 4
    lo, hi = 0, n
    if args.range:
        lo = max(0, (args.range[0] - base) // 4)
        hi = min(n, (args.range[1] - base) // 4)
    cache = {}

    def insn(i):
        s = cache.get(i)
        if s is None:
            w, = struct.unpack_from('<I', code, 4 * i)
            s = ' '.join(rabbitizer.Instruction(w, vram=base + 4 * i,
                                                category=rabbitizer.InstrCategory.R5900).disassemble().split())
            cache[i] = s
        return s

    pats = compile_pattern(args.pattern)
    by_addr = sorted((a, s) for s, a in verify.load_symbols().items() if base <= a < base + len(code))
    keys = [a for a, _ in by_addr]

    def where(addr):
        k = bisect.bisect_right(keys, addr) - 1
        if k >= 0 and addr - keys[k] < 0x400:
            return '%s+0x%X' % (by_addr[k][1], addr - keys[k])
        return '?'

    hits = []
    for i in range(lo, hi - len(pats) + 1):
        if all(p is None or p.match(insn(i + j)) for j, p in enumerate(pats)):
            hits.append(i)
    print('%d hits for "%s" in 0x%08X..0x%08X' % (len(hits), args.pattern, base + 4 * lo, base + 4 * hi))
    if args.count:
        return 0
    for i in hits[:args.limit]:
        addr = base + 4 * i
        print('0x%08X  %s' % (addr, where(addr)))
        for j in range(max(0, i - args.context), min(n, i + len(pats) + args.context)):
            mark = '>' if i <= j < i + len(pats) else ' '
            print('  %s %08X  %s' % (mark, base + 4 * j, insn(j)))
    if len(hits) > args.limit:
        print('... %d more (use --limit)' % (len(hits) - args.limit))
    return 0


if __name__ == '__main__':
    sys.exit(main())
