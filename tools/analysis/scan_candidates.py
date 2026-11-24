#!/usr/bin/env python3
"""Scan SLUS_204.89 for unmatched functions by complexity, vtable membership, and structural twins.

Usage:
  scan_candidates.py --level {1,2,3} [--limit N] [--class CLASS]
    --level 1: Pure leaf getters/setters/constants (2..6 instructions, 0 calls)
    --level 2: Simple delegation wrappers (4..12 instructions, 1 call)
    --level 3: Unmatched virtual methods referenced by any RTTI vtable, sorted by size
  scan_candidates.py --twins [--limit N] [--class CLASS]
    --twins:   Group unmatched functions by relocation/immediate-normalized skeleton (including
               already-matched siblings, so one matched exemplar can be ported to its twins)
"""
import argparse
import struct
import sys
from pathlib import Path

from whirl_paths import REPO  # noqa: E402,F401
import whirl_paths  # noqa: E402

import extract_rtti as e  # noqa: E402
import inspect_tu as itu  # noqa: E402
import verify  # noqa: E402

GAME_END = 0x00228F30  # End of game + IVP code (before static SDK/libc libraries)


def skeleton_key(words):
    """Normalize jal targets and 16-bit load/store/arith immediates so structural twins share a key."""
    out = []
    for w in words:
        op = w >> 26
        if op in (2, 3):  # j, jal
            out.append(w & 0xFC000000)
        elif op in (8, 9, 10, 11, 12, 13, 14, 15, 32, 33, 35, 36, 37, 40, 41, 43, 49, 57):
            # I-type arithmetic/lui/loads/stores: keep opcode, rs, rt; mask immediate
            out.append(w & 0xFFFF0000)
        else:
            out.append(w)
    return tuple(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--level', type=int, choices=(1, 2, 3), default=3,
                    help='1=leaf getters/setters, 2=single-call wrappers, 3=unmatched vtable methods')
    ap.add_argument('--twins', action='store_true',
                    help='group unmatched functions by normalized instruction skeleton (structural families)')
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
    matched = whirl_paths.matched_addresses(addr_to_sym)
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

    if args.twins:
        groups = {}
        for addr in starts:
            end_a = end_of(addr)
            start_off, end_off = addr - e.TEXT_BASE, end_a - e.TEXT_BASE
            words = list(struct.unpack_from('<%dI' % ((end_off - start_off) // 4), text, start_off))
            while len(words) > 2 and words[-1] == 0 and words[-3] == 0x03E00008:
                words.pop()
            if len(words) < 4:
                continue
            groups.setdefault(skeleton_key(words), []).append((addr, len(words)))
        clusters = []
        for key, members in groups.items():
            unmatched = [a for a, _ in members if a not in matched]
            if not unmatched or len(members) < 2:
                continue
            if args.class_filter and not any(args.class_filter.lower() in nearest_class(a).lower() for a in unmatched):
                continue
            banked = [a for a, _ in members if a in matched]
            clusters.append((len(unmatched), len(banked), members[0][1], unmatched, banked))
        clusters.sort(key=lambda c: (not c[4], -c[0], c[2]))  # families with a matched sibling first
        print('Found %d structural twin families with unmatched members (showing top %d):'
              % (len(clusters), min(args.limit, len(clusters))))
        for n_unm, n_bnk, insns, unmatched, banked in clusters[:args.limit]:
            bnk_str = (' [matched sibling: %s]' % addr_to_sym.get(banked[0], '0x%08X' % banked[0])) if banked else ''
            sample = ', '.join('0x%08X(%s)' % (a, nearest_class(a)) for a in unmatched[:4])
            more = (' +%d more' % (n_unm - 4)) if n_unm > 4 else ''
            print('  [%3d insns] %2d unmatched, %2d matched%s: %s%s'
                  % (insns, n_unm, n_bnk, bnk_str, sample, more))
        return 0

    if args.level == 3:
        rows = []
        seen_funcs = set()
        for vt in vtables:
            cname = vt['class_name']
            if args.class_filter and args.class_filter.lower() not in cname.lower():
                continue
            for slot in vt['slots']:
                faddr = slot['func']
                if faddr in matched or faddr in seen_funcs or faddr >= GAME_END:
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
        if addr in matched:
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
