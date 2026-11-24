#!/usr/bin/env python3
"""Local translation-unit & class inspector for Whirl Tour (SLUS_204.89).

Usage:
  inspect_tu.py --class <ClassName> [--dis]
  inspect_tu.py --range <start_hex> <end_hex> [--dis]
  inspect_tu.py --func <addr_hex>
  inspect_tu.py --trivial [<start_hex> <end_hex>]

Performs local static analysis on SLUS_204.89 + split/asm/text.s + config/symbols.txt:
- Lists all functions in a range or in a class's vtable with exact instruction counts,
  already-matched status, callees, .rodata string literals, float constants, and
  struct member accesses (`offset($a0)`).
- Synthesizes C++ drafts automatically for leaf getters/setters/wrappers and simple
  methods so the AI doesn't need to read raw assembly for trivial functions.
"""
import argparse
import re
import struct
import sys
from pathlib import Path
import rabbitizer

from whirl_paths import REPO, SLUS, SPLIT  # noqa: E402
import whirl_paths  # noqa: E402
SPLIT_TEXT = SPLIT / 'asm' / 'text.s'

import extract_rtti as e  # noqa: E402
import verify  # noqa: E402

RODATA_END = e.RODATA_BASE + e.RODATA_SIZE


def load_binary():
    data = SLUS.read_bytes()
    text = data[e.TEXT_OFFSET:e.TEXT_OFFSET + e.TEXT_SIZE]
    rodata = data[e.RODATA_OFFSET:e.RODATA_OFFSET + e.RODATA_SIZE]
    return data, text, rodata


def parse_func_boundaries(text):
    """Return sorted list of function start addresses from splat's text.s (or prologue scan)."""
    starts = set()
    if SPLIT_TEXT.is_file():
        glabel_re = re.compile(r'^glabel\s+(?:func_([0-9A-Fa-f]{8})|([A-Za-z0-9_$]+))')
        sym_to_addr = verify.load_symbols()
        with open(SPLIT_TEXT, encoding='latin-1') as f:
            for line in f:
                if line.startswith('glabel '):
                    m = glabel_re.match(line)
                    if m and m.group(1):
                        starts.add(int(m.group(1), 16))
                    elif m and m.group(2) in sym_to_addr:
                        starts.add(sym_to_addr[m.group(2)])
    for addr in verify.load_symbols().values():
        if e.TEXT_BASE <= addr < e.TEXT_BASE + e.TEXT_SIZE:
            starts.add(addr)
    # Also scan for jr $ra + delay slot followed by non-nop instruction
    words = struct.unpack_from('<%dI' % (len(text) // 4), text)
    starts.add(e.TEXT_BASE)
    for i in range(len(words) - 2):
        if words[i] == 0x03E00008:  # jr $ra
            k = i + 2
            while k < len(words) and words[k] == 0:
                k += 1
            if k < len(words):
                # Only treat as function boundary if no branch inside the current function jumps past i+1
                starts.add(e.TEXT_BASE + k * 4)
    return sorted(starts)


def get_rodata_string(rodata, addr):
    if not (e.RODATA_BASE <= addr < RODATA_END):
        return None
    off = addr - e.RODATA_BASE
    end = rodata.find(b'\x00', off)
    if end < 0 or end - off > 120:
        return None
    raw = rodata[off:end]
    if all(32 <= b < 127 for b in raw) and len(raw) >= 1:
        return raw.decode('ascii')
    return None


def get_rodata_float(rodata, addr):
    if not (e.RODATA_BASE <= addr <= RODATA_END - 4) or (addr & 3):
        return None
    off = addr - e.RODATA_BASE
    val, = struct.unpack_from('<f', rodata, off)
    return val


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


def analyze_function(addr, end_addr, text, rodata, addr_to_sym, vtable_addrs):
    """Analyze one function in [addr, end_addr), returning metadata + optional C++ suggestion."""
    start_off = addr - e.TEXT_BASE
    end_off = end_addr - e.TEXT_BASE
    words = list(struct.unpack_from('<%dI' % ((end_off - start_off) // 4), text, start_off))
    # Trim trailing nop padding after jr $ra + delay slot
    while len(words) > 2 and words[-1] == 0 and words[-3] == 0x03E00008:
        words.pop()

    callees = []
    strings = []
    floats = []
    vtable_refs = []
    this_reads = {}   # offset -> set of op types ('w', 'h', 'b', 'f', 'addr')
    this_writes = {}  # offset -> set of op types
    lui_state = {}    # reg_num -> (hi16, insn_idx)
    annotated_lines = []

    for idx, w in enumerate(words):
        pc = addr + idx * 4
        ins = rabbitizer.Instruction(w, vram=pc, category=rabbitizer.InstrCategory.R5900)
        dis_str = ins.disassemble()
        note = []

        op = w >> 26
        rs = (w >> 21) & 0x1F
        rt = (w >> 16) & 0x1F
        imm = w & 0xFFFF
        simm = sext16(imm)

        if op == 0x03:  # jal
            target = ((pc & 0xF0000000) | ((w & 0x03FFFFFF) << 2))
            sym = addr_to_sym.get(target, 'func_%08X' % target)
            callees.append((target, sym))
            note.append('-> %s' % sym)
        elif op == 0x0F:  # lui rt, imm
            lui_state[rt] = imm
            # Check if lui + ori / mtc1 forms an inline float constant
            if idx + 1 < len(words):
                w2 = words[idx + 1]
                if (w2 >> 26) == 0x0D and ((w2 >> 21) & 0x1F) == rt and ((w2 >> 16) & 0x1F) == rt:
                    bits = (imm << 16) | (w2 & 0xFFFF)
                    fval, = struct.unpack('<f', struct.pack('<I', bits))
                    floats.append(fval)
                    note.append('float %.6gf (0x%08X)' % (fval, bits))
                elif (w2 >> 21) == (0x11 << 5 | 4) and ((w2 >> 16) & 0x1F) == rt:  # mtc1 rt, $fN
                    bits = imm << 16
                    fval, = struct.unpack('<f', struct.pack('<I', bits))
                    floats.append(fval)
                    note.append('float %.6gf (0x%08X)' % (fval, bits))
        elif op == 0x09 and rs in lui_state:  # addiu rt, rs, simm
            full = (lui_state[rs] << 16) + simm
            if full in vtable_addrs:
                vt_name = vtable_addrs[full]
                vtable_refs.append((full, vt_name))
                note.append('vtable %s (0x%08X)' % (vt_name, full))
            else:
                s = get_rodata_string(rodata, full)
                if s is not None:
                    strings.append((full, s))
                    note.append('"%s" (0x%08X)' % (s, full))
                elif full in addr_to_sym:
                    note.append('%s (0x%08X)' % (addr_to_sym[full], full))
            if rt != rs:
                lui_state.pop(rt, None)
        elif op == 0x31 and rs in lui_state:  # lwc1 ft, simm(rs)
            full = (lui_state[rs] << 16) + simm
            fval = get_rodata_float(rodata, full)
            if fval is not None:
                floats.append(fval)
                note.append('rodata float %.6gf (0x%08X)' % (fval, full))

        # Track accesses to $a0 (this pointer in leaf methods)
        if rs == 4:  # $a0
            if op in (0x23, 0x20, 0x24, 0x21, 0x25, 0x31):  # lw, lb, lbu, lh, lhu, lwc1
                kind = {0x23: 'int', 0x20: 's8', 0x24: 'u8', 0x21: 's16', 0x25: 'u16', 0x31: 'f32'}[op]
                this_reads.setdefault(simm, set()).add(kind)
            elif op in (0x2B, 0x28, 0x29, 0x39):  # sw, sb, sh, swc1
                kind = {0x2B: 'int', 0x28: 'u8', 0x29: 'u16', 0x39: 'f32'}[op]
                this_writes.setdefault(simm, set()).add(kind)
            elif op == 0x09 and rt == 2:  # addiu $v0, $a0, simm
                this_reads.setdefault(simm, set()).add('&ptr')

        comment = ('  # ' + ', '.join(note)) if note else ''
        annotated_lines.append('  %08x: %08x  %-36s%s' % (pc, w, dis_str, comment))

    suggestion = suggest_cpp(words, this_reads, this_writes, callees)
    return {
        'addr': addr,
        'size': len(words) * 4,
        'insns': len(words),
        'sym': addr_to_sym.get(addr),
        'callees': callees,
        'strings': strings,
        'floats': floats,
        'vtables': vtable_refs,
        'this_reads': this_reads,
        'this_writes': this_writes,
        'suggestion': suggestion,
        'dis': annotated_lines,
        'words': words,
    }


def suggest_cpp(words, this_reads, this_writes, callees):
    """Pattern-match common short functions (2..8 instructions) into ready-to-use C++."""
    n = len(words)
    if n == 2 and words[0] == 0x03E00008 and words[1] == 0x00000000:
        return 'void Method() {}'
    if n == 2 and words[0] == 0x03E00008:
        w1 = words[1]
        op, rs, rt, simm = w1 >> 26, (w1 >> 21) & 0x1F, (w1 >> 16) & 0x1F, sext16(w1 & 0xFFFF)
        if op == 0x23 and rs == 4 and rt == 2:  # lw $v0, off($a0)
            return 'int GetField%X() { return mField%X; }' % (simm, simm)
        if op == 0x31 and rs == 4 and rt == 0:  # lwc1 $f0, off($a0)
            return 'f32 GetField%X() { return mField%X; }' % (simm, simm)
        if op == 0x09 and rs == 4 and rt == 2:  # addiu $v0, $a0, off
            return 'void *GetPtr%X() { return &mField%X; }' % (simm, simm)
        if op == 0x2B and rs == 4 and rt == 5:  # sw $a1, off($a0)
            return 'void SetField%X(int v) { mField%X = v; }' % (simm, simm)
        if op == 0x2B and rs == 4 and rt == 0:  # sw $zero, off($a0)
            return 'void ClearField%X() { mField%X = 0; }' % (simm, simm)
        if op == 0x39 and rs == 4 and rt == 12:  # swc1 $f12, off($a0)
            return 'void SetField%X(f32 v) { mField%X = v; }' % (simm, simm)
        if op == 0x09 and rs == 0 and rt == 2:  # addiu $v0, $zero, imm
            return 'int GetConst() { return %d; }' % simm
        if w1 == 0x0000102D:  # daddu $v0, $zero, $zero
            return 'int GetConst0() { return 0; }'
    if n == 3 and words[1] == 0x03E00008:
        w0, w2 = words[0], words[2]
        if (w0 >> 26) == 0x09 and ((w0 >> 21) & 0x1F) == 0 and (w2 >> 26) == 0x2B and ((w2 >> 21) & 0x1F) == 4:
            val = sext16(w0 & 0xFFFF)
            off = sext16(w2 & 0xFFFF)
            return 'void SetField%XConst() { mField%X = %d; }' % (off, off, val)
        if (w0 >> 26) == 0x2B and (w2 >> 26) == 0x2B and ((w0 >> 21) & 0x1F) == 4 and ((w2 >> 21) & 0x1F) == 4:
            off1, off2 = sext16(w0 & 0xFFFF), sext16(w2 & 0xFFFF)
            return 'void SetFields%X_%X(int a, int b) { mField%X = a; mField%X = b; }' % (off1, off2, off1, off2)
    if n == 4 and words[2] == 0x03E00008:
        w0, w1, w3 = words[0], words[1], words[3]
        if (w0 >> 26) == 0x23 and ((w0 >> 21) & 0x1F) == 4:  # lw $v0, off($a0)
            off = sext16(w0 & 0xFFFF)
            if (w1 >> 26) == 0x0E and (w3 == 0x2C420001):  # xori $v0, $v0, K; sltiu $v0, $v0, 1
                return 'int IsField%XEqual() { return mField%X == %d; }' % (off, off, w1 & 0xFFFF)
            if w1 == 0x00000000 and w3 == 0x2C420001:  # lw; nop; jr; sltiu $v0, $v0, 1
                return 'int IsField%XZero() { return mField%X == 0; }' % (off, off)
    if n <= 10 and len(callees) == 1:
        return 'wrapper -> %s (%d insns)' % (callees[0][1], n)
    return None


def decompile_m2c(addr, words, addr_to_sym):
    """Run m2c (-t mipsee-gcc-c++) on the function's instructions and return pseudo-C++."""
    try:
        from m2c.main import parse_flags, run
        import io
        import tempfile
        from contextlib import redirect_stdout
    except ImportError:
        return None
    fn_name = addr_to_sym.get(addr, 'func_%08X' % addr)
    insns = []
    targets = set()
    for i, w in enumerate(words):
        pc = addr + i * 4
        ins = rabbitizer.Instruction(w, vram=pc, category=rabbitizer.InstrCategory.R5900)
        if ins.isBranch() or ins.isUnconditionalBranch():
            t = ins.getBranchVramGeneric()
            if addr <= t < addr + len(words) * 4:
                targets.add(t)
        insns.append((pc, w, ins))
    asm_lines = ['.section .text', 'glabel %s' % fn_name]
    for pc, w, ins in insns:
        if pc in targets:
            asm_lines.append('.L%08X:' % pc)
        if ins.isBranch() or ins.isUnconditionalBranch():
            t = ins.getBranchVramGeneric()
            dis = ins.disassemble(immOverride='.L%08X' % t)
        elif ins.isJumpWithAddress():
            t = ins.getInstrIndexAsVram()
            dis = ins.disassemble(immOverride=addr_to_sym.get(t, 'func_%08X' % t))
        else:
            dis = ins.disassemble()
        asm_lines.append('/* %06X %08X %08X */ %s' % (pc - e.TEXT_BASE + 0x80, pc, w, dis))
    asm_lines.append('endlabel %s' % fn_name)
    with tempfile.NamedTemporaryFile('w', suffix='.s', delete=False) as tf:
        tf.write('\n'.join(asm_lines) + '\n')
        tf_path = tf.name
    try:
        options = parse_flags(['-t', 'mipsee-gcc-c++', '--allman', '--pointer-style', 'right',
                               '--comment-style', 'none', '--globals', 'none', tf_path])
        buf = io.StringIO()
        with redirect_stdout(buf):
            run(options)
        return buf.getvalue().strip()
    except Exception as exc:
        return '// m2c error: %s' % exc
    finally:
        Path(tf_path).unlink(missing_ok=True)


MATCHED = set()  # filled by main() from whirl_paths.matched_addresses()


def print_func_summary(info, show_dis=False, show_m2c=False, addr_to_sym=None):
    if info['addr'] in MATCHED:
        status = 'MATCHED (%s)' % info['sym']
    elif info['sym']:
        status = 'UNMATCHED (named %s)' % info['sym']
    else:
        status = 'UNMATCHED'
    print('0x%08X [%3d insns, %4d B] %s' % (info['addr'], info['insns'], info['size'], status))
    if info['vtables']:
        print('  vtables : ' + ', '.join('%s (0x%08X)' % (n, a) for a, n in info['vtables']))
    if info['strings']:
        print('  strings : ' + ', '.join('"%s"' % s for _, s in info['strings']))
    if info['floats']:
        print('  floats  : ' + ', '.join('%.6gf' % f for f in info['floats']))
    if info['callees']:
        seen = []
        for t, s in info['callees']:
            item = '%s(0x%08X)' % (s, t) if not s.startswith('func_') else s
            if item not in seen:
                seen.append(item)
        print('  calls   : ' + ', '.join(seen))
    if info['this_reads'] or info['this_writes']:
        offs = sorted(set(info['this_reads']) | set(info['this_writes']))
        fields = []
        for off in offs:
            r = '/'.join(sorted(info['this_reads'].get(off, ())))
            w = '/'.join(sorted(info['this_writes'].get(off, ())))
            rw = ('R:' + r if r else '') + (' W:' + w if w else '')
            fields.append('+0x%02X(%s)' % (off, rw.strip()))
        print('  $a0     : ' + ', '.join(fields))
    if info['suggestion']:
        print('  C++     : ' + info['suggestion'])
    if show_m2c:
        m2c_out = decompile_m2c(info['addr'], info['words'], addr_to_sym or {})
        if m2c_out:
            print('  --- m2c (mipsee-gcc-c++) ---')
            for line in m2c_out.splitlines():
                print('  ' + line)
    if show_dis:
        for line in info['dis']:
            print(line)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--class', dest='class_name', help='inspect vtable and methods of an RTTI class')
    ap.add_argument('--range', nargs=2, metavar=('START', 'END'), help='inspect all functions in [START, END]')
    ap.add_argument('--func', help='inspect and disassemble a single function at ADDR')
    ap.add_argument('--trivial', nargs='*', metavar='ADDR', help='scan for unmatched leaf functions <= 8 insns')
    ap.add_argument('--dis', action='store_true', help='include annotated disassembly for each function')
    ap.add_argument('--m2c', action='store_true', help='decompile with m2c (mipsee-gcc-c++)')
    args = ap.parse_args()

    _, text, rodata = load_binary()
    rtti_strings = e.find_rtti_strings(rodata)
    tf_funcs = e.find_tf_functions(text, rtti_strings)
    vtables = e.find_vtables(rodata, tf_funcs)
    vtable_addrs = {v['vtable_addr']: v['vtable_symbol'] for v in vtables}

    sym_to_addr = verify.load_symbols()
    addr_to_sym = {a: s for s, a in sym_to_addr.items()}
    MATCHED.update(whirl_paths.matched_addresses(addr_to_sym))
    starts = parse_func_boundaries(text)

    def end_of(addr):
        for s in starts:
            if s > addr:
                return min(s, addr + 0x2000)
        return min(e.TEXT_BASE + e.TEXT_SIZE, addr + 0x400)

    if args.func:
        addr = int(args.func, 16)
        info = analyze_function(addr, end_of(addr), text, rodata, addr_to_sym, vtable_addrs)
        print_func_summary(info, show_dis=True, show_m2c=True, addr_to_sym=addr_to_sym)
        return 0

    if args.class_name:
        matches = [v for v in vtables if v['class_name'] == args.class_name]
        if not matches:
            print('No vtable found for %s' % args.class_name)
            return 1
        for vt in matches:
            bases = (' : public ' + ', public '.join(vt['bases'])) if vt['bases'] else ''
            print('=== class %s%s ===' % (vt['class_name'], bases))
            print('vtable: 0x%08X (%s)  __tf: 0x%08X (%s)  __ti: 0x%08X'
                  % (vt['vtable_addr'], vt['vtable_symbol'], vt['tf_addr'], vt['tf_symbol'], vt['ti_addr']))
            for slot in vt['slots']:
                faddr = slot['func']
                info = analyze_function(faddr, end_of(faddr), text, rodata, addr_to_sym, vtable_addrs)
                print('  [slot %2d delta=%d idx=%d]' % (slot['slot'], slot['delta'], slot['index']), end=' ')
                print_func_summary(info, show_dis=args.dis, show_m2c=args.m2c, addr_to_sym=addr_to_sym)
        return 0

    if args.range:
        lo, hi = int(args.range[0], 16), int(args.range[1], 16)
        in_range = [s for s in starts if lo <= s < hi]
        if not in_range or in_range[0] > lo:
            in_range = [lo] + in_range
        print('=== Range 0x%08X..0x%08X (%d functions) ===' % (lo, hi, len(in_range)))
        for addr in in_range:
            info = analyze_function(addr, min(hi, end_of(addr)), text, rodata, addr_to_sym, vtable_addrs)
            print_func_summary(info, show_dis=args.dis, show_m2c=args.m2c, addr_to_sym=addr_to_sym)
        return 0

    if args.trivial is not None:
        lo = int(args.trivial[0], 16) if len(args.trivial) >= 1 else 0x00100000
        hi = int(args.trivial[1], 16) if len(args.trivial) >= 2 else 0x001C0000
        in_range = [s for s in starts if lo <= s < hi]
        found = 0
        for addr in in_range:
            if addr in MATCHED:
                continue
            info = analyze_function(addr, end_of(addr), text, rodata, addr_to_sym, vtable_addrs)
            if info['suggestion'] and info['insns'] <= 8:
                print_func_summary(info, show_dis=args.dis)
                found += 1
        print('Total trivial unmatched candidates in 0x%08X..0x%08X: %d' % (lo, hi, found))
        return 0

    ap.print_help()
    return 0


if __name__ == '__main__':
    sys.exit(main())
