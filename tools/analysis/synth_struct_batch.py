#!/usr/bin/env python3
"""Synthesize minimal UnkObj<ADDR> structs for m2c match-sweep drafts that only fail draft_to_cpp
because they access fields on arg0 (->unkXX), then emit and verify matching ones.

Usage:
  synth_struct_batch.py scan [--region game|physics|all] [--range A B] [--min-size N] [--max-size N]
  synth_struct_batch.py emit ADDR... [--apply]
"""
import argparse
import os
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
    # Fold `temp_X = arg0 + OFF;` followed by `M2C_FIELD(temp_X, T *, K)` -> `M2C_FIELD(arg0, T *, OFF + K)`
    text = draft_text
    for tm in re.finditer(r'^\s*(\w+)\s*=\s*arg0\s*\+\s*((?:0x[0-9A-Fa-f]+|\d+))\s*;\s*$', text, re.M):
        tvar, base_off = tm.group(1), int(tm.group(2), 0)
        if not re.search(rf'\b{re.escape(tvar)}\b(?!\s*=)(?!\s*\))', re.sub(rf'M2C_FIELD\(\s*{re.escape(tvar)}\b[^)]*\)', '', text)):
            pass
        text = re.sub(
            rf'M2C_FIELD\(\s*{re.escape(tvar)}\s*,\s*([^,]+?)\s*,\s*((?:0x[0-9A-Fa-f]+|-?\d+))\s*\)',
            lambda m, bo=base_off: f'M2C_FIELD(arg0, {m.group(1)}, 0x{bo + int(m.group(2), 0):X})',
            text,
        )
        # Drop the now-unused `temp_X = arg0 + ...;` if tvar no longer appears in body
        cand = text.replace(tm.group(0) + '\n', '', 1)
        if not re.search(rf'\b{re.escape(tvar)}\b', cand.split('{', 1)[1]):
            text = cand
            text = re.sub(rf'^\s*void \*{re.escape(tvar)};\s*\n', '', text, flags=re.M)

    # Fold indexed array fields: M2C_FIELD((arg0 + (IDX * 4)), T *, OFF) -> M2C_ARRAY(arg0, T *, OFF, IDX)
    arr_fields = re.findall(
        r'M2C_FIELD\(\s*\(\s*arg0\s*\+\s*\(\s*([A-Za-z_]\w*)\s*\*\s*4\s*\)\s*\)\s*,\s*([^,]+?)\s*,\s*((?:0x[0-9A-Fa-f]+|-?\d+))\s*\)',
        text,
    )
    text = re.sub(
        r'M2C_FIELD\(\s*\(\s*arg0\s*\+\s*\(\s*([A-Za-z_]\w*)\s*\*\s*4\s*\)\s*\)\s*,\s*([^,]+?)\s*,\s*((?:0x[0-9A-Fa-f]+|-?\d+))\s*\)',
        lambda m: f'M2C_ARRAY(arg0, {m.group(2)}, 0x{int(m.group(3), 0):X}, {m.group(1)})',
        text,
    )

    # Check all M2C_FIELD(base, type *, OFF) accesses (hex or decimal)
    fields = re.findall(r'M2C_FIELD\(\s*([A-Za-z_]\w*)\s*,\s*([^,]+?)\s*,\s*((?:0x[0-9A-Fa-f]+|-?\d+))\s*\)', text)
    if not fields and not arr_fields:
        return None, 'no M2C_FIELD'
    bad_bases = {b for b, _, _ in fields if b != 'arg0'}
    if bad_bases:
        return None, 'other base: ' + ','.join(sorted(bad_bases))
    lines = text.splitlines()
    sig_idx = next((i for i, l in enumerate(lines) if f'func_{addr:08X}' in l or '(' in l), 0)
    sig = lines[sig_idx].strip()
    if not re.search(r'\b(?:void \*|s32 |u32 |int )arg0\b', sig):
        return None, 'arg0 not ptr/int'
    body_only = '\n'.join(lines[sig_idx + 1:])
    if re.search(r'\*\s*arg0\b', body_only):
        return None, '*arg0'
    if '?' in text:
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
    arr_offsets = set()
    for _, ptr_type, off_str in arr_fields:
        off = int(off_str, 0)
        if off < 0:
            return None, 'negative offset'
        arr_offsets.add(off)
        pt = ' '.join(ptr_type.split())
        offsets[off] = TYPE_MAP.get(pt, ('void *', 4, 4) if pt.endswith('**') else ('int', 4, 4))
    for _, ptr_type, off_str in fields:
        off = int(off_str, 0)
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
        if off in arr_offsets:
            fname = f'mArr{off:02X}'
            s_lines.append(f'    {typ} {fname}[1]; // 0x{off:02X}')
        else:
            fname = f'mField{off:02X}'
            if typ == 'void *':
                s_lines.append(f'    void *{fname}; // 0x{off:02X}')
            else:
                s_lines.append(f'    {typ} {fname}; // 0x{off:02X}')
        cur = off + sz
    s_lines.append('};')

    body = '\n'.join(lines)
    body = re.sub(r'\b(?:void \*|s32 |u32 |int )arg0\b', f'{sname} *arg0', body)
    body = re.sub(r'\bNULL\b', '0', body)
    body = re.sub(r'\bs32\b', 'int', body)
    body = re.sub(
        r'M2C_ARRAY\(\s*arg0\s*,\s*[^,]+?\s*,\s*0x([0-9A-Fa-f]+)\s*,\s*([A-Za-z_]\w*)\s*\)',
        lambda m: f'arg0->mArr{int(m.group(1), 16):02X}[{m.group(2)}]',
        body,
    )
    body = re.sub(
        r'M2C_FIELD\(\s*arg0\s*,\s*[^,]+?\s*,\s*((?:0x[0-9A-Fa-f]+|-?\d+))\s*\)',
        lambda m: f'arg0->mField{int(m.group(1), 0):02X}',
        body,
    )
    return '\n'.join(s_lines), body


def to_method_variant(addr, sdef, body):
    """Convert free-function (UnkObj *arg0, ...) into UnkObj::Method<ADDR>(...) with `this`."""
    sname = f'UnkObj{addr:06X}'
    lines = body.splitlines()
    sig_idx = next((i for i, l in enumerate(lines) if f'func_{addr:08X}' in l), 0)
    sig = lines[sig_idx]
    m = re.match(r'^(.+?)\s+func_([0-9A-F]{8})\((.*)\)\s*$', sig)
    if not m:
        return None, None, None
    ret, _, params = m.groups()
    plist = [p.strip() for p in params.split(',') if p.strip()]
    if not plist or not plist[0].startswith(f'{sname} *'):
        return None, None, None
    rest = ', '.join(plist[1:])
    mname = f'Method{addr:06X}'
    decl = f'    {ret} {mname}({rest});'
    new_sdef = sdef.replace('\n};', f'\n{decl}\n}};')
    new_lines = list(lines)
    new_lines[sig_idx] = f'{ret} {sname}::{mname}({rest})'
    new_body = '\n'.join(new_lines)
    new_body = re.sub(r'\barg0->', 'this->', new_body)
    new_body = re.sub(r'\barg0\b', 'this', new_body)
    mangled = f'{mname}__{len(sname)}{sname}'
    if not rest:
        mangled += 'v'
    return new_sdef, new_body, mangled


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


def probe_compile(cpp_text, addr, game, game_base):
    """Compile cpp_text in verify.BUILD and return (ok, sym_name)."""
    work = verify.BUILD
    work.mkdir(parents=True, exist_ok=True)
    src = work / '_synth_probe.cpp'
    ii = work / '_synth_probe.ii'
    asm = work / '_synth_probe.s'
    obj = work / '_synth_probe.o'
    fixed = work / '_synth_probe.fixed.s'
    src.write_text('#include "common/types.h"\n\n' + cpp_text + '\n')
    tool_dir = COMPILERS.resolve() / verify.COMPILER / verify.TOOL_DIR
    rel = lambda p: p.relative_to(REPO).as_posix()
    try:
        verify.run_tool(tool_dir, 'cpp.exe', verify.CPPFLAGS + [rel(src), rel(ii)])
        verify.run_tool(tool_dir, 'cc1plus.exe', verify.CFLAGS + [rel(ii), '-o', rel(asm)])
        verify.assemble(COMPILERS, asm, obj)
        eobj = verify.Elf32(obj)
        ti, _ = eobj.section('.text')
        syms = [n for n, _, _, k, sh in eobj.symbols() if sh == ti and k == verify.STT_FUNC]
        if not syms:
            return False, None
        sym = syms[0]
        _, count, problems, _ = verify.compare(obj, game, game_base, {sym: addr}, verbose=False)
        return (count == 1 and not problems), sym
    except verify.VerifyError:
        return False, None
    finally:
        for p in (src, ii, asm, obj, fixed):
            p.unlink(missing_ok=True)


def reverse_simple_stores(body):
    """If body is 2-4 simple store lines inside {}, return a variant with those lines reversed."""
    m = re.match(r'^([\s\S]*?\{\n)([\s\S]*?)(\n\})\s*$', body)
    if not m:
        return None
    head, inner, tail = m.groups()
    st_lines = [l for l in inner.splitlines() if l.strip()]
    if not (2 <= len(st_lines) <= 4) or any(re.search(r'\b(?:if|for|while|switch|do|return)\b', l) for l in st_lines):
        return None
    if not all('=' in l and l.strip().endswith(';') for l in st_lines):
        return None
    return head + '\n'.join(reversed(st_lines)) + tail


def emit_matches(args):
    import os  # noqa: F401
    cands = load_candidates(args)
    ok_cands = [c for c in cands if c[2] is not None]
    verify.check_target(whirl_paths.SLUS)
    slus = verify.Elf32(whirl_paths.SLUS)
    _, text = slus.section('.text')
    game, game_base = slus.contents(text), text['addr']
    matches = []
    for addr, sz, sdef, body in ok_cands:
        variants = []
        msdef, mbody, _ = to_method_variant(addr, sdef, body)
        if msdef:
            variants.append(('method', msdef, mbody))
            rmbody = reverse_simple_stores(mbody)
            if rmbody:
                variants.append(('method-rev', msdef, rmbody))
        variants.append(('free', sdef, body))
        rbody = reverse_simple_stores(body)
        if rbody:
            variants.append(('free-rev', sdef, rbody))

        matched = False
        for kind, vsdef, vbody in variants:
            ok, sym = probe_compile(vsdef + '\n\n' + vbody, addr, game, game_base)
            if ok:
                matches.append((addr, sz, sym, vsdef + '\n\n' + vbody, kind))
                matched = True
                break
        if matched:
            print(f'MATCH 0x{addr:08X} ({sz} B) [{matches[-1][4]}] {sym}', flush=True)
    print(f'Tested {len(ok_cands)}: {len(matches)} matched ({sum(m[1] for m in matches)} B)')
    if args.apply and matches:
        syms_text = SYMS.read_text().rstrip('\n') + '\n'
        by_block = {}
        for addr, sz, sym, code, kind in matches:
            blk = addr & ~0x3FFF
            by_block.setdefault(blk, []).append((addr, sym, code))
            if f' {sym}\n' not in syms_text:
                syms_text += f'0x{addr:08X} {sym}\n'
        SYMS.write_text(syms_text)
        for blk, items in sorted(by_block.items()):
            bp = BLOCKS / f'Block_{blk:08X}.cpp'
            if bp.exists():
                cur = bp.read_text().rstrip('\n') + '\n\n'
            else:
                cur = '#include "common/types.h"\n\n'
            for addr, sym, code in items:
                cur += f'// Synthesized from m2c (0x{addr:08X})\n{code}\n\n'
            bp.write_text(cur)
        print(f'Applied {len(matches)} functions to {len(by_block)} block files + symbols.txt')


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = ap.add_subparsers(dest='cmd', required=True)
    for name in ('scan', 'emit'):
        p = sub.add_parser(name)
        p.add_argument('--region', choices=['game', 'physics', 'all'], default='game')
        p.add_argument('--range', nargs=2)
        p.add_argument('--status', default='match')
        p.add_argument('--min-size', type=int, default=16)
        p.add_argument('--max-size', type=int, default=0)
        if name == 'scan':
            p.add_argument('--show', type=int, default=0, help='print synthesized C++ for top N')
        else:
            p.add_argument('--apply', action='store_true', help='write matching functions to Block_*.cpp and symbols.txt')
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
    elif args.cmd == 'emit':
        emit_matches(args)


if __name__ == '__main__':
    main()
