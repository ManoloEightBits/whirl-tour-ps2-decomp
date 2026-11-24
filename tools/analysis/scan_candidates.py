#!/usr/bin/env python3
"""Scan SLUS_204.89 for unmatched functions by complexity and vtable membership.

Usage:
  scan_candidates.py --level {1,2,3} [--limit N] [--class CLASS]
    --level 1: Pure leaf getters/setters/constants (2..6 instructions, 0 calls)
    --level 2: Simple delegation wrappers (4..12 instructions, 1 call)
    --level 3: Unmatched virtual methods referenced by any of the 182 RTTI vtables, sorted by size
"""
import argparse
import sys
from pathlib import Path

from whirl_paths import REPO  # noqa: E402,F401

import extract_rtti as e  # noqa: E402
import inspect_tu as itu  # noqa: E402
import verify  # noqa: E402

GAME_END = 0x00228F30  # End of game + IVP code (before static SDK/libc libraries)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--level', type=int, choices=(1, 2, 3), default=3,
                    help='1=leaf getters/setters, 2=single-call wrappers, 3=unmatched vtable methods')
    ap.add_argument('--limit', type=int, default=40, help='max results to display')
    ap.add_argument('--class', dest='class_filter', help='filter by class name substring')
    args = ap.parse_args()

    _, text, rodata = itu.load_binary()
    rtti_strings = e.find_rtti_strings(rodata)
    tf_funcs = e.find_tf_functions(text, rtti_strings)
    vtables = e.find_vtables(rodata, tf_funcs)
    vtable_addrs = {v['vtable_addr']: v['vtable_symbol'] for v in vtables}

    sym_to_addr = verify.load_symbols()
    addr_to_sym = {a: s for s, a in sym_to_addr.items()}
    starts = [s for s in itu.parse_func_boundaries(text) if e.TEXT_BASE <= s < GAME_END]
    start_idx = {s: i for i, s in enumerate(starts)}

    def end_of(addr):
        idx = start_idx.get(addr)
        if idx is not None and idx + 1 < len(starts):
            return min(starts[idx + 1], addr + 0x2000)
        for s in starts:
            if s > addr:
                return min(s, addr + 0x2000)
        return min(GAME_END, addr + 0x400)

    # Map every function address to the nearest RTTI __tf function for TU context
    tf_sorted = sorted((t['tf_addr'], t['class_name']) for t in tf_funcs.values())

    def nearest_class(addr):
        best_dist, best_name = 0x100000, '?'
        for taddr, cname in tf_sorted:
            d = abs(addr - taddr)
            if d < best_dist:
                best_dist, best_name = d, cname
        return '%s(%+d)' % (best_name, addr - next(t for t, c in tf_sorted if c == best_name))

    if args.level == 3:
        rows = []
        seen_funcs = set()
        for vt in vtables:
            cname = vt['class_name']
            if args.class_filter and args.class_filter.lower() not in cname.lower():
                continue
            for slot in vt['slots']:
                faddr = slot['func']
                if faddr in addr_to_sym or faddr in seen_funcs or faddr >= GAME_END:
                    continue
                seen_funcs.add(faddr)
                info = itu.analyze_function(faddr, end_of(faddr), text, rodata, addr_to_sym, vtable_addrs)
                rows.append((info['insns'], faddr, cname, slot['slot'], info))
        rows.sort(key=lambda r: (r[0], r[1]))
        print('Found %d unmatched vtable methods (showing top %d by shortest instruction count):'
              % (len(rows), min(args.limit, len(rows))))
        for insns, faddr, cname, slot_num, info in rows[:args.limit]:
            sug = (' -> ' + info['suggestion']) if info['suggestion'] else ''
            print('  0x%08X [%3d insns] %-28s slot %2d%s' % (faddr, insns, cname, slot_num, sug))
        return 0

    rows = []
    for addr in starts:
        if addr in addr_to_sym:
            continue
        near = nearest_class(addr)
        if args.class_filter and args.class_filter.lower() not in near.lower():
            continue
        info = itu.analyze_function(addr, end_of(addr), text, rodata, addr_to_sym, vtable_addrs)
        if args.level == 1 and 2 <= info['insns'] <= 6 and not info['callees'] and info['suggestion']:
            rows.append((info['insns'], addr, near, info))
        elif args.level == 2 and 4 <= info['insns'] <= 12 and len(info['callees']) == 1:
            rows.append((info['insns'], addr, near, info))

    print('Found %d level-%d candidates (showing %d):' % (len(rows), args.level, min(args.limit, len(rows))))
    for insns, addr, near, info in rows[:args.limit]:
        sug = info['suggestion'] or ('calls %s' % info['callees'][0][1])
        print('  0x%08X [%2d insns] near %-26s : %s' % (addr, insns, near, sug))
    return 0


if __name__ == '__main__':
    sys.exit(main())
