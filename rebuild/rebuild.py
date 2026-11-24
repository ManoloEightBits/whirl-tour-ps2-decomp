#!/usr/bin/env python3
"""Rebuild SLUS_204.89 from a splat split and the decompiled C++, and compare it with the game.

Usage: rebuild.py --split <folder> [--compilers <dir>] [--slus <SLUS_204.89>] [--asm-only] [--allow-kept]

Every function in src/ that can be linked replaces the game's assembly for it. Each C++
function is compiled into its own section, the same address range is cut out of the split
assembly, and a generated linker script puts every piece at its original address. The result
must have the SHA-1 in pkg/target.sha1. Exit status is 0 only when it does.
"""
import argparse
import hashlib
import os
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / 'tools'))
import verify  # noqa: E402

WORK = verify.BUILD / 'rebuild'
UNLINKED = '__unlinked'
SHT_PROGBITS, STT_OBJECT, STT_SECTION = 1, 1, 3
R_MIPS_NONE, R_MIPS_HI16, R_MIPS_LO16 = 0, 5, 6
BINUTILS_TIMEOUT = 600
# splat writes registers 8-15 with their o32 names ($t0-$t7); under -mabi=eabi registers 8-11
# are $a4-$a7 and 12-15 are $t0-$t3, and the assembler has no $t4-$t7.
O32_TEMPS = re.compile(r'\$t([0-7])\b')
EABI_NAME = {'0': 'a4', '1': 'a5', '2': 'a6', '3': 'a7', '4': 't0', '5': 't1', '6': 't2', '7': 't3'}
INSTRUCTION = re.compile(r'\s+/\* [0-9A-F]+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/')


def find_binutils_prefix():
    for prefix in ('mips-linux-gnu-', 'mipsel-linux-gnu-', 'mips64-linux-gnu-', 'mips64el-linux-gnu-'):
        if shutil.which(prefix + 'as') and shutil.which(prefix + 'ld'):
            return prefix
    return None


def binutils(tool, *args):
    prefix = find_binutils_prefix()
    if not prefix:
        raise verify.VerifyError('mips-linux-gnu-%s not found: install binutils-mips-linux-gnu or binutils-mipsel-linux-gnu' % tool)
    try:
        p = subprocess.run([prefix + tool, *map(str, args)], capture_output=True, text=True,
                           timeout=BINUTILS_TIMEOUT)
    except subprocess.TimeoutExpired:
        raise verify.VerifyError('%s timed out after %d s' % (tool, BINUTILS_TIMEOUT))
    if p.returncode != 0:
        raise verify.VerifyError('%s failed:\n%s' % (tool, p.stderr.strip()[:3000]))


def rel(path):
    return path.relative_to(ROOT).as_posix()


def sext16(value):
    return value - 0x10000 if value & 0x8000 else value


def game_bytes(slus, address, length):
    for s in slus.sections:
        if s['type'] == SHT_PROGBITS and s['addr'] <= address and address + length <= s['addr'] + s['size']:
            start = s['offset'] + address - s['addr']
            return slus.data[start:start + length]
    return None


def same_data(obj, ro_bytes, ro_relocs, symbols, ours, slus, theirs, text_index, base):
    if ours in ro_relocs:
        while ours in ro_relocs:
            kind, sym = ro_relocs[ours]
            entry = game_bytes(slus, theirs, 4)
            if kind != verify.R_MIPS_32 or symbols[sym][4] != text_index or entry is None:
                return False
            if struct.unpack('<I', entry)[0] != base + struct.unpack_from('<I', ro_bytes, ours)[0]:
                return False
            ours, theirs = ours + 4, theirs + 4
        return True
    end = ro_bytes.find(b'\0', ours)
    if ours < 0 or end < 0:
        return False
    return game_bytes(slus, theirs, end + 1 - ours) == ro_bytes[ours:end + 1]


def resolve_local_data(source, dest, addresses, slus):
    obj = verify.Elf32(source)
    data = bytearray(obj.data)
    symbols = obj.symbols()
    index_of = {s['name']: i for i, s in enumerate(obj.sections)}
    resolved = set()
    ro_index = index_of.get('.rodata') or index_of.get('.rdata')
    if ro_index is not None:
        ro_bytes = obj.contents(obj.sections[ro_index])
        ro_relocs = obj.relocations(ro_index)
        for rel_sec in obj.sections:
            target = obj.sections[rel_sec['info']] if rel_sec['type'] == verify.SHT_REL else None
            if target is None or not target['name'].startswith('.text.'):
                continue
            name = target['name'][len('.text.'):]
            if name not in addresses:
                continue
            base = addresses[name]
            sites = []
            for pos in range(rel_sec['offset'], rel_sec['offset'] + rel_sec['size'], 8):
                r_offset, r_info = struct.unpack_from('<II', data, pos)
                sym = symbols[r_info >> 8]
                if sym[4] == ro_index and sym[3] in (STT_SECTION, STT_OBJECT):
                    sites.append((pos, r_offset, r_info & 0xFF, sym[1] if sym[3] == STT_OBJECT else 0))
            if not sites or any(kind not in (R_MIPS_HI16, R_MIPS_LO16) for _, _, kind, _ in sites):
                continue
            ours = lambda offset: struct.unpack_from('<I', data, target['offset'] + offset)[0]
            words = {offset: game_bytes(slus, base + offset, 4) for _, offset, _, _ in sites}
            if None in words.values():
                continue
            game = {offset: struct.unpack('<I', w)[0] for offset, w in words.items()}
            highs = {game[o] & 0xFFFF for _, o, kind, _ in sites if kind == R_MIPS_HI16}
            targets, ok = set(), True
            for _, offset, kind, start in sites:
                if kind == R_MIPS_HI16:
                    ok = ok and ours(offset) & 0xFFFF == 0
                    continue
                fits = {t for t in ((h << 16) + sext16(game[offset] & 0xFFFF) for h in highs)
                        if same_data(obj, ro_bytes, ro_relocs, symbols, start + sext16(ours(offset) & 0xFFFF), slus, t,
                                     rel_sec['info'], base)}
                ok = ok and len(fits) == 1
                targets |= fits
            ok = ok and all(any((t + 0x8000) >> 16 & 0xFFFF == game[o] & 0xFFFF for t in targets)
                            for _, o, kind, _ in sites if kind == R_MIPS_HI16)
            if not ok:
                continue
            for pos, offset, _, _ in sites:
                struct.pack_into('<I', data, target['offset'] + offset, ours(offset) & 0xFFFF0000 | game[offset] & 0xFFFF)
                struct.pack_into('<I', data, pos + 4, R_MIPS_NONE)
            resolved.add(name)
    Path(dest).write_bytes(data)
    return resolved


def classify(obj, addresses):
    symbols = obj.symbols()
    linked, kept, calls = {}, {}, {}
    for name, _, _, kind, shndx in symbols:
        if kind != verify.STT_FUNC or not 0 < shndx < len(obj.sections):
            continue
        section = obj.sections[shndx]
        if section['name'] != '.text.' + name:
            continue
        reason = None if name in addresses else 'has no address in config/symbols.txt'
        for kind, index in obj.relocations(shndx).values():
            if kind == R_MIPS_NONE:
                continue
            target, _, _, target_kind, target_section = symbols[index]
            inside = obj.sections[target_section]['name'] if 0 < target_section < len(obj.sections) else ''
            if target_kind == STT_SECTION and inside.startswith('.text.'):
                calls.setdefault(name, set()).add(inside[len('.text.'):])
            elif 0 < target_section < len(obj.sections) and target_kind != verify.STT_FUNC:
                reason = "uses data from its own object file that the game's copy doesn't confirm"
            elif not 0 < target_section < len(obj.sections) and target not in addresses:
                # undefined, or a common symbol such as a type_info node: the game's address is needed
                reason = 'refers to %s, which has no address in config/symbols.txt' % target
        if reason:
            kept[name] = reason
        else:
            linked[name] = section['size']
    settled = False
    while not settled:
        settled = True
        for name in sorted(linked):
            missing = sorted(calls.get(name, set()) - set(linked))
            if missing:
                kept[name] = 'calls %s in the same file, which is not linked' % missing[0]
                del linked[name]
                settled = False
    return linked, kept


def compile_functions(compilers_dir, source, addresses, slus):
    tool_dir = Path(compilers_dir).resolve() / verify.COMPILER / verify.TOOL_DIR
    base = WORK / source.relative_to(verify.SRC)
    base.parent.mkdir(parents=True, exist_ok=True)
    ii, asm, raw, renamed, relinked, settled, obj, stamp = (
        base.with_suffix(e) for e in ('.ii', '.s', '.raw.o', '.link.s', '.link.o', '.data.o', '.o', '.key'))
    assemble = lambda src, dst: verify.assemble(compilers_dir, src, dst)
    key = verify.source_key(source, verify.BUILD_KEY + ['-ffunction-sections'])
    if not (raw.is_file() and stamp.is_file() and stamp.read_text() == key):
        stamp.unlink(missing_ok=True)
        verify.run_tool(tool_dir, 'cpp.exe', verify.CPPFLAGS + [rel(source), rel(ii)])
        verify.run_tool(tool_dir, 'cc1plus.exe', verify.CFLAGS + ['-ffunction-sections', rel(ii), '-o', rel(asm)])
        assemble(asm, raw)
        stamp.write_text(key)
    resolve_local_data(raw, settled, addresses, slus)
    linked, kept = classify(verify.Elf32(settled), addresses)
    if kept:
        names = '|'.join(map(re.escape, kept))
        text = asm.read_bytes().decode('latin-1')
        text = re.sub(r'(?m)^(\t\.(?:globl|ent|end)\t)(%s)(\r?)$' % names, r'\1\2%s\3' % UNLINKED, text)
        text = re.sub(r'(?m)^(%s)(:\r?)$' % names, r'\1%s\2' % UNLINKED, text)
        renamed.write_bytes(text.encode('latin-1'))
        assemble(renamed, relinked)
        resolve_local_data(relinked, settled, addresses, slus)
    binutils('objcopy', settled, obj)
    return obj, linked, kept


def cut_assembly(source, dest, ranges):
    chunks, pending = [], []
    index, dropping, open_label = 0, False, None
    with open(source, encoding='latin-1') as fin, open(dest, 'w', encoding='latin-1') as out:
        def close(lines):
            nonlocal open_label
            for line in lines:
                if open_label and line.split()[1] == open_label:
                    out.write(line)
                    open_label = None

        for line in fin:
            line = O32_TEMPS.sub(lambda m: '$' + EABI_NAME[m.group(1)], line)
            instruction = INSTRUCTION.match(line)
            if not instruction:
                if not line.startswith(('.align', '.section')):
                    pending.append(line)
                continue
            address, word = int(instruction.group(1), 16), instruction.group(2)
            while index < len(ranges) and address >= ranges[index][1]:
                index += 1
            close(l for l in pending if l.startswith('endlabel'))
            opening = [l for l in pending if not l.startswith('endlabel')]
            pending = []
            starts_function = any(l.startswith('glabel') for l in opening)
            if (index < len(ranges) and address >= ranges[index][0]) or (
                    dropping and word == '00000000' and not starts_function):
                if not chunks:
                    raise verify.VerifyError('the first function of the game cannot be replaced')
                if open_label:
                    out.write('endlabel %s\n' % open_label)
                    open_label = None
                dropping = True
                continue
            if dropping or not chunks:
                name = '.text.asm_%08X' % address
                out.write('\n.section %s, "ax"\n' % name)
                chunks.append((name, address))
                dropping = False
            for l in opening:
                out.write(l)
                if l.startswith('glabel'):
                    open_label = l.split()[1]
            out.write(line)
        close(pending)
    return chunks


def write_linker_script(path, text_obj, chunks, functions, addresses, text_base):
    lines = ['/* Generated by rebuild.py. */']
    for name, address in sorted(addresses.items(), key=lambda kv: kv[1]):
        if name in functions:
            lines.append('func_%08X = %s;' % (address, name))
        else:
            lines.append('%s = 0x%08X;' % (name, address))
    pieces = [(address, '"%s"(%s)' % (text_obj, name)) for name, address in chunks]
    pieces += [(addresses[name], '"%s"(.text.%s)' % (obj, name)) for name, obj in functions.items()]
    lines += ['SECTIONS', '{', '    .text 0x%08X :' % text_base, '    {']
    lines += ['        . = 0x%X; %s' % (address - text_base, spec) for address, spec in sorted(pieces)]
    lines += ['    }', '    /DISCARD/ : { *(*) }', '}']
    path.write_text('\n'.join(lines) + '\n')


def report_difference(rebuilt, original, text, functions, addresses, sizes):
    ranges = sorted((addresses[n], addresses[n] + sizes[n], n) for n in functions)
    count = min(len(rebuilt), len(original)) // 4 * 4
    diffs = [i for i in range(0, count, 4) if rebuilt[i:i + 4] != original[i:i + 4]]
    print('NO MATCH: %d words differ (sizes %d and %d)' % (len(diffs), len(rebuilt), len(original)))
    for i in diffs[:20]:
        ours, theirs = struct.unpack_from('<I', rebuilt, i)[0], struct.unpack_from('<I', original, i)[0]
        address = i - text['offset'] + text['addr']
        where = next((n for start, end, n in ranges if start <= address < end), 'not in a C++ function')
        print('  0x%08X  rebuilt %08X  game %08X  %s' % (address, ours, theirs, where))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--split', default=os.environ.get('WHIRL_SPLIT'),
                    help="folder holding splat's output (or set WHIRL_SPLIT)")
    ap.add_argument('--compilers', default=os.environ.get('WHIRL_COMPILERS'),
                    help='folder holding %s (or set WHIRL_COMPILERS)' % verify.COMPILER)
    ap.add_argument('--slus', default=os.environ.get('WHIRL_SLUS'),
                    help='path to SLUS_204.89 (or set WHIRL_SLUS)')
    ap.add_argument('--asm-only', action='store_true', help='link no C++, to test the split by itself')
    ap.add_argument('--allow-kept', action='store_true',
                    help='succeed even when some functions had to stay as assembly')
    args = ap.parse_args()
    try:
        if not args.split or not args.slus or not (args.asm_only or args.compilers):
            raise verify.VerifyError('give --split, --slus and --compilers, or set WHIRL_SPLIT, '
                                     'WHIRL_SLUS and WHIRL_COMPILERS')
        split = Path(args.split).resolve()
        if not (split / 'asm' / 'text.s').is_file():
            raise verify.VerifyError('no asm/text.s in %s: run splat first' % split)
        verify.check_target(args.slus)
        slus = verify.Elf32(args.slus)
        _, text = slus.section('.text')
        addresses = verify.load_symbols()
        WORK.mkdir(parents=True, exist_ok=True)

        functions, sizes, objects, kept_all = {}, {}, [], {}
        if not args.asm_only:
            verify.enter_sandbox()
            tool_dir = Path(args.compilers).resolve() / verify.COMPILER / verify.TOOL_DIR
            if not (tool_dir / 'cc1plus.exe').is_file():
                raise verify.VerifyError('no cc1plus.exe in %s' % tool_dir)
            sources = sorted(verify.SRC.rglob('*.cpp'))
            results = verify.build_all(lambda source: compile_functions(args.compilers, source, addresses, slus), sources)
            for obj, linked, kept in results:
                objects.append(obj)
                functions.update((name, obj) for name in linked)
                sizes.update(linked)
                kept_all.update(kept)
            for name in verify.load_probes():
                kept_all.pop(name, None)  # helpers of the generated probes: not game code
            print('linking %d C++ functions (%d bytes); %d kept as assembly'
                  % (len(functions), sum(sizes.values()), len(kept_all)))
            for name, reason in sorted(kept_all.items()):
                print('  kept: %s %s' % (name, reason))

        # Link, then check each C++ function against the game. A function whose bytes differ (an
        # address in config/symbols.txt that holds for one translation unit but not another, such
        # as a type_info node the game has in two places) goes back to assembly and we link again.
        while True:
            ranges = sorted((addresses[n], addresses[n] + sizes[n]) for n in functions)
            cut, text_obj, script, elf, binary = (WORK / n for n in
                                                  ('text.s', 'text.o', 'link.ld', 'out.elf', 'text.bin'))
            chunks = cut_assembly(split / 'asm' / 'text.s', cut, ranges)
            binutils('as', '-EL', '-march=r5900', '-mabi=eabi', '-G0', '-I', split / 'include', '-o', text_obj, cut)
            write_linker_script(script, text_obj, chunks, functions, addresses, text['addr'])
            binutils('ld', '-EL', '--no-check-sections', '-T', script, '-T', split / 'undefined_syms_auto.txt',
                     '-T', split / 'undefined_funcs_auto.txt', '-o', elf, text_obj, *objects)
            binutils('objcopy', '-O', 'binary', '-j', '.text', elf, binary)
            built, original = binary.read_bytes(), slus.contents(text)
            wrong = [n for n in functions
                     if built[addresses[n] - text['addr']:addresses[n] - text['addr'] + sizes[n]]
                     != original[addresses[n] - text['addr']:addresses[n] - text['addr'] + sizes[n]]]
            if not wrong:
                break
            for n in wrong:
                kept_all[n] = 'links to the wrong address for a symbol shared between translation units'
                del functions[n]
                del sizes[n]
            print('%d linked functions differ from the game; keeping them as assembly' % len(wrong))

        rebuilt = ((split / 'assets' / 'header.bin').read_bytes() + binary.read_bytes()[:text['size']]
                   + (split / 'assets' / 'after_text.bin').read_bytes())
        want = verify.TARGET_SHA1.read_text().split()[0]
        got = hashlib.sha1(rebuilt).hexdigest()
        print('sha1 rebuilt  %s\nsha1 expected %s' % (got, want))
        if got == want:
            print('MATCH: rebuilt file is byte-identical, %d assembly pieces and %d C++ functions'
                  % (len(chunks), len(functions)))
            if kept_all and not args.allow_kept:
                print('but %d functions could not be linked (listed above); fix them or pass --allow-kept'
                      % len(kept_all))
                return 1
            return 0
        report_difference(rebuilt, Path(args.slus).read_bytes(), text, functions, addresses, sizes)
        return 1
    except verify.VerifyError as e:
        print('rebuild: ' + str(e), file=sys.stderr)
        return 2


if __name__ == '__main__':
    sys.exit(main())
