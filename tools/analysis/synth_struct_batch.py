#!/usr/bin/env python3
"""Synthesize minimal UnkObj<ADDR> structs for m2c match-sweep drafts that only fail draft_to_cpp
because they access fields on arg0 (->unkXX), then emit and verify matching ones.

Usage:
  synth_struct_batch.py scan [--region game|physics|all] [--range A B] [--min-size N] [--max-size N]
  synth_struct_batch.py emit ADDR... [--apply]
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

import whirl_paths
from whirl_paths import REPO, COMPILERS
import verify
import m2c_sweep
import draft_to_cpp as dtc

DRAFTS = m2c_sweep.OUT / 'drafts'
BLOCKS = REPO / 'src' / 'game' / 'blocks'
SYMS = REPO / 'config' / 'symbols.txt'
SOUND_LIBRARY = (0x001A5998, 0x001AC000)


def infer_arg0_struct(addr, draft_text):
    """If draft_text only accesses ->unkXX on arg0 (and has no blockers), return (struct_def, new_func) or (None, reason)."""
    if 'M2C_ERROR' in draft_text:
        return None, 'M2C_ERROR'
    if '__ti' in draft_text or '__rtti_' in draft_text or '_vt$' in draft_text:
        return None, 'rtti/vtable'
    if re.search(r'\bD_[0-9A-Fa-f]{6,8}\b', draft_text):
        return None, 'raw D_ global'
    if re.search(r'\bdata_[0-9A-Fa-f]{6,8}\b', draft_text):
        return None, 'data_ global'
    # Check all M2C_FIELD(base, type *, 0xOFF) accesses
    fields = re.findall(r'M2C_FIELD\(\s*([A-Za-z_]\w*)\s*,\s*([^,]+?)\s*,\s*0x([0-9A-Fa-f]+)\s*\)', draft_text)
    if not fields:
        return None, 'no M2C_FIELD'
    bad_bases = {b for b, _, _ in fields if b != 'arg0'}
    if bad_bases:
        return None, 'other base: ' + ','.join(sorted(bad_bases))
    lines = draft_text.splitlines()
    sig_idx = next((i for i, l in enumerate(lines) if f'func_{addr:08X}' in l or '(' in l), 0)
    sig = lines[sig_idx].strip()
    if 'void *arg0' not in sig:
        return None, 'arg0 not void*'
    body_only = '\n'.join(lines[sig_idx + 1:])
    if re.search(r'\*\s*arg0\b', body_only):
        return None, '*arg0'
    if '?' in draft_text:
        return None, 'unknown ? type'

    # Infer field types at each offset from M2C_FIELD type argument
    TYPE_MAP = {
        'f32 *': ('f32', 4, 4),
        'f64 *': ('f64', 8, 8),
        's16 *': ('s16', 2, 2),
        'u16 *': ('u16', 2, 2),
        's8 *': ('s8', 1, 1),
        'u8 *': ('u8', 1, 1),
        'void **': ('void *', 4, 4),
        'u32 *': ('u32', 4, 4),
        's32 *': ('int', 4, 4),
    }
    offsets = {}
    for _, ptr_type, hex_off in fields:
        off = int(hex_off, 16)
        if off < 0:
            return None, 'negative offset'
        if off in offsets:
            continue
        pt = ' '.join(ptr_type.split())
        if pt in TYPE_MAP:
            offsets[off] = TYPE_MAP[pt]
        elif pt.endswith('**'):
            offsets[off] = ('void *', 4, 4)
        else:
            offsets[off] = ('int', 4, 4)

    # Check alignment/overlap
    sname = f'UnkObj{addr:06X}'
    cur = 0
    s_lines = [f'struct {sname}', '{']
    for off in sorted(offsets):
        typ, sz, al = offsets[off]
        if off < cur or (off % al) != 0:
            return None, f'overlap/align at 0x{off:X}'
        if off > cur:
            s_lines.append(f'    char pad{cur:02X}[0x{off - cur:X}];')
        fname = f'mField{off:02X}'
        if typ == 'void *':
            s_lines.append(f'    void *{fname}; // 0x{off:02X}')
        else:
            s_lines.append(f'    {typ} {fname}; // 0x{off:02X}')
        cur = off + sz
    s_lines.append('};')

    body = '\n'.join(lines)
    body = re.sub(r'\bvoid \*arg0\b', f'{sname} *arg0', body)
    body = re.sub(r'\bNULL\b', '0', body)
    body = re.sub(r'\bs32\b', 'int', body)
    body = re.sub(
        r'M2C_FIELD\(\s*arg0\s*,\s*[^,]+?\s*,\s*0x([0-9A-Fa-f]+)\s*\)',
        lambda m: f'arg0->mField{int(m.group(1), 16):02X}',
        body,
    )
    return '\n'.join(s_lines), body


def load_candidates(args):
    sym_to_addr = verify.load_symbols()
    addr_to_sym = {a: s for s, a in sym_to_addr.items()}
    matched = whirl_paths.matched_addresses(addr_to_sym)
    rows = m2c_sweep.load_results()
    lo, hi = (0, 0xFFFFFFFF)
    if args.range:
        lo, hi = int(args.range[0], 16), int(args.range[1], 16)
    elif args.region == 'game':
        lo, hi = 0x00100000, 0x001C62D0
    elif args.region == 'physics':
        lo, hi = 0x001C62D0, 0x00228F30

    out = []
    for addr in sorted(rows):
        row = rows[addr]
        if addr in matched or not (lo <= addr < hi):
            continue
        if row['status'] != args.status:
            continue
        if addr % 8 == 4 or (SOUND_LIBRARY[0] <= addr < SOUND_LIBRARY[1]):
            continue
        if addr in addr_to_sym:
            continue
        sz = int(row['size'])
        if sz < args.min_size or (args.max_size and sz > args.max_size):
            continue
        dp = DRAFTS / f'{addr:08X}.c'
        if not dp.exists():
            continue
        sdef, body = infer_arg0_struct(addr, dp.read_text())
        out.append((addr, sz, sdef, body))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = ap.add_subparsers(dest='cmd', required=True)
    p_scan = sub.add_parser('scan')
    p_scan.add_argument('--region', choices=['game', 'physics', 'all'], default='game')
    p_scan.add_argument('--range', nargs=2)
    p_scan.add_argument('--status', default='match')
    p_scan.add_argument('--min-size', type=int, default=16)
    p_scan.add_argument('--max-size', type=int, default=0)
    p_scan.add_argument('--show', type=int, default=0, help='print synthesized C++ for top N')
    args = ap.parse_args()

    if args.cmd == 'scan':
        from collections import Counter
        cands = load_candidates(args)
        ok = [c for c in cands if c[2] is not None]
        skip = [c for c in cands if c[2] is None]
        reasons = Counter(c[3] for c in skip)
        print(f'{len(ok)} auto-synthesizable ({sum(c[1] for c in ok)} B), {len(skip)} skipped:')
        for r, n in reasons.most_common():
            print(f'  {n:4d}  {r}')
        for addr, sz, sdef, _ in sorted(ok, key=lambda x: -x[1])[:30]:
            print(f'  0x{addr:08X}  {sz:4d} B')
        if args.show:
            for addr, sz, sdef, body in sorted(ok, key=lambda x: -x[1])[:args.show]:
                print(f'\n// --- 0x{addr:08X} ({sz} B) ---')
                print(sdef)
                print(body)


if __name__ == '__main__':
    main()
