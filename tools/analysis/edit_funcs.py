#!/usr/bin/env python3
"""Replace, delete or add whole functions and declaration lines of a C++ file, from a spec on stdin.

Usage:
  edit_funcs.py FILE <<'SPEC'
  === func NAME
  <new text of the function NAME, with its comment if any>
  === drop NAME
  === after NAME
  <a new function to put after the function NAME>
  === append
  <text to add at the end of the file>
  === decl NAME
  <the line(s) that replace the declaration of NAME (a prototype or an `extern`); an empty text
   deletes it; when NAME has no declaration, the text goes before the first function definition>
  === top
  <text to put right after the last #include line>
  SPEC

NAME is a function name as it appears at its definition: `func_00128C80`, `FindPickupDef`, or
`UnkParser::ParseFloat1C3818` for a method. A definition is found by its head at column 0 followed by
`{` on the next line (the repository's style); it ends at the first `}` at column 0. Blocks apply in
order and the file is written once at the end; a NAME that is not found stops the tool before writing.

Meant for batches of hand fixes, such as the functions draft_to_cpp.py's fixcompile and prune remove,
and for trying a rewrite of several functions at once (diff_func.py --bodies handles one function).
"""
import re
import sys


def find_func(src, name, path):
    m = re.search(r'(?m)^[A-Za-z_][^\n;]*?(?<![\w:])%s\(([^;{]*)\)[^\n;{]*\n\{\n' % re.escape(name), src)
    if not m:
        raise SystemExit('%s: no definition of %s' % (path, name))
    end = src.index('\n}\n', m.end() - 2) + 3
    return m.start(), end


def apply(src, spec, path):
    parts = re.split(r'(?m)^=== (\w+) ?(\S*)\n', spec)
    if parts[0].strip():
        raise SystemExit('the spec must start with a "=== <kind> [NAME]" line')
    for i in range(1, len(parts), 3):
        kind, name, text = parts[i], parts[i + 1], parts[i + 2]
        if kind == 'func':
            a, b = find_func(src, name, path)
            src = src[:a] + text.rstrip('\n') + '\n' + src[b:]
        elif kind == 'drop':
            a, b = find_func(src, name, path)
            src = src[:a] + src[b:]
        elif kind == 'after':
            _, b = find_func(src, name, path)
            src = src[:b] + '\n' + text.rstrip('\n') + '\n' + src[b:]
        elif kind == 'append':
            src = src.rstrip('\n') + '\n\n' + text.rstrip('\n') + '\n'
        elif kind == 'decl':
            m = (re.search(r'(?m)^[^\n(]*\b%s\([^\n]*\);[^\n]*\n' % re.escape(name), src)
                 or re.search(r'(?m)^extern [^\n]*\b%s(\[[^\]]*\])?;[^\n]*\n' % re.escape(name), src))
            if m:
                src = src[:m.start()] + text + src[m.end():]
            else:
                f = re.search(r'(?m)^[A-Za-z_][^\n;]*\([^;{]*\)[^\n;{]*\n\{\n', src)
                at = f.start() if f else len(src)
                src = src[:at] + text.rstrip('\n') + '\n\n' + src[at:]
        elif kind == 'top':
            incs = list(re.finditer(r'(?m)^#include [^\n]*\n', src))
            at = incs[-1].end() if incs else 0
            src = src[:at] + text + src[at:]
        else:
            raise SystemExit('unknown block "=== %s"' % kind)
    return re.sub(r'\n{3,}', '\n\n', src)


def main():
    if len(sys.argv) != 2 or sys.argv[1] in ('-h', '--help'):
        print(__doc__)
        return 0 if len(sys.argv) == 2 else 2
    path = sys.argv[1]
    src = open(path).read()
    out = apply(src, sys.stdin.read(), path)
    open(path, 'w').write(out)
    print('%s: %+d lines' % (path, out.count('\n') - src.count('\n')))
    return 0


if __name__ == '__main__':
    sys.exit(main())
