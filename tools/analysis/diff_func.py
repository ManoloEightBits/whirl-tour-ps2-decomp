#!/usr/bin/env python3
"""Side-by-side decoded MIPS R5900 diff & batch C++ variant tester for Whirl Tour.

Usage:
  diff_func.py <source.cpp> <mangled_symbol> [--all] [-D DEFINE]
  diff_func.py <source.cpp> <mangled_symbol> --variants <variants.json> [--apply]
  diff_func.py <source.cpp> <mangled_symbol> --bodies <bodies.txt | -> [--apply]

1. Side-by-side mode: compiles <source.cpp> and compares <mangled_symbol> against SLUS_204.89,
   decoding both instruction streams with rabbitizer (R5900) and showing relocations.
   By default only prints differing lines (+/- 2 lines of context); pass --all for full listing.
2. Batch variant mode (`--variants file.json`): given `{"target": "old C++ snippet", "candidates": ["new1", "new2", ...]}`,
   tests all candidates in one sandboxed run and reports the exact diff count for each.
3. Body variant mode (`--bodies file`, or `-` for stdin): finds the definition of <mangled_symbol>
   in <source.cpp> by its name and replaces only its body. Candidates are separated by lines that
   hold only `---`; each is the text between the function's braces. A line `@@` in a candidate
   splits it: the text above is inserted before the function (inline helpers), the text below is
   the body. Prints one line per candidate: diff count and the offset of the first difference.

With --apply, the best candidate (fewest differences, first on ties) is written into the source.
"""
import argparse
import json
import os
import re
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


def _skip_literal(text, i):
    """If text[i] starts a comment or a string/char literal, return the index just past it."""
    if text.startswith('//', i):
        end = text.find('\n', i)
        return len(text) if end < 0 else end
    if text.startswith('/*', i):
        end = text.find('*/', i + 2)
        return len(text) if end < 0 else end + 2
    if text[i] in '"\'':
        quote, j = text[i], i + 1
        while j < len(text) and text[j] != quote:
            j += 2 if text[j] == '\\' else 1
        return j + 1
    return i


def qualified_name(symbol):
    """C++ name of a GCC 2.95 mangled symbol, for finding its definition: Class::name or name."""
    if symbol.startswith('_$_'):
        m = re.match(r'_\$_(\d+)', symbol)
        cls = symbol[m.end():m.end() + int(m.group(1))]
        return '%s::~%s' % (cls, cls)
    name, _, rest = symbol.partition('__')
    m = re.match(r'(\d+)', rest)
    if not m:
        return name
    cls = rest[m.end():m.end() + int(m.group(1))]
    return '%s::%s' % (cls, name or cls)


def function_span(text, symbol):
    """(line_start, open_brace, close_brace) of the definition of `symbol` in `text`."""
    qual = qualified_name(symbol)
    found = []
    for m in re.finditer(r'(?<![\w:~])%s\s*\(' % re.escape(qual), text):
        i, depth = m.end(), 1
        while i < len(text) and depth:  # skip the parameter list
            j = _skip_literal(text, i)
            if j != i:
                i = j
                continue
            depth += {'(': 1, ')': -1}.get(text[i], 0)
            i += 1
        while i < len(text) and text[i] not in '{;':
            i += 1
        if i >= len(text) or text[i] == ';':
            continue  # a declaration or a call
        open_brace, depth = i, 0
        while i < len(text):
            j = _skip_literal(text, i)
            if j != i:
                i = j
                continue
            depth += {'{': 1, '}': -1}.get(text[i], 0)
            if depth == 0:
                break
            i += 1
        found.append((text.rfind('\n', 0, m.start()) + 1, open_brace, i))
    if len(found) != 1:
        raise verify.VerifyError('%d definitions of %s found; use --variants with an explicit target'
                                 % (len(found), qual))
    return found[0]


def body_candidates(text, symbol, spec):
    """Full source texts for each body candidate in `spec` (the --bodies file contents)."""
    line_start, open_brace, close_brace = function_span(text, symbol)
    out = []
    for cand in re.split(r'^---[ \t]*$\n?', spec, flags=re.M):
        if not cand.strip():
            continue
        prelude, sep, body = cand.partition('\n@@\n')
        if not sep:
            prelude, body = '', cand
        body = body.strip('\n')
        out.append(text[:line_start] + (prelude.rstrip('\n') + '\n\n' if prelude.strip() else '')
                   + text[line_start:open_brace] + '{\n' + body + '\n' + text[close_brace:])
    return out


def run_candidates(args, src_path, orig_text, texts, labels, game, game_base, addresses):
    """Build each full source text, print one line per candidate, and return the best index."""
    best, best_diffs = None, None
    try:
        for idx, (cand_text, label) in enumerate(zip(texts, labels), 1):
            src_path.write_text(cand_text)
            try:
                obj = verify.build(args.compilers, src_path, args.defines)
                addr, ow, gw, rn, diffs = eval_function(obj, args.symbol, game, game_base, addresses)
                if diffs:
                    status = '%d/%d diffs, first at +0x%03X' % (len(diffs), len(ow), diffs[0] * 4)
                else:
                    status = 'MATCH (0 diffs)'
                if best is None or len(diffs) < best_diffs:
                    best, best_diffs = idx, len(diffs)
            except Exception as exc:
                status = 'BUILD ERROR (%s)' % str(exc).splitlines()[0][:100]
            print('Variant #%d: %s%s' % (idx, status, ('  -->  ' + label) if label else ''))
    finally:
        final = orig_text
        if args.apply and best is not None:
            final = texts[best - 1]
            print('Applied variant #%d (%d diffs) to %s' % (best, best_diffs, src_path.name))
        src_path.write_text(final)
        verify.build(args.compilers, src_path, args.defines)
    return best


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('source', type=Path, help='path to source .cpp file')
    ap.add_argument('symbol', help='mangled symbol name to compare')
    ap.add_argument('--compilers', default=str(COMPILERS))
    ap.add_argument('--slus', default=str(SLUS))
    ap.add_argument('-D', dest='defines', action='append', default=[])
    ap.add_argument('--all', action='store_true', help='show all instructions, not just differing lines')
    ap.add_argument('--variants', type=Path, help='JSON file with {"target": "...", "candidates": ["..."]}')
    ap.add_argument('--bodies', help='file (or - for stdin) with function bodies separated by --- lines')
    ap.add_argument('--apply', action='store_true', help='write the best candidate into the source')
    args = ap.parse_args()

    verify.enter_sandbox()
    slus = verify.Elf32(args.slus)
    _, text = slus.section('.text')
    game, game_base = slus.contents(text), text['addr']
    addresses = verify.load_symbols()
    src_path = args.source.resolve()

    if args.variants or args.bodies:
        orig_text = src_path.read_text()
        if args.bodies:
            spec = sys.stdin.read() if args.bodies == '-' else Path(args.bodies).read_text()
            texts = body_candidates(orig_text, args.symbol, spec)
            labels = [''] * len(texts)
        else:
            spec = json.loads(args.variants.read_text())
            if spec['target'] not in orig_text:
                print('Target snippet not found in %s' % src_path, file=sys.stderr)
                return 2
            texts = [orig_text.replace(spec['target'], c, 1) for c in spec['candidates']]
            labels = [' '.join(c.split())[:60] for c in spec['candidates']]
        best = run_candidates(args, src_path, orig_text, texts, labels, game, game_base, addresses)
        return 0 if best is not None else 1

    obj = verify.build(args.compilers, src_path, args.defines)
    addr, ow, gw, rn, diffs = eval_function(obj, args.symbol, game, game_base, addresses)
    print_side_by_side(addr, args.symbol, ow, gw, rn, diffs, args.all)
    return 1 if diffs else 0


if __name__ == '__main__':
    sys.exit(main())
