#!/usr/bin/env python3
"""Discover Translation Unit (TU) boundaries and class layouts in SLUS_204.89.

Usage:
  map_tus.py [--filter SUBSTR] [--class CLASS]

Groups RTTI classes whose __tf functions and .rodata vtables/strings sit next to each other
into probable original .cpp translation units, and infers class sizes (from `new` call sites
and vtable pointer offsets) and member field offsets.
"""
import argparse
import struct
import sys
from pathlib import Path

from whirl_paths import REPO  # noqa: E402,F401

import extract_rtti as e  # noqa: E402
import inspect_tu as itu  # noqa: E402
import verify  # noqa: E402


def infer_vptr_offset(vt, text):
    """Inspect slot 1 (typically virtual destructor) to find `sw $v0, OFFSET($this)` for vptr."""
    if not vt['slots']:
        return None
    dtor_addr = vt['slots'][0]['func']
    off = dtor_addr - e.TEXT_BASE
    if not (0 <= off <= len(text) - 64):
        return None
    words = struct.unpack_from('<16I', text, off)
    hi = vt['vtable_addr'] >> 16
    lo = vt['vtable_addr'] & 0xFFFF
    if lo & 0x8000:
        hi = (hi + 1) & 0xFFFF
    vreg = None
    for w in words:
        op, rs, rt, imm = w >> 26, (w >> 21) & 0x1F, (w >> 16) & 0x1F, w & 0xFFFF
        if op == 0x09 and imm == lo:  # addiu rt, rs, lo(vtable)
            vreg = rt
        elif op == 0x2B and vreg is not None and rt == vreg:  # sw vreg, simm($this)
            return itu.sext16(imm)
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--filter', help='only show TUs/classes matching substring')
    ap.add_argument('--class', dest='class_name', help='infer full field layout for a specific class')
    args = ap.parse_args()

    _, text, rodata = itu.load_binary()
    rtti_strings = e.find_rtti_strings(rodata)
    tf_funcs = e.find_tf_functions(text, rtti_strings)
    vtables = e.find_vtables(rodata, tf_funcs)
    vtable_addrs = {v['vtable_addr']: v['vtable_symbol'] for v in vtables}
    sym_to_addr = verify.load_symbols()
    addr_to_sym = {a: s for s, a in sym_to_addr.items()}
    starts = itu.parse_func_boundaries(text)

    def end_of(addr):
        for s in starts:
            if s > addr:
                return min(s, addr + 0x2000)
        return min(e.TEXT_BASE + e.TEXT_SIZE, addr + 0x400)

    if args.class_name:
        matches = [v for v in vtables if v['class_name'] == args.class_name]
        if not matches:
            print('Class %s not found in RTTI vtables' % args.class_name)
            return 1
        vt = matches[0]
        vptr_off = infer_vptr_offset(vt, text)
        bases = (' : public ' + ', public '.join(vt['bases'])) if vt['bases'] else ''
        print('=== Class Layout: %s%s ===' % (vt['class_name'], bases))
        print('vtable: 0x%08X  __tf: 0x%08X  __ti: 0x%08X  _vptr offset: %s'
              % (vt['vtable_addr'], vt['tf_addr'], vt['ti_addr'],
                 ('0x%02X' % vptr_off) if vptr_off is not None else 'unknown'))
        field_map = {}
        for slot in vt['slots']:
            info = itu.analyze_function(slot['func'], end_of(slot['func']), text, rodata, addr_to_sym, vtable_addrs)
            for off, kinds in info['this_reads'].items():
                field_map.setdefault(off, set()).update('R:' + k for k in kinds)
            for off, kinds in info['this_writes'].items():
                field_map.setdefault(off, set()).update('W:' + k for k in kinds)
        if field_map:
            print('Inferred $this field accesses across virtual methods:')
            for off in sorted(field_map):
                print('  +0x%03X : %s' % (off, ', '.join(sorted(field_map[off]))))
        return 0

    # Cluster vtables by proximity of their __tf functions in .text (within 0x900 bytes, or same __ti)
    vts_sorted = sorted(vtables, key=lambda v: v['tf_addr'])
    clusters = []
    for vt in vts_sorted:
        if clusters and (vt['tf_addr'] - clusters[-1][-1]['tf_addr'] <= 0x600
                         or (vt['ti_addr'] and vt['ti_addr'] == clusters[-1][-1]['ti_addr'])):
            clusters[-1].append(vt)
        else:
            clusters.append([vt])

    print('Discovered %d RTTI Translation Unit clusters across %d vtables:' % (len(clusters), len(vtables)))
    for idx, cl in enumerate(clusters, 1):
        names = [v['class_name'] for v in cl]
        if args.filter and not any(args.filter.lower() in n.lower() for n in names):
            continue
        tf_min = min(v['tf_addr'] for v in cl)
        tf_max = max(v['tf_addr'] for v in cl)
        local_slots = [s['func'] for v in cl for s in v['slots']
                       if tf_min - 0x4000 <= s['func'] <= tf_max + 0x4000]
        min_addr = min([tf_min] + local_slots)
        max_addr = max([tf_max] + local_slots)
        funcs_in_span = [s for s in starts if min_addr <= s <= max_addr]
        matched_in_span = sum(1 for s in funcs_in_span if s in addr_to_sym)
        vptrs = []
        for v in cl:
            vo = infer_vptr_offset(v, text)
            vptrs.append('%s(vptr=%s,%dv)' % (v['class_name'], ('+0x%X' % vo) if vo is not None else '?', len(v['slots'])))
        print('TU #%02d  0x%08X..0x%08X  [%2d/%2d funcs matched]  %s'
              % (idx, min_addr, max_addr, matched_in_span, len(funcs_in_span), ', '.join(vptrs)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
