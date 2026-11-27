#!/usr/bin/env python3
"""Parse C++ struct/class layouts and global types from src/game/ to feed back into m2c and naming.

Usage:
  struct_fields.py [--struct NAME] [--globals] [--suggest-renames]
"""
import argparse
import re
import sys
from pathlib import Path

import whirl_paths
from whirl_paths import REPO

GAME_DIR = REPO / 'src' / 'game'

BASE_SIZES = {
    'char': (1, 1), 's8': (1, 1), 'u8': (1, 1), 'bool': (1, 1),
    's16': (2, 2), 'u16': (2, 2), 'short': (2, 2),
    's32': (4, 4), 'u32': (4, 4), 'int': (4, 4), 'f32': (4, 4),
    'unsigned int': (4, 4), 'float': (4, 4), 'long': (4, 4),
    's64': (8, 8), 'u64': (8, 8), 'f64': (8, 8), 'double': (8, 8),
}

STRUCT_RE = re.compile(r'\b(?:struct|class)\s+([A-Za-z_]\w*)\s*(?::[^{]*)?\{(.*?)\n\};', re.S)
EXTERN_RE = re.compile(r'\bextern\s+(?:const\s+)?([A-Za-z_]\w*)\s*(\*)?\s*([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*;')
FIELD_RE = re.compile(
    r'^\s*(?:const\s+|volatile\s+|mutable\s+)*'
    r'((?:unsigned\s+)?[A-Za-z_]\w*)\s+'
    r'(\*+\s*)?'
    r'([A-Za-z_]\w*)'
    r'(?:\s*\[([^\]]+)\])?(?:\s*\[([^\]]+)\])?\s*;'
)


def _eval_dim(s):
    s = s.strip()
    try:
        return int(s, 0)
    except ValueError:
        return None


def parse_all_structs():
    """Return (structs, globals_map):
    structs: {name: {'size': int, 'align': int, 'fields': {offset: (type_str, field_name)}}}
    globals_map: {global_name: (struct_name, is_ptr)}
    """
    files = sorted(GAME_DIR.glob('*.h')) + sorted(GAME_DIR.glob('*.cpp')) + sorted((GAME_DIR / 'blocks').glob('*.cpp'))
    raw_bodies = {}
    globals_map = {}
    for p in files:
        text = p.read_text(errors='replace')
        for m in STRUCT_RE.finditer(text):
            name, body = m.group(1), m.group(2)
            if name not in raw_bodies:
                raw_bodies[name] = body
        for m in EXTERN_RE.finditer(text):
            typ, ptr, gname = m.group(1), bool(m.group(2)), m.group(3)
            if typ not in BASE_SIZES and typ != 'void':
                globals_map[gname] = (typ, ptr)

    structs = {}
    for _pass in range(4):
        for name, body in raw_bodies.items():
            if name in structs:
                continue
            layout = _try_layout(body, structs)
            if layout is not None:
                structs[name] = layout
    return structs, globals_map


def _try_layout(body, known):
    off = 0
    max_align = 1
    fields = {}
    depth = 0
    for raw_line in body.splitlines():
        line = raw_line.split('//')[0].strip()
        if not line:
            continue
        if depth > 0:
            depth += line.count('{') - line.count('}')
            continue
        if '{' in line:
            depth += line.count('{') - line.count('}')
            continue
        if line in ('public:', 'private:', 'protected:') or '(' in line:
            continue
        m = FIELD_RE.match(line)
        if not m:
            continue
        typ, ptr, fname, d1, d2 = m.groups()
        if ptr:
            sz, al = 4, 4
        elif typ in BASE_SIZES:
            sz, al = BASE_SIZES[typ]
        elif typ in known:
            sz, al = known[typ]['size'], known[typ]['align']
        else:
            return None
        count = 1
        if d1:
            n1 = _eval_dim(d1)
            if n1 is None:
                return None
            count *= n1
        if d2:
            n2 = _eval_dim(d2)
            if n2 is None:
                return None
            count *= n2
        off = (off + al - 1) & ~(al - 1)
        if al > max_align:
            max_align = al
        if not fname.startswith(('pad', 'field_')):
            fields[off] = (typ + (' *' if ptr else ''), fname)
            if typ in known and not ptr and count == 1:
                for sub_off, (sub_t, sub_n) in known[typ]['fields'].items():
                    fields[off + sub_off] = (sub_t, f'{fname}.{sub_n}')
        off += sz * count
    total = (off + max_align - 1) & ~(max_align - 1)
    return {'size': total, 'align': max_align, 'fields': fields}


_CACHE = None


def _get_cache():
    global _CACHE
    if _CACHE is None:
        _CACHE = parse_all_structs()
    return _CACHE


def annotate_m2c(text):
    """Rewrite known global->unkXX / global.unkXX accesses in m2c output using C++ struct layouts."""
    structs, globals_map = _get_cache()

    def repl(m):
        gname, op, hex_off = m.group(1), m.group(2), m.group(3)
        info = globals_map.get(gname)
        if not info:
            return m.group(0)
        sname, _ = info
        st = structs.get(sname)
        if not st:
            return m.group(0)
        off = int(hex_off, 16)
        hit = st['fields'].get(off)
        if not hit:
            return m.group(0)
        return f'{gname}{op}{hit[1]}'

    return re.sub(r'\b([A-Za-z_]\w*)(->|\.)unk([0-9A-Fa-f]+)\b', repl, text)


def suggest_keyword_renames():
    """Cross-reference keyword_fields.py parser hits against mFieldXX fields in src/game/."""
    import keyword_fields as kf
    structs, _ = _get_cache()
    _, text, rodata = kf.load_binary() if hasattr(kf, 'load_binary') else (None, None, None)
    if text is None:
        import inspect_tu as itu
        _, text, rodata = itu.load_binary()
    # Check keyword_fields output by running its scanner if available
    print(f'Parsed {len(structs)} structs from src/game/:')
    generic = []
    for sname, st in sorted(structs.items()):
        for off, (typ, fname) in sorted(st['fields'].items()):
            if re.match(r'^mField[0-9A-Fa-f]+$', fname):
                generic.append((sname, off, typ, fname))
    print(f'Generic mFieldXX fields: {len(generic)}')
    for sname, off, typ, fname in generic[:40]:
        print(f'  {sname} +0x{off:02X} ({typ}) {fname}')


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--struct', help='print parsed layout for a struct')
    ap.add_argument('--globals', action='store_true', help='list typed extern globals')
    ap.add_argument('--suggest-renames', action='store_true', help='list generic mFieldXX fields')
    args = ap.parse_args()

    structs, globals_map = parse_all_structs()
    if args.struct:
        st = structs.get(args.struct)
        if not st:
            sys.exit(f'unknown struct: {args.struct}')
        print(f'{args.struct} (size 0x{st["size"]:X}, align {st["align"]}):')
        for off, (typ, fname) in sorted(st['fields'].items()):
            print(f'  +0x{off:03X}: {typ} {fname}')
    elif args.globals:
        for gname, (sname, ptr) in sorted(globals_map.items()):
            print(f'  {gname}: {sname}{" *" if ptr else ""}')
    elif args.suggest_renames:
        suggest_keyword_renames()
    else:
        print(f'{len(structs)} structs, {len(globals_map)} typed globals')


if __name__ == '__main__':
    main()
