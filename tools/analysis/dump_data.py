#!/usr/bin/env python3
"""Show data of the game at an address: words, a vtable, or a string.

Usage:
  dump_data.py ADDR [-n N]        N words (default 8), each with what it points to
  dump_data.py ADDR --vtable      vtable entries from slot 0 (the address given in config/vtables.txt)
  dump_data.py ADDR --string      the NUL-terminated string at ADDR

A word that is a known address shows its name from config/symbols.txt, and whether it matches
(build/matched.txt, see whirl_paths.matched_addresses). A word that points at printable text shows
the text, a word inside a function shows the nearest symbol before it plus the offset (jump
tables), and a word that reads as an ordinary float shows the float. A vtable entry is
{s16 delta, s16 index, function}; the listing stops at the next vtable's all-zero header entry.

Examples:
  dump_data.py 284090 --vtable     # Global_Phantom_Listener: __tf and its three slots
  dump_data.py 25A230 -n 20        # a keyword table: {id, "name"} pairs
  dump_data.py 284460 -n 8         # a switch's jump table
"""
import argparse
import math
import struct
import sys

from whirl_paths import SLUS  # noqa: E402
import whirl_paths  # noqa: E402

import verify  # noqa: E402

SHT_NOBITS = 8


class Image:
    def __init__(self, path):
        self.elf = verify.Elf32(path)
        self.ranges = [(s['addr'], s['addr'] + s['size'], s['offset'], s['name']) for s in self.elf.sections
                       if s['addr'] and s['size'] and s['type'] != SHT_NOBITS]

    def offset(self, addr):
        for lo, hi, off, _ in self.ranges:
            if lo <= addr < hi:
                return off + addr - lo
        return None

    def section_of(self, addr):
        for lo, hi, _, name in self.ranges:
            if lo <= addr < hi:
                return name
        return None

    def word(self, addr):
        off = self.offset(addr)
        if off is None:
            raise SystemExit('dump_data: 0x%08X is not in any loaded section' % addr)
        return struct.unpack_from('<I', self.elf.data, off)[0]

    def string(self, addr, limit=80):
        off = self.offset(addr)
        if off is None:
            return None
        end = self.elf.data.find(b'\0', off, off + limit + 1)
        if end < 0:
            return None
        raw = self.elf.data[off:end]
        if len(raw) < 2 or not all(32 <= b < 127 for b in raw):
            return None
        return raw.decode('ascii')


def describe(image, word, names, matched):
    if word in names:
        return '%s%s' % (names[word], '' if word in matched else ' (not matched)')
    section = image.section_of(word)
    if section == '.text':
        # Inside a function (a jump-table target, for example): name it by the nearest symbol before.
        starts = sorted(a for a in names if a <= word)
        if starts and word - starts[-1] < 0x2000:
            return '%s+0x%X' % (names[starts[-1]], word - starts[-1])
        return '-> .text'
    if section:
        text = image.string(word)
        if text is not None:
            return '"%s"' % text
        return '-> %s' % section
    f = struct.unpack('<f', struct.pack('<I', word))[0]
    if word and not math.isnan(f) and 1e-4 <= abs(f) <= 1e7:
        return '%gf' % f
    return ''


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('addr', help='address in hex (0x optional)')
    ap.add_argument('-n', type=int, default=None, help='words (or vtable slots) to show')
    ap.add_argument('--vtable', action='store_true', help='read 8-byte vtable entries')
    ap.add_argument('--string', action='store_true', help='print the string at the address')
    args = ap.parse_args()

    addr = int(args.addr, 16)
    image = Image(SLUS)
    names = {a: s for s, a in verify.load_symbols().items()}
    matched = whirl_paths.matched_addresses(names)

    if args.string:
        print(image.string(addr, limit=4096) or '(no printable string at 0x%08X)' % addr)
        return 0
    if args.vtable:
        for slot in range(args.n or 64):
            a = addr + 8 * slot
            off = image.offset(a)
            delta, index, func = struct.unpack_from('<hhI', image.elf.data, off)
            if slot and not (delta or index or func):
                break
            what = describe(image, func, names, matched) if func else '(null)'
            print('  slot %2d  0x%08X  %s' % (slot, func, what))
        return 0
    for i in range(args.n or 8):
        a = addr + 4 * i
        w = image.word(a)
        print('  0x%08X: 0x%08X  %s' % (a, w, describe(image, w, names, matched)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
