#!/usr/bin/env python3
"""Extract C++ RTTI type descriptors, __tf functions and virtual function tables from SLUS_204.89.

Usage: extract_rtti.py --slus <SLUS_204.89> [--json <out.json>] [--summary]

Whirl Tour (SLUS_204.89) was compiled with SN Systems ee-gcc 2.95.3 build 1.14 with RTTI
enabled. Each polymorphic class has an 8-byte-per-slot vtable in .rodata whose slot 0 points
to the class's `__tf<MangledName>` RTTI function in .text. This script scans .rodata and .text
to recover every RTTI class name, inheritance link, `__tf` function address, `__ti` BSS node,
and vtable slot table.
"""
import argparse
import json
import re
import struct
import sys
from pathlib import Path

TEXT_BASE = 0x00100000
TEXT_OFFSET = 0x000080
TEXT_SIZE = 0x156268

RODATA_BASE = 0x00280B00
RODATA_OFFSET = 0x180B80
RODATA_SIZE = 0x0302E4

RTTI_HELPERS = {
    0x0022CFF0: '__rtti_si',
    0x0022D010: '__rtti_user',
    0x0022CFA8: '__rtti_class',
}


def demangle_simple(mangled):
    m = re.match(r'^(\d+)(.+)$', mangled)
    if m and int(m.group(1)) == len(m.group(2)):
        return m.group(2)
    return mangled


def find_rtti_strings(rodata):
    out = {}
    pattern = re.compile(rb'([0-9]{1,2}[A-Z_][A-Za-z0-9_]{2,60}|t[0-9]{1,2}[A-Z_][A-Za-z0-9_]{2,70})\x00')
    for m in pattern.finditer(rodata):
        if m.start() > 0 and rodata[m.start() - 1] != 0 and (m.start() & 7) != 0:
            continue
        addr = RODATA_BASE + m.start()
        s = m.group(1).decode('ascii')
        if s[0].isdigit():
            m_len = re.match(r'^(\d+)(.+)$', s)
            if m_len and int(m_len.group(1)) == len(m_len.group(2)):
                out[addr] = s
        elif s.startswith('t'):
            out[addr] = s
    return out


def find_tf_functions(text, rtti_strings):
    twords = struct.unpack_from('<%dI' % ( len(text) // 4), text)
    tf_funcs = {}
    for i in range(len(twords) - 16):
        w = twords[i]
        # Prologue: addiu $sp, $sp, -N
        if (w >> 16) == 0x27BD and (w & 0x8000):
            f_addr = TEXT_BASE + i * 4
            hi_a1 = None
            lo_a1 = None
            hi_reg = None
            hi_val = None
            ti_addr = 0
            jals = []
            for k in range(i + 1, min(i + 60, len(twords))):
                wk = twords[k]
                op, rs, rt = wk >> 26, (wk >> 21) & 0x1F, (wk >> 16) & 0x1F
                if op == 0x0F and hi_reg is None:  # first lui loads high half of own __ti node
                    hi_reg, hi_val = rt, wk & 0xFFFF
                elif op == 0x23 and rs == hi_reg and not ti_addr:  # first lw from that lui tests own __ti
                    ti_addr = (hi_val << 16) + struct.unpack('<h', struct.pack('<H', wk & 0xFFFF))[0]
                elif (wk >> 16) == 0x3C05:  # last lui $a1, hi(name) in the function is the class's own name
                    hi_a1 = wk & 0xFFFF
                    lo_a1 = None
                elif (wk >> 16) == 0x24A5 and hi_a1 is not None and lo_a1 is None:  # addiu $a1, $a1, lo(name)
                    lo_a1 = struct.unpack('<h', struct.pack('<H', wk & 0xFFFF))[0]
                elif op == 3:  # jal
                    jals.append((wk & 0x03FFFFFF) << 2)
                elif wk == 0x03E00008:  # jr $ra
                    break
            if hi_a1 is not None and lo_a1 is not None:
                str_addr = (hi_a1 << 16) + lo_a1
                if str_addr in rtti_strings:
                    mangled = rtti_strings[str_addr]
                    tf_funcs[f_addr] = {
                        'tf_addr': f_addr,
                        'symbol': '__tf' + mangled,
                        'mangled': mangled,
                        'class_name': demangle_simple(mangled),
                        'ti_addr': ti_addr,
                        'name_addr': str_addr,
                        'jals': jals,
                    }
    return tf_funcs


def find_vtables(rodata, tf_funcs):
    rwords = struct.unpack_from('<%dI' % (len(rodata) // 4), rodata)
    vtables = []
    for i in range(len(rwords) - 3):
        if rwords[i] == 0 and rwords[i + 1] in tf_funcs:
            vt_addr = RODATA_BASE + i * 4
            tf_addr = rwords[i + 1]
            tf_info = tf_funcs[tf_addr]
            slots = []
            k = i + 2
            while k + 1 < len(rwords):
                first = rwords[k]
                ptr = rwords[k + 1]
                if first == 0 and ptr == 0:
                    break
                if not (TEXT_BASE <= ptr < TEXT_BASE + TEXT_SIZE and (ptr & 3) == 0):
                    break
                delta, index = struct.unpack('<hh', struct.pack('<I', first))
                slots.append({'slot': len(slots) + 1, 'delta': delta, 'index': index, 'func': ptr})
                k += 2
            base_classes = []
            for jal_target in tf_info['jals']:
                if jal_target in tf_funcs:
                    base_classes.append(tf_funcs[jal_target]['class_name'])
            vtables.append({
                'vtable_addr': vt_addr,
                'vtable_symbol': '_vt$' + tf_info['mangled'],
                'mangled': tf_info['mangled'],
                'class_name': tf_info['class_name'],
                'tf_addr': tf_addr,
                'tf_symbol': tf_info['symbol'],
                'ti_addr': tf_info['ti_addr'],
                'bases': base_classes,
                'slots': slots,
            })
    return vtables


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--slus', required=True, help='path to SLUS_204.89')
    ap.add_argument('--json', help='write extracted RTTI and vtables to JSON file (outside repo)')
    ap.add_argument('--summary', action='store_true', help='print class hierarchy and vtable summary')
    args = ap.parse_args()

    data = Path(args.slus).read_bytes()
    text = data[TEXT_OFFSET:TEXT_OFFSET + TEXT_SIZE]
    rodata = data[RODATA_OFFSET:RODATA_OFFSET + RODATA_SIZE]

    rtti_strings = find_rtti_strings(rodata)
    tf_funcs = find_tf_functions(text, rtti_strings)
    vtables = find_vtables(rodata, tf_funcs)

    if args.summary or not args.json:
        print('Extracted %d RTTI strings, %d __tf functions, %d vtables'
              % (len(rtti_strings), len(tf_funcs), len(vtables)))
        for vt in vtables:
            bases = (' : ' + ', '.join(vt['bases'])) if vt['bases'] else ''
            print('  0x%08X  %-38s  __tf=0x%08X  (%2d virtuals)%s'
                  % (vt['vtable_addr'], vt['class_name'], vt['tf_addr'], len(vt['slots']), bases))

    if args.json:
        out = {
            'tf_functions': list(tf_funcs.values()),
            'vtables': vtables,
        }
        Path(args.json).write_text(json.dumps(out, indent=2) + '\n')
    return 0


if __name__ == '__main__':
    sys.exit(main())
