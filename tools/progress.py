#!/usr/bin/env python3
"""Compute the README progress numbers and optionally write them into README.md.

Usage:
  progress.py [--write] [--no-rebuild]

Builds every source like verify.py and every vtable probe like verify_vtables.py, then prints:
- the "Decompilation Progress" table of README.md (between the progress:begin/end markers),
- matched bytes per region of the binary map (game code, IVP physics, runtime libraries).

--write      replace the table in README.md (refused while any check fails)
--no-rebuild skip rebuild/rebuild.py; the relink row is then copied from the current README

WHIRL_COMPILERS, WHIRL_SLUS and WHIRL_SPLIT default to ../whirl-tour-work like check_all.py.
"""
import argparse
import math
import os
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import extract_rtti  # noqa: E402
import verify  # noqa: E402
import verify_vtables  # noqa: E402

README = verify.ROOT / 'README.md'
BEGIN, END = '<!-- progress:begin -->', '<!-- progress:end -->'
# Binary map of SLUS_204.89 .text (README "Binary .text Map"); the last region runs to the end of .text.
REGIONS = [('Game code', 0x00100000, 0x001C62D0),
           ('Physics engine (IVP_*)', 0x001C62D0, 0x00228F30),
           ('Runtime & system libraries', 0x00228F30, None)]
# Total functions in .text (splat split); RTTI classes and checkable vtable slots are derived from the binary.
TOTAL_FUNCTIONS = 7125


def derive_rtti_denominators(slus_path):
    """Derive (total_classes, total_checkable_vtable_slots) directly from SLUS_204.89."""
    data = Path(slus_path).read_bytes()
    text = data[extract_rtti.TEXT_OFFSET:extract_rtti.TEXT_OFFSET + extract_rtti.TEXT_SIZE]
    rodata = data[extract_rtti.RODATA_OFFSET:extract_rtti.RODATA_OFFSET + extract_rtti.RODATA_SIZE]
    tfs = extract_rtti.find_tf_functions(text, extract_rtti.find_rtti_strings(rodata))
    vtables = extract_rtti.find_vtables(rodata, tfs)
    # Approximate total virtual method slots across all RTTI vtables (excluding only pure-base slot-1 destructors)
    slots = sum(len(vt['slots']) - (0 if vt['bases'] else 1) for vt in vtables)
    return len(vtables), slots


def bar(percent):
    blocks = min(20, max(0, math.ceil(percent / 5.0 - 1e-9)))
    return '`' + '█' * blocks + '░' * (20 - blocks) + '`'


def run_verify(compilers, slus_path):
    slus = verify.Elf32(slus_path)
    _, text = slus.section('.text')
    game, base = slus.contents(text), text['addr']
    addresses = verify.load_symbols()
    sources = sorted(verify.SRC.rglob('*.cpp'))
    objects = verify.build_all(lambda s: verify.build(compilers, s, []), sources)
    found, problems = [], 0
    for obj in objects:
        problems += len(verify.compare(obj, game, base, addresses, False, found)[2])
    return slus, base, len(game), addresses, found, problems


def run_vtables(compilers, slus, addresses):
    tables = verify_vtables.load_tables()
    objects = verify.build_all(lambda t: verify_vtables.build_probe(compilers, t[1], t[2]), tables)
    slots = unchecked = problems = 0
    for (address, name, _), obj in zip(tables, objects):
        c, u, p = verify_vtables.check(address, name, verify_vtables.probe_table(obj), slus, addresses, False)
        slots, unchecked, problems = slots + c, unchecked + u, problems + len(p)
    return slots, len(tables), unchecked, problems


def run_rebuild(env):
    p = subprocess.run([sys.executable, 'rebuild/rebuild.py', '-q'], cwd=verify.ROOT, env=env,
                       text=True, capture_output=True)
    m = re.search(r'^MATCH:.*?(\d+) C\+\+ functions', p.stdout, re.M)
    if p.returncode != 0 or not m:
        return None
    return int(m.group(1))


def current_block():
    text = README.read_text()
    if BEGIN not in text or END not in text:
        raise verify.VerifyError('README.md has no %s ... %s block' % (BEGIN, END))
    return text, text[text.index(BEGIN) + len(BEGIN):text.index(END)]


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--write', action='store_true', help='update the table in README.md')
    ap.add_argument('--no-rebuild', action='store_true', help='skip rebuild.py and keep the README relink row')
    args = ap.parse_args()
    work = verify.ROOT.parent / 'whirl-tour-work'
    os.environ.setdefault('WHIRL_COMPILERS', str(work / 'compilers'))
    os.environ.setdefault('WHIRL_SLUS', str(work / 'SLUS_204.89'))
    os.environ.setdefault('WHIRL_SPLIT', str(work / 'split'))
    compilers, slus_path = os.environ['WHIRL_COMPILERS'], os.environ['WHIRL_SLUS']
    try:
        verify.enter_sandbox()
        verify.check_target(slus_path)
        slus, base, text_size, addresses, found, bad_functions = run_verify(compilers, slus_path)
        slots, classes, unchecked, bad_slots = run_vtables(compilers, slus, addresses)
        total_classes, total_slots = derive_rtti_denominators(slus_path)
        readme, block = current_block()
    except verify.VerifyError as e:
        print('progress: ' + str(e), file=sys.stderr)
        return 2

    total = sum(size for _, size, _ in found)
    end_of_text = base + text_size
    per_region = []
    for name, lo, hi in REGIONS:
        hi = hi or end_of_text
        per_region.append((name, lo, hi, sum(size for a, size, _ in found if lo <= a < hi)))
    game_name, game_lo, game_hi, game_bytes = per_region[0]

    if args.no_rebuild:
        old = [l for l in block.splitlines() if l.startswith('| **Full binary relink')]
        relink = old[0] if old else '| **Full binary relink (`rebuild.py`)** | not run | | | |'
        rebuild_ok = True
    else:
        linked = run_rebuild(dict(os.environ))
        rebuild_ok = linked is not None
        sha = (verify.TARGET_SHA1.read_text().split()[0])
        relink = ('| **Full binary relink (`rebuild.py`)** | **%d linked** | `%s...%s` | **SHA-1 MATCH** | %s |'
                  % (linked, sha[:8], sha[-4:], bar(100)) if rebuild_ok
                  else '| **Full binary relink (`rebuild.py`)** | **FAILED** | | | |')

    def row(label, value, denominator, part, whole):
        pct = 100.0 * part / whole
        return '| %s | **%s** | %s | **%.3f%%** | %s |' % (label, value, denominator, pct, bar(pct))

    rows = [
        '| Metric | Matched / Confirmed | Total in `.text` | Share | Progress |',
        '| :--- | ---: | ---: | ---: | :--- |',
        row('**Total `.text` bytes**', '{:,} B'.format(total), '{:,} B'.format(text_size), total, text_size),
        row('**Game logic bytes** (`0x%X..0x%X`)' % (game_lo, game_hi - 1), '{:,} B'.format(game_bytes),
            '{:,} B'.format(game_hi - game_lo), game_bytes, game_hi - game_lo),
        row('**Matched functions (`verify.py`)**', str(len(found)), '~{:,}'.format(TOTAL_FUNCTIONS),
            len(found), TOTAL_FUNCTIONS),
        row('**Confirmed vtable slots (`verify_vtables.py`)**', str(slots), '~{:,}'.format(total_slots),
            slots, total_slots),
        row('**Confirmed RTTI classes (`vtables.txt`)**', str(classes), str(total_classes), classes, total_classes),
        relink,
    ]
    table = '\n'.join(rows)
    print(table)
    print()
    for name, lo, hi, nbytes in per_region:
        print('%-28s 0x%08X..0x%08X  %7s B of %9s B  %.3f%%'
              % (name, lo, hi - 1, '{:,}'.format(nbytes), '{:,}'.format(hi - lo), 100.0 * nbytes / (hi - lo)))
    failures = []
    if bad_functions:
        failures.append('%d verify problems' % bad_functions)
    if bad_slots:
        failures.append('%d vtable problems' % bad_slots)
    if unchecked:
        print('note: %d vtable slots unchecked (no address in config/symbols.txt yet)' % unchecked)
    if not rebuild_ok:
        failures.append('rebuild.py did not reproduce the SHA-1')
    if failures:
        print('progress: not clean (%s); run tools/check_all.py' % '; '.join(failures), file=sys.stderr)
        return 1
    if args.write:
        new = readme.replace(BEGIN + block + END, BEGIN + '\n' + table + '\n' + END)
        if new != readme:
            README.write_text(new)
            print('README.md updated')
        else:
            print('README.md already up to date')
    return 0


if __name__ == '__main__':
    sys.exit(main())
