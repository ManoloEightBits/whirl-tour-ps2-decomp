#!/usr/bin/env python3
"""Check the virtual function tables that include/ and src/ declare against the game's.

Usage: verify_vtables.py --compilers <dir> --slus <SLUS_204.89> [-v]

A byte match proves a function's code, not its name. A vtable is evidence for the name: if
class C declares its virtual functions in the right order, then each function's address must
sit in the matching slot of C's vtable in the game. config/vtables.txt lists the address of
each class's vtable and the header that declares the class.

Exit status is 0 only when no slot disagrees. Slots whose function has no address in
config/symbols.txt yet are counted as unchecked, and -v lists them with the game's address.
"""
import argparse
import os
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import verify  # noqa: E402

TABLES = verify.ROOT / 'config' / 'vtables.txt'
WORK = verify.BUILD / 'vtables'
ENTRY = 8  # {s16 delta, s16 index, pointer}


def load_tables():
    """config/vtables.txt -> [(address, class, header)]."""
    out = []
    for n, line in enumerate(TABLES.read_text().splitlines(), 1):
        parts = line.split('#')[0].split()
        if not parts:
            continue
        if len(parts) != 3:
            raise verify.VerifyError('%s:%d: expected "<address> <class> <header>"' % (TABLES.name, n))
        out.append((int(parts[0], 16), parts[1], parts[2]))
    return out


def build_probe(compilers_dir, name, header):
    """Compile a class derived from `name` and return the object holding its vtable."""
    WORK.mkdir(parents=True, exist_ok=True)
    tool_dir = Path(compilers_dir).resolve() / verify.COMPILER / verify.TOOL_DIR
    safe = name.replace('::', '_')
    src, ii, asm, obj, stamp = (WORK / (safe + e) for e in ('.cpp', '.ii', '.s', '.o', '.key'))
    src.write_text('#include "%s"\n\nstruct Probe : public %s {\n    Probe();\n    virtual void probe_();\n};\n\n'
                   'void Probe::probe_()\n{\n}\n' % (header, name))
    key = verify.source_key(src, verify.BUILD_KEY)
    if not (obj.is_file() and stamp.is_file() and stamp.read_text() == key):
        stamp.unlink(missing_ok=True)
        r = lambda p: p.relative_to(verify.ROOT).as_posix()
        verify.run_tool(tool_dir, 'cpp.exe', verify.CPPFLAGS + [r(src), r(ii)])
        verify.run_tool(tool_dir, 'cc1plus.exe', verify.CFLAGS + [r(ii), '-o', r(asm)])
        verify.assemble(compilers_dir, asm, obj)
        stamp.write_text(key)
    return obj


def probe_table(obj_path):
    """[(first word, function symbol or None)] for each entry of the probe's vtable."""
    obj = verify.Elf32(obj_path)
    symbols = obj.symbols()
    found = [s for s in symbols if s[0].startswith('_vt') and 'Probe' in s[0] and 0 < s[4] < len(obj.sections)]
    if len(found) != 1:
        raise verify.VerifyError('%s: expected one Probe vtable, found %d' % (obj_path.name, len(found)))
    _, value, size, _, shndx = found[0]
    data = obj.contents(obj.sections[shndx])
    relocs = obj.relocations(shndx)
    if not size:
        size = len(data) - value
    out = []
    for off in range(value, value + size - ENTRY + 1, ENTRY):
        first, = struct.unpack_from('<I', data, off)
        kind, sym = relocs.get(off + 4, (None, None))
        if first == 0 and sym is None and off > value:
            break
        out.append((first, symbols[sym][0] if sym is not None else None))
    return out


def check(address, name, table, slus, addresses, verbose):
    """Compare one probe table with the game. Returns (checked, unchecked, problems)."""
    checked, unchecked, problems = 0, [], []
    # Entry 0 is the RTTI (__tf) entry, the last is the probe's own function, and the destructor
    # slot holds the probe's own destructor: none of those say anything about `name`'s virtuals.
    for i, (first, symbol) in enumerate(table[1:-1], 1):
        where = address + i * ENTRY
        raw = slus_bytes(slus, where, ENTRY)
        if raw is None:
            problems.append('%s: slot %d at 0x%08X is outside the game' % (name, i, where))
            break
        game_first, game_pointer = struct.unpack('<II', raw)
        if symbol is None or 'Probe' in symbol:
            continue
        if 'pure_virtual' in symbol:
            continue
        if symbol not in addresses:
            unchecked.append((i, symbol, game_pointer))
            continue
        if first != game_first or addresses[symbol] != game_pointer:
            problems.append('%s: slot %d is %s at 0x%08X here, but the game has 0x%08X there'
                            % (name, i, symbol, addresses[symbol], game_pointer))
        else:
            checked += 1
    if verbose:
        for slot, symbol, pointer in unchecked:
            print('    unchecked slot %2d  game 0x%08X  %s' % (slot, pointer, symbol))
    return checked, len(unchecked), problems


def slus_bytes(slus, address, length):
    for s in slus.sections:
        if s['type'] == 1 and s['addr'] <= address and address + length <= s['addr'] + s['size']:
            start = s['offset'] + address - s['addr']
            return slus.data[start:start + length]
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--compilers', default=os.environ.get('WHIRL_COMPILERS'))
    ap.add_argument('--slus', default=os.environ.get('WHIRL_SLUS'))
    ap.add_argument('-v', '--verbose', action='store_true', help='list slots that could not be checked')
    ap.add_argument('-q', '--quiet', action='store_true', help='only print classes with failures and the final summary')
    args = ap.parse_args()
    try:
        if not args.compilers or not args.slus:
            raise verify.VerifyError('give --compilers and --slus, or set WHIRL_COMPILERS and WHIRL_SLUS')
        verify.enter_sandbox()
        verify.check_target(args.slus)
        slus = verify.Elf32(args.slus)
        addresses = verify.load_symbols()
        tables = load_tables()
        objects = verify.build_all(lambda t: build_probe(args.compilers, t[1], t[2]), tables)
        total = unknown = failed = 0
        for (address, name, _), obj in zip(tables, objects):
            checked, unchecked, problems = check(address, name, probe_table(obj), slus, addresses, args.verbose)
            if not args.quiet or problems:
                print('%-28s %3d slots confirmed, %3d unchecked, %d wrong' % (name, checked, unchecked, len(problems)))
            for p in problems:
                print('  FAIL ' + p)
            total += checked
            unknown += unchecked
            failed += len(problems)
        print('%d vtable slots confirmed in %d classes; %d unchecked; %d problems'
              % (total, len(tables), unknown, failed))
        return 1 if failed else 0
    except verify.VerifyError as e:
        print('verify_vtables: ' + str(e), file=sys.stderr)
        return 2


if __name__ == '__main__':
    sys.exit(main())
