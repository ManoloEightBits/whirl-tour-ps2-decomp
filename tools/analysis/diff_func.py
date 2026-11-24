#!/usr/bin/env python3
"""Side-by-side decoded MIPS R5900 diff & batch C++ variant tester for Whirl Tour.

Usage:
  diff_func.py <source.cpp> <mangled_symbol> [--all] [-D DEFINE]
  diff_func.py <source.cpp> <mangled_symbol> --variants <variants.json>

1. Side-by-side mode: compiles <source.cpp> and compares <mangled_symbol> against SLUS_204.89,
   decoding both instruction streams with rabbitizer (R5900) and showing relocations.
   By default only prints differing lines (+/- 2 lines of context); pass --all for full listing.
2. Batch variant mode (`--variants file.json`): given `{"target": "old C++ snippet", "candidates": ["new1", "new2", ...]}`,
   tests all candidates in one sandboxed run and reports the exact diff count for each.
"""
import argparse
import json
import os
import struct
import sys
import tempfile
from pathlib import Path
import rabbitizer

from whirl_paths import REPO, SLUS, COMPILERS  # noqa: E402,F401

import verify  # noqa: E402


def dis_word(w, pc):
    ins = rabbitizer.Instruction(w, vram=pc, category=rabbitizer.InstrCategory.R5900)
    return ins.disassemble()


def eval_function(obj_path, sym_name, game, game_base, addresses):
    """Return (ours_words, game_words, reloc_notes, diff_indices) for sym_name in obj_path."""
    obj = verify.Elf32(obj_path)
    text_index, text = obj.section('.text')
    code = obj.contents(text)
    relocs = obj.relocations(text_index)
    symbols = obj.symbols()
    funcs = sorted((value, size, name) for name, value, size, kind, shndx in symbols
                   if shndx == text_index and kind == verify.STT_FUNC)
    starts = [value for value, _, _ in funcs] + [len(code)]
    target_entry = None
    for i, (start, size, name) in enumerate(funcs):
        if name == sym_name:
            end = start + size if size else starts[i + 1]
            target_entry = (start, end)
            break
    if target_entry is None:
        available = [name for _, _, name in funcs]
        raise verify.VerifyError('symbol %s not found in %s (available: %s)'
                                 % (sym_name, obj_path.name, ', '.join(available)))
    start, end = target_entry
    while end - start > 8 and struct.unpack_from('<I', code, end - 4)[0] == 0:
        prev_word, = struct.unpack_from('<I', code, end - 12)
        if prev_word == 0x03E00008:
            end -= 4
            break
        break

    address = addresses.get(sym_name)
    if address is None:
        raise verify.VerifyError('%s has no address in config/symbols.txt' % sym_name)
    offset = address - game_base

    ours_words, game_words, reloc_notes, diff_indices = [], [], {}, []
    for idx, pos in enumerate(range(start, end, 4)):
        ours, = struct.unpack_from('<I', code, pos)
        theirs, = struct.unpack_from('<I', game, offset + pos - start)
        mask = 0
        if pos in relocs:
            kind, sym = relocs[pos]
            sym_str = symbols[sym][0]
            reloc_notes[idx] = sym_str
            mask = verify.RELOC_MASK.get(kind, verify.RELOC_MASK_DEFAULT)
            target = addresses.get(sym_str)
            if kind == verify.R_MIPS_26 and target is not None:
                ours, mask = (ours & ~mask) | (target >> 2 & mask), 0
        ours_words.append(ours)
        game_words.append(theirs)
        if (ours ^ theirs) & ~mask & 0xFFFFFFFF:
            diff_indices.append(idx)
    return address, ours_words, game_words, reloc_notes, diff_indices


def print_side_by_side(address, sym_name, ours_words, game_words, reloc_notes, diff_indices, show_all):
    n = len(ours_words)
    if not diff_indices:
        print('MATCH: %s at 0x%08X (%d instructions, %d bytes) matches 100%%!' % (sym_name, address, n, n * 4))
        if not show_all:
            return
    else:
        print('DIFF: %s at 0x%08X: %d of %d instructions differ' % (sym_name, address, len(diff_indices), n))

    show_set = set(range(n)) if show_all else {i for d in diff_indices for i in range(max(0, d - 2), min(n, d + 3))}
    last_i = -1
    for i in sorted(show_set):
        if last_i != -1 and i > last_i + 1:
            print('  ...')
        last_i = i
        pc = address + i * 4
        ow, gw = ours_words[i], game_words[i]
        odis = dis_word(ow, pc)
        gdis = dis_word(gw, pc)
        mark = '!=' if i in diff_indices else '  '
        rnote = (' [' + reloc_notes[i] + ']') if i in reloc_notes else ''
        print('  +0x%03X (%08X) %s  OURS: %08X %-30s | GAME: %08X %-30s%s'
              % (i * 4, pc, mark, ow, odis, gw, gdis, rnote))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('source', type=Path, help='path to source .cpp file')
    ap.add_argument('symbol', help='mangled symbol name to compare')
    ap.add_argument('--compilers', default=str(COMPILERS))
    ap.add_argument('--slus', default=str(SLUS))
    ap.add_argument('-D', dest='defines', action='append', default=[])
    ap.add_argument('--all', action='store_true', help='show all instructions, not just differing lines')
    ap.add_argument('--variants', type=Path, help='JSON file with {"target": "...", "candidates": ["..."]}')
    args = ap.parse_args()

    verify.enter_sandbox()
    slus = verify.Elf32(args.slus)
    _, text = slus.section('.text')
    game, game_base = slus.contents(text), text['addr']
    addresses = verify.load_symbols()
    src_path = args.source.resolve()

    if args.variants:
        spec = json.loads(args.variants.read_text())
        orig_text = src_path.read_text()
        target_str = spec['target']
        if target_str not in orig_text:
            print('Target snippet not found in %s' % src_path, file=sys.stderr)
            return 2
        try:
            for idx, cand in enumerate(spec['candidates'], 1):
                src_path.write_text(orig_text.replace(target_str, cand, 1))
                try:
                    obj = verify.build(args.compilers, src_path, args.defines)
                    addr, ow, gw, rn, diffs = eval_function(obj, args.symbol, game, game_base, addresses)
                    status = 'MATCH (0 diffs)' if not diffs else ('%d/%d diffs' % (len(diffs), len(ow)))
                    print('Variant #%d: %s  -->  %s' % (idx, status, cand.strip().replace('\n', ' ')))
                except Exception as exc:
                    print('Variant #%d: BUILD ERROR (%s)' % (idx, str(exc).splitlines()[0]))
        finally:
            src_path.write_text(orig_text)
            verify.build(args.compilers, src_path, args.defines)
        return 0

    obj = verify.build(args.compilers, src_path, args.defines)
    addr, ow, gw, rn, diffs = eval_function(obj, args.symbol, game, game_base, addresses)
    print_side_by_side(addr, args.symbol, ow, gw, rn, diffs, args.all)
    return 1 if diffs else 0


if __name__ == '__main__':
    sys.exit(main())
