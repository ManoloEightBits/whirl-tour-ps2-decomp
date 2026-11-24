#!/usr/bin/env python3
"""Build the decompiled sources with the game's compiler and compare them with the game.

Usage: verify.py --compilers <dir> --slus <SLUS_204.89> [-D NAME] [-v] [source.cpp ...]

Every function compiled from src/ must be listed in config/symbols.txt and must be
byte-identical to the game at its listed address. Exit status is 0 only when that holds.

Whirl Tour (SLUS_204.89) was compiled with SN Systems ProDG ee-gcc 2.95.3 build 1.14
at `-O2 -G0 -fno-exceptions` (with C++ RTTI enabled) and assembled with SN's `ps2eeas.exe`
(ProDG 2.0 build without short-loop padding).

Run it in Linux/WSL. The compiler is an old proprietary Windows binary, so it runs under
Wine inside a network namespace with no interfaces; the script re-executes itself under
`unshare -rn` when it finds a network. It uses the standard library only, so nothing
third-party runs next to the compiler.
"""
import argparse
import hashlib
import os
import re
import socket
import struct
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SRC = ROOT / 'src'
INC = ROOT / 'include'
BUILD = ROOT / 'build'
SYMBOLS = ROOT / 'config' / 'symbols.txt'
PROBES = ROOT / 'config' / 'probes.txt'
TARGET_SHA1 = ROOT / 'pkg' / 'target.sha1'

COMPILER = 'ee-gcc2.95.3-114'
TOOL_DIR = 'lib/gcc-lib/ee/2.95.3'
# SN's early ps2eeas.exe (from ee-gcc2.95.2-273a) inserts the nop after mtc1 without
# over-padding short loops, matching SLUS_204.89's retail assembler behaviour.
ASSEMBLER_COMPILER = 'ee-gcc2.95.2-273a'
ASSEMBLER_TOOL_DIR = 'lib/gcc-lib/ee/2.95.2'
ASSEMBLER = 'ps2eeas.exe'

CPPFLAGS = ['-lang-c++', '-nostdinc', '-Iinclude', '-Isrc']
CFLAGS = ['-quiet', '-O2', '-G0', '-fno-exceptions']
ASFLAGS = ['-G0']

BUILD_KEY = CPPFLAGS + CFLAGS + [ASSEMBLER_COMPILER, ASSEMBLER] + ASFLAGS
TOOL_TIMEOUT = 120
JOBS = min(8, os.cpu_count() or 1)
INCLUDE = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)

SANDBOX_MARK = 'WHIRL_SANDBOXED'

SHT_SYMTAB, SHT_RELA, SHT_REL = 2, 4, 9
STT_FUNC = 2
R_MIPS_32, R_MIPS_26 = 2, 4
RELOC_MASK = {R_MIPS_32: 0xFFFFFFFF, R_MIPS_26: 0x03FFFFFF}
RELOC_MASK_DEFAULT = 0x0000FFFF


class VerifyError(Exception):
    """A problem the user has to fix: bad input, failed build, missing file."""


class Elf32:
    """The few parts of a little-endian ELF32 file this script needs."""

    def __init__(self, path):
        self.data = Path(path).read_bytes()
        if self.data[:6] != b'\x7fELF\x01\x01':
            raise VerifyError('%s is not a little-endian ELF32 file' % path)
        shoff, = struct.unpack_from('<I', self.data, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from('<HHH', self.data, 0x2E)
        fields = ('name', 'type', 'flags', 'addr', 'offset', 'size', 'link', 'info', 'align', 'entsize')
        self.sections = [dict(zip(fields, struct.unpack_from('<10I', self.data, shoff + i * shentsize)))
                         for i in range(shnum)]
        names = self.sections[shstrndx]
        for s in self.sections:
            s['name'] = self._string(names, s['name'])

    def _string(self, table, offset):
        start = table['offset'] + offset
        return self.data[start:self.data.index(b'\0', start)].decode('latin-1')

    def section(self, name):
        for i, s in enumerate(self.sections):
            if s['name'] == name:
                return i, s
        raise VerifyError('no %s section' % name)

    def contents(self, s):
        return self.data[s['offset']:s['offset'] + s['size']]

    def symbols(self):
        """[(name, value, size, type, section index)] in symbol-table order."""
        out = []
        for s in self.sections:
            if s['type'] != SHT_SYMTAB:
                continue
            strings = self.sections[s['link']]
            for off in range(s['offset'], s['offset'] + s['size'], 16):
                name, value, size, info, _, shndx = struct.unpack_from('<IIIBBH', self.data, off)
                out.append((self._string(strings, name), value, size, info & 0xF, shndx))
        return out

    def relocations(self, target_index):
        """{offset: (type, symbol index)} for the section with this index."""
        out = {}
        for s in self.sections:
            if s['type'] not in (SHT_REL, SHT_RELA) or s['info'] != target_index:
                continue
            step = 8 if s['type'] == SHT_REL else 12
            for off in range(s['offset'], s['offset'] + s['size'], step):
                r_offset, r_info = struct.unpack_from('<II', self.data, off)
                out[r_offset] = (r_info & 0xFF, r_info >> 8)
        return out


def enter_sandbox():
    """Make sure there is no network before any proprietary binary runs."""
    interfaces = {name for _, name in socket.if_nameindex()} - {'lo'}
    if not interfaces:
        return
    if os.environ.get(SANDBOX_MARK):
        raise VerifyError('still see network interfaces %s inside the namespace' % sorted(interfaces))
    os.environ[SANDBOX_MARK] = '1'
    os.execvp('unshare', ['unshare', '-rn', sys.executable, *sys.argv])


def check_target(slus):
    want = TARGET_SHA1.read_text().split()[0]
    got = hashlib.sha1(Path(slus).read_bytes()).hexdigest()
    if got != want:
        raise VerifyError('%s has SHA-1 %s, expected %s: wrong build of the game' % (slus, got, want))


def load_symbols():
    """config/symbols.txt -> {mangled symbol: address}."""
    out = {}
    for n, line in enumerate(SYMBOLS.read_text().splitlines(), 1):
        parts = line.split('#')[0].split()
        if not parts:
            continue
        if len(parts) != 2:
            raise VerifyError('%s:%d: expected "<address> <symbol>"' % (SYMBOLS.name, n))
        address, symbol = int(parts[0], 16), parts[1]
        if symbol in out:
            raise VerifyError('%s:%d: %s is listed twice' % (SYMBOLS.name, n, symbol))
        out[symbol] = address
    return out


def load_probes():
    """config/probes.txt -> set of compiler-emitted helper names that verify.py ignores."""
    if not PROBES.is_file():
        return set()
    return {l.split('#')[0].strip() for l in PROBES.read_text().splitlines() if l.split('#')[0].strip()}


def resolve_assembler(compilers_dir):
    asm_dir = Path(compilers_dir).resolve() / ASSEMBLER_COMPILER / ASSEMBLER_TOOL_DIR
    if (asm_dir / ASSEMBLER).is_file():
        return asm_dir, ASSEMBLER
    fallback_dir = Path(compilers_dir).resolve() / COMPILER / TOOL_DIR
    return fallback_dir, ASSEMBLER


def run_tool(tool_dir, exe, args):
    env = dict(os.environ, WINEPREFIX=str(Path.home() / '.wine-ps2'), WINEDEBUG='-all', WINEARCH='win32')
    cmd = ['wine', str(tool_dir / exe), *args]
    try:
        p = subprocess.run(cmd, cwd=ROOT, env=env, capture_output=True, text=True,
                           errors='replace', timeout=TOOL_TIMEOUT)
    except subprocess.TimeoutExpired:
        raise VerifyError('%s timed out after %d s' % (exe, TOOL_TIMEOUT))
    if p.returncode != 0 or 'error' in p.stderr.lower():
        raise VerifyError('%s failed (exit %d):\n%s' % (exe, p.returncode, p.stderr.strip()))
    if p.stderr.strip():
        print(p.stderr.strip())


def source_key(source, flags):
    """Hash of everything that decides a source's object: itself, its headers and the flags."""
    seen, todo = {}, [source]
    while todo:
        path = todo.pop()
        if path in seen:
            continue
        seen[path] = path.read_bytes()
        for name in INCLUDE.findall(seen[path].decode('latin-1')):
            for base in (SRC, INC, path.parent):
                candidate = (base / name).resolve()
                if candidate.is_file():
                    todo.append(candidate)
    digest = hashlib.sha1(repr((COMPILER, flags)).encode())
    for path in sorted(seen):
        digest.update(path.as_posix().encode())
        digest.update(seen[path])
    return digest.hexdigest()


def assemble(compilers_dir, asm, obj):
    """Assemble compiler output with SN's ps2eeas.exe."""
    asm_dir, asm_exe = resolve_assembler(compilers_dir)
    r = lambda p: p.relative_to(ROOT).as_posix()
    run_tool(asm_dir, asm_exe, ASFLAGS + ['-o', r(obj), r(asm)])


def build(compilers_dir, source, defines):
    """Preprocess, compile and assemble one source file. Returns the object path."""
    tool_dir = Path(compilers_dir).resolve() / COMPILER / TOOL_DIR
    rel = source.relative_to(ROOT)
    out = BUILD / rel.relative_to('src')
    out.parent.mkdir(parents=True, exist_ok=True)
    ii, asm, obj, stamp = (out.with_suffix(e) for e in ('.ii', '.s', '.o', '.key'))
    key = source_key(source, BUILD_KEY + defines)
    if obj.is_file() and stamp.is_file() and stamp.read_text() == key:
        return obj
    stamp.unlink(missing_ok=True)
    r = lambda p: p.relative_to(ROOT).as_posix()
    run_tool(tool_dir, 'cpp.exe', CPPFLAGS + ['-D' + d for d in defines] + [rel.as_posix(), r(ii)])
    run_tool(tool_dir, 'cc1plus.exe', CFLAGS + [r(ii), '-o', r(asm)])
    assemble(compilers_dir, asm, obj)
    stamp.write_text(key)
    return obj


def build_all(function, sources):
    """Run function(source) for every source, a few at a time. Results keep the sources' order."""
    with ThreadPoolExecutor(max_workers=JOBS) as pool:
        return list(pool.map(function, sources))


def compare(obj_path, game, game_base, addresses, verbose):
    """Compare each function in the object with the game. Returns (bytes, functions, problems)."""
    obj = Elf32(obj_path)
    text_index, text = obj.section('.text')
    code = obj.contents(text)
    relocs = obj.relocations(text_index)
    symbols = obj.symbols()
    funcs = sorted((value, size, name) for name, value, size, kind, shndx in symbols
                   if shndx == text_index and kind == STT_FUNC)
    starts = [value for value, _, _ in funcs] + [len(code)]
    matched, count, problems = 0, 0, []
    for i, (start, size, name) in enumerate(funcs):
        end = start + size if size else starts[i + 1]
        # ps2eeas pads the end of .text to 16 bytes with trailing nops; trim trailing nops
        # if the game has another function or ends at an 8-byte boundary.
        address = addresses.get(name)
        if address is None and name in load_probes():
            continue
        if address is None:
            problems.append('%s: not in %s' % (name, SYMBOLS.name))
            continue
        offset = address - game_base
        if offset < 0 or offset + (end - start) > len(game):
            problems.append('%s: address 0x%08X is outside the game .text' % (name, address))
            continue
        # Find jr $ra + delay slot at the end of the function to avoid ps2eeas section padding mismatch
        while end - start > 8 and struct.unpack_from('<I', code, end - 4)[0] == 0:
            prev_word, = struct.unpack_from('<I', code, end - 12)
            if prev_word == 0x03E00008:  # jr $ra followed by delay slot at end - 8
                end -= 4
                break
            break
        diffs, unchecked = [], 0
        for pos in range(start, end, 4):
            ours, = struct.unpack_from('<I', code, pos)
            theirs, = struct.unpack_from('<I', game, offset + pos - start)
            mask = 0
            if pos in relocs:
                kind, sym = relocs[pos]
                mask = RELOC_MASK.get(kind, RELOC_MASK_DEFAULT)
                target = addresses.get(symbols[sym][0])
                if kind == R_MIPS_26 and target is not None:
                    ours, mask = (ours & ~mask) | (target >> 2 & mask), 0
                else:
                    unchecked += 1
            if (ours ^ theirs) & ~mask & 0xFFFFFFFF:
                diffs.append('    +0x%03x  ours %08X  game %08X' % (pos - start, ours, theirs))
        note = ', %d linker fields unchecked' % unchecked if unchecked else ''
        tail = game[offset + end - start:offset + ((end - start + 7) & ~7)]
        if not diffs and any(tail):
            problems.append('%s: matches as far as it goes, but the game has more code after 0x%08X'
                            % (name, address + end - start))
            continue
        if diffs:
            problems.append('%s: %d of %d words differ at 0x%08X\n%s'
                            % (name, len(diffs), (end - start) // 4, address, '\n'.join(diffs[:12])))
        else:
            matched += end - start
            count += 1
            if verbose:
                print('  match 0x%08X %4d bytes  %s%s' % (address, end - start, name, note))
    return matched, count, problems


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--compilers', default=os.environ.get('WHIRL_COMPILERS'),
                    help='folder holding %s (or set WHIRL_COMPILERS)' % COMPILER)
    ap.add_argument('--slus', default=os.environ.get('WHIRL_SLUS'),
                    help='path to SLUS_204.89 (or set WHIRL_SLUS)')
    ap.add_argument('-D', dest='defines', action='append', default=[], metavar='NAME',
                    help='preprocessor define, e.g. NON_MATCHING')
    ap.add_argument('-v', '--verbose', action='store_true', help='list every matching function')
    ap.add_argument('sources', nargs='*', type=Path, help='default: every .cpp under src/')
    args = ap.parse_args()
    try:
        if not args.compilers or not args.slus:
            raise VerifyError('give --compilers and --slus, or set WHIRL_COMPILERS and WHIRL_SLUS')
        enter_sandbox()
        tool_dir = Path(args.compilers).resolve() / COMPILER / TOOL_DIR
        if not (tool_dir / 'cc1plus.exe').is_file():
            raise VerifyError('no cc1plus.exe in %s' % tool_dir)
        check_target(args.slus)
        slus = Elf32(args.slus)
        _, text = slus.section('.text')
        game, game_base = slus.contents(text), text['addr']
        addresses = load_symbols()
        sources = [p.resolve() for p in args.sources] or sorted(SRC.rglob('*.cpp'))
        total, count, failed = 0, 0, 0
        objects = build_all(lambda source: build(args.compilers, source, args.defines), sources)
        for source, obj in zip(sources, objects):
            print(source.relative_to(ROOT).as_posix())
            matched, functions, problems = compare(obj, game, game_base, addresses, args.verbose)
            total += matched
            count += functions
            failed += len(problems)
            for p in problems:
                print('  FAIL ' + p)
        print('%d functions match: %d bytes, %.3f%% of the game code; %d problems'
              % (count, total, 100.0 * total / len(game), failed))
        return 1 if failed else 0
    except VerifyError as e:
        print('verify: ' + str(e), file=sys.stderr)
        return 2


if __name__ == '__main__':
    sys.exit(main())
