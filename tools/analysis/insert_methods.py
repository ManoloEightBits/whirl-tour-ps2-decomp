#!/usr/bin/env python3
"""Insert methods into a class in address order: the declaration in the class body, the definition in the .cpp.

Usage:
  insert_methods.py SPEC.json        (or - to read the spec from stdin)

SPEC:
  {"header": "src/game/AI_Boss.h", "cpp": "src/game/AI_Boss.cpp", "class": "AI_Boss",
   "methods": [{"addr": "0015EB78", "decl": "f32 GetAttackField10();", "note": "optional comment",
                "def": "f32 AI_Boss::GetAttackField10()\\n{\\n    return mField10;\\n}\\n"}]}

The class body must mark its methods with `// 0x<ADDR>` comments (the repository's style). Each new
declaration goes before the first declared method with a higher address (or after the last one), its
`// 0x<ADDR>` comment aligned with that line's. Each definition goes right before the definition of the
next declared method of the class in the .cpp, or at the end of the file. When the class is declared in
the .cpp itself, give the same file as "header" and "cpp".

Useful when a run of methods (from gen_accessors.py, from m2c drafts or written by hand) belongs to a
class that already has methods on both sides: the file stays in address order.
"""
import json
import re
import sys
from pathlib import Path


def class_body(text, cls):
    return re.search(r'(?ms)^(?:class|struct) %s\b[^\n]*\n\{\n(.*?)^\};' % re.escape(cls), text)


def insert(spec):
    cls = spec['class']
    h, c = Path(spec['header']), Path(spec['cpp'])
    ht, ct = h.read_text(), c.read_text()
    m = class_body(ht, cls)
    if not m:
        raise SystemExit('%s: no class or struct %s' % (h, cls))
    lines = m.group(1).split('\n')
    for meth in sorted(spec['methods'], key=lambda x: int(x['addr'], 16)):
        addr = int(meth['addr'], 16)
        decl_idx = [(i, int(mm.group(1), 16)) for i, l in enumerate(lines)
                    for mm in [re.search(r'//\s*0x([0-9A-Fa-f]{8})', l)] if mm and '(' in l]
        if not decl_idx:
            raise SystemExit('%s: %s has no method marked with a // 0x<ADDR> comment' % (h, cls))
        after = [(i, a) for i, a in decl_idx if a > addr]
        before = [(i, a) for i, a in decl_idx if a < addr]
        ref = lines[after[0][0]] if after else lines[before[-1][0]]
        col = ref.index('//')
        text = ('    ' + meth['decl']).ljust(col - 1) + ' // 0x%08X' % addr
        if meth.get('note'):
            text += ': ' + meth['note']
        pos = after[0][0] if after else before[-1][0] + 1
        lines.insert(pos, text)
        for i, a in sorted(decl_idx, key=lambda x: x[1]):
            if a <= addr:
                continue
            nm = re.search(r'(~?\b\w+)\s*\(', lines[i + (1 if i >= pos else 0)])
            dm = nm and re.search(r'(?m)^[^\n;]*\b%s::%s\s*\(' % (re.escape(cls), re.escape(nm.group(1))), ct)
            if dm:
                ct = ct[:dm.start()] + meth['def'].rstrip('\n') + '\n\n' + ct[dm.start():]
                break
        else:
            ct = ct.rstrip('\n') + '\n\n' + meth['def'].rstrip('\n') + '\n'
    if h == c:
        m2 = class_body(ct, cls)
        c.write_text(ct[:m2.start(1)] + '\n'.join(lines) + ct[m2.end(1):])
    else:
        h.write_text(ht[:m.start(1)] + '\n'.join(lines) + ht[m.end(1):])
        c.write_text(ct)
    print('inserted %d methods into %s' % (len(spec['methods']), cls))


def main():
    if len(sys.argv) != 2 or sys.argv[1] in ('-h', '--help'):
        print(__doc__)
        return 0 if len(sys.argv) == 2 else 2
    insert(json.load(sys.stdin if sys.argv[1] == '-' else open(sys.argv[1])))
    return 0


if __name__ == '__main__':
    sys.exit(main())
