#!/usr/bin/env python3
"""What is left to match: unmatched code by region, function size and area of the binary.

Usage:
  coverage.py [--region game|physics|runtime|all] [--top N] [--block KB]
  coverage.py --map FILE [--block KB]

For each region of .text (the README map) it prints matched and unmatched functions and bytes,
how many unmatched functions sit in an RTTI vtable,
how the unmatched bytes split by function size, the largest unmatched functions, and the address
blocks with the most unmatched bytes (labelled with the RTTI classes whose __tf is in or before
the block, a rough guide to which classes live there).

With --map it writes a Markdown table instead: one row per block of the whole .text with the share
matched, the RTTI classes whose __tf is in it, the repository files with matched functions in it,
and the keywords its code uses (short identifier-like strings, such as script keys) as hints of what
the code does. docs/MAP.md is generated this way.
"""
import argparse
import bisect
import collections
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

import inspect_tu as itu  # noqa: E402
import extract_rtti as e  # noqa: E402
import verify  # noqa: E402
import whirl_paths  # noqa: E402

REGIONS = {'game': ('Game code', 0x00100000, 0x001C62D0),
           'physics': ('Physics engine (IVP_*)', 0x001C62D0, 0x00228F30),
           'runtime': ('Runtime & system libraries', 0x00228F30, e.TEXT_BASE + e.TEXT_SIZE)}
BUCKETS = [(16, '<= 16 B'), (64, '17-64 B'), (256, '65-256 B'), (1024, '257 B-1 KB'),
           (4096, '1-4 KB'), (1 << 30, '> 4 KB')]


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--region', choices=list(REGIONS) + ['all'], default='all')
    ap.add_argument('--top', type=int, default=10, help='rows in the largest-functions and block lists')
    ap.add_argument('--block', type=int, default=16, help='block size in KB for the area list')
    ap.add_argument('--map', type=Path, help='write the per-block Markdown map to this file')
    args = ap.parse_args()

    _, text, rodata = itu.load_binary()
    tf_funcs = e.find_tf_functions(text, e.find_rtti_strings(rodata))
    virtual = {slot['func'] for vt in e.find_vtables(rodata, tf_funcs) for slot in vt['slots']}
    tfs = sorted((t['tf_addr'], t['class_name']) for t in tf_funcs.values())
    tf_addrs = [a for a, _ in tfs]
    addr_to_sym = {a: s for s, a in verify.load_symbols().items()}
    matched = whirl_paths.matched_addresses(addr_to_sym)
    starts = itu.parse_func_boundaries(text)
    text_end = e.TEXT_BASE + e.TEXT_SIZE
    sizes = {a: (starts[i + 1] if i + 1 < len(starts) else text_end) - a for i, a in enumerate(starts)}

    def classes_near(lo, hi):
        inside = [c for a, c in tfs if lo <= a < hi]
        if inside:
            return ', '.join(inside[:3]) + (' +%d' % (len(inside) - 3) if len(inside) > 3 else '')
        i = bisect.bisect_right(tf_addrs, lo)
        return ('after ' + tfs[i - 1][1]) if i else '-'

    if args.map:
        write_map(args.map, args.block * 1024, text, rodata, starts, sizes, matched, tfs, addr_to_sym)
        print('wrote %s' % args.map)
        return 0

    keys = list(REGIONS) if args.region == 'all' else [args.region]
    for key in keys:
        name, lo, hi = REGIONS[key]
        funcs = [a for a in starts if lo <= a < hi]
        done = [a for a in funcs if a in matched]
        left = [a for a in funcs if a not in matched]
        total_b = sum(sizes[a] for a in funcs)
        done_b = sum(sizes[a] for a in done)
        print('=== %s 0x%08X..0x%08X: %d/%d functions, %s/%s bytes matched (%.2f%%) ==='
              % (name, lo, hi - 1, len(done), len(funcs), '{:,}'.format(done_b), '{:,}'.format(total_b),
                 100.0 * done_b / total_b if total_b else 0))
        vleft = [a for a in left if a in virtual]
        print('  unmatched functions in an RTTI vtable: %d (%s bytes); the rest have no vtable to name them'
              % (len(vleft), '{:,}'.format(sum(sizes[a] for a in vleft))))
        print('  unmatched by function size:')
        left_b = sum(sizes[a] for a in left)
        prev = 0
        for limit, label in BUCKETS:
            group = [a for a in left if prev < sizes[a] <= limit]
            gb = sum(sizes[a] for a in group)
            print('    %-11s %5d functions  %9s bytes  %5.1f%% of what is left'
                  % (label, len(group), '{:,}'.format(gb), 100.0 * gb / left_b if left_b else 0))
            prev = limit
        print('  largest unmatched functions:')
        for a in sorted(left, key=lambda a: -sizes[a])[:args.top]:
            print('    0x%08X %7s B  %s' % (a, '{:,}'.format(sizes[a]), classes_near(a, a + sizes[a])))
        block = args.block * 1024
        per_block = {}
        for a in left:
            b = (a - lo) // block
            per_block[b] = per_block.get(b, 0) + sizes[a]
        print('  %d KB blocks with the most unmatched bytes:' % args.block)
        for b, nb in sorted(per_block.items(), key=lambda kv: -kv[1])[:args.top]:
            blo = lo + b * block
            print('    0x%08X..0x%08X %8s B  %s' % (blo, min(blo + block, hi) - 1, '{:,}'.format(nb),
                                                    classes_near(blo, blo + block)))
    return 0


KEYWORD = re.compile(r'[a-z][a-z0-9_]*(/[a-z0-9_]+)?$')


def source_files():
    """Map each name in config/symbols.txt to the file of its '# Section (src/...)' header."""
    out, current = {}, None
    for line in (verify.ROOT / 'config' / 'symbols.txt').read_text().splitlines():
        m = re.match(r'#.*\((src/[^)]*?)\)', line)
        if m:
            current = [Path(f.strip()).name for f in m.group(1).split(',')][0]
            continue
        parts = line.split()
        if current and len(parts) == 2 and parts[0].startswith('0x'):
            out[parts[1]] = current
    return out


def write_map(path, block, text, rodata, starts, sizes, matched, tfs, addr_to_sym):
    files = source_files()
    vtable_addrs = {}
    rows = []
    for key in REGIONS:
        name, lo, hi = REGIONS[key]
        rows.append('\n## %s (`0x%08X..0x%08X`)\n' % (name, lo, hi - 1))
        rows.append('| Block | Matched | Unmatched | RTTI classes | Our files | Keywords in its code |')
        rows.append('| :--- | ---: | ---: | :--- | :--- | :--- |')
        for blo in range(lo, hi, block):
            bhi = min(blo + block, hi)
            funcs = [a for a in starts if blo <= a < bhi]
            total = sum(sizes[a] for a in funcs)
            done = sum(sizes[a] for a in funcs if a in matched)
            classes = [c for a, c in tfs if blo <= a < bhi and re.fullmatch(r'[A-Za-z_]\w*', c)]
            ours = sorted({files[addr_to_sym[a]] for a in funcs if a in matched and addr_to_sym.get(a) in files})
            words = collections.Counter()
            for a in funcs:
                info = itu.analyze_function(a, a + sizes[a], text, rodata, addr_to_sym, vtable_addrs)
                for _, s in info['strings']:
                    if 3 <= len(s) <= 24 and KEYWORD.match(s):
                        words[s] += 1
            pct = 100.0 * done / total if total else 0
            bar = '█' * int(round(pct / 10)) + '░' * (10 - int(round(pct / 10)))
            rows.append('| `0x%08X` | `%s` %.0f%% | %s B | %s | %s | %s |' % (
                blo, bar, pct, '{:,}'.format(total - done),
                ', '.join(classes[:6]) + (' +%d' % (len(classes) - 6) if len(classes) > 6 else '') or '-',
                ', '.join('`%s`' % f for f in ours) or '-',
                ', '.join('`%s`' % w for w, _ in words.most_common(6)) or '-'))
    header = ('# Binary map\n\nGenerated by `tools/analysis/coverage.py --map docs/MAP.md`: one row per %d KB block of '
              '`.text`. *Matched* is the share of the block\'s bytes in matched functions; *RTTI classes* are the '
              'classes whose `__tf` is in the block; *Our files* are the repository files with matched functions '
              'there; *Keywords* are short identifier-like strings the block\'s code refers to (script keys, event '
              'names), the best hint of what code without a vtable does. Regenerate it after a batch of matches.\n'
              % (block // 1024))
    path.write_text(header + '\n'.join(rows) + '\n')


if __name__ == '__main__':
    sys.exit(main())
