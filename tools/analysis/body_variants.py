#!/usr/bin/env python3
"""Write every combination of a set of rewrites of a function's body, for diff_func.py --bodies.

Usage:
  body_variants.py FILE FUNC [--sub 'REGEX=>REPLACEMENT']... [--alt 'TEXT=>ALT1||ALT2']...
                   [--per-match] [--text-macros VAR] [--max N] [-o OUT]

FUNC is the name at the definition (`Draw`, `FEMenu::Draw`); its body (between the `{` and `}` at
column 0) is the starting point. Each --sub is a Python regex and its replacement, either applied or
not; with --per-match every match of it is a separate choice. Each --alt replaces the literal TEXT by
one of its alternatives (or keeps it). --text-macros VAR adds the TEXT_SET_* rewrites of FEScreen.h for
statements on the text pointer VAR (`mText164`): each statement plain or as its macro. All
combinations are written, separated by `---` lines, to OUT (default stdout), up to --max (default
256); OUT.names gets one line per variant naming the choices made, in the same order, so a variant
number from diff_func.py can be read back.

  python3 tools/analysis/body_variants.py src/game/FEScreens.cpp FEMenu::Draw --text-macros text \\
      --alt 'int i = 0;=>int i;' -o /tmp/v.txt
  python3 tools/analysis/diff_func.py src/game/FEScreens.cpp Draw__6FEMenu --bodies /tmp/v.txt
"""
import argparse
import itertools
import re
import sys

TEXT_MACROS = [
    ('pos', r'(?m)^(\s*)%s->mPos04\.Set\(([^;]*)\);$', r'\1TEXT_SET_POS(%s, \2);'),
    ('scale', r'(?m)^(\s*)%s->mScale1C\.Set\(([^;]*)\);$', r'\1TEXT_SET_SCALE(%s, \2);'),
    ('color', r'(?m)^(\s*)%s->SetColor\(([^;]*)\);$', r'\1TEXT_SET_COLOR(%s, \2);'),
    ('rgba', r'(?m)^(\s*)%s->mColor28 = ([^;]*);$', r'\1TEXT_SET_RGBA(%s, \2);'),
    ('string', r'(?m)^(\s*)%s->mString30 = ([^;]*);$', r'\1TEXT_SET_STRING(%s, \2);'),
    ('align', r'(?m)^(\s*)%s->mAlign00 \|= ([^;]*);$', r'\1TEXT_ADD_ALIGN(%s, \2);'),
]


def function_body(src, func):
    m = re.search(r'(?m)^[^\n;]*(?<![\w:])%s\s*\([^;{]*\)[^\n;{]*\n\{\n' % re.escape(func), src)
    if not m:
        raise SystemExit('no definition of %s' % func)
    end = src.index('\n}\n', m.end() - 2)
    return src[m.end():end + 1]


def choices(body, args):
    """A list of (label, [(label, transform) ...]) choice groups; each transform maps body -> body."""
    groups = []
    subs = [(s.split('=>', 1)[0], s.split('=>', 1)[1], 'sub%d' % k) for k, s in enumerate(args.sub)]
    if args.text_macros:
        v = re.escape(args.text_macros)
        subs += [(pat % v, rep % args.text_macros, name) for name, pat, rep in TEXT_MACROS]
    for pat, rep, name in subs:
        hits = list(re.finditer(pat, body))
        if not hits:
            continue
        if args.per_match:
            for k, h in enumerate(hits):
                start, end = h.span()
                groups.append([('', None), ('%s#%d' % (name, k),
                                            (lambda b, s=start, e=end, h=h, r=rep:
                                             b[:s] + h.expand(r) + b[e:]), start)])
        else:
            groups.append([('', None), (name, lambda b, p=pat, r=rep: re.sub(p, r, b))])
    for k, a in enumerate(args.alt):
        text, alts = a.split('=>', 1)
        if text not in body:
            raise SystemExit('--alt: "%s" is not in the body' % text)
        groups.append([('', None)] + [('alt%d.%d' % (k, j), lambda b, t=text, x=x: b.replace(t, x))
                                      for j, x in enumerate(alts.split('||'))])
    return groups


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0],
                                 formatter_class=argparse.RawDescriptionHelpFormatter, epilog=__doc__)
    ap.add_argument('file')
    ap.add_argument('func')
    ap.add_argument('--sub', action='append', default=[], metavar="'REGEX=>REPLACEMENT'")
    ap.add_argument('--alt', action='append', default=[], metavar="'TEXT=>ALT1||ALT2'")
    ap.add_argument('--per-match', action='store_true', help='each match of a --sub is its own choice')
    ap.add_argument('--text-macros', metavar='VAR', help='the TEXT_SET_* macros on statements of VAR')
    ap.add_argument('--max', type=int, default=256)
    ap.add_argument('-o', '--out')
    args = ap.parse_args()
    body = function_body(open(args.file).read(), args.func)
    groups = choices(body, args)
    outs, names = [], []
    for combo in itertools.product(*groups):
        b = body
        # --per-match choices edit by position in the original body: apply them first, from the end
        # of the body to the start, then the others
        positional = sorted((c for c in combo if len(c) == 3), key=lambda c: -c[2])
        for c in positional + [c for c in combo if len(c) == 2]:
            if c[1]:
                b = c[1](b)
        outs.append(b)
        names.append(' '.join(c[0] for c in combo if c[1]) or 'unchanged')
        if len(outs) >= args.max:
            print('stopped at --max %d variants' % args.max, file=sys.stderr)
            break
    text = '\n---\n'.join(o.rstrip('\n') for o in outs) + '\n'
    if args.out:
        open(args.out, 'w').write(text)
        open(args.out + '.names', 'w').write('\n'.join(names) + '\n')
        print('%d variants from %d choices -> %s' % (len(outs), len(groups), args.out))
    else:
        sys.stdout.write(text)
    return 0


if __name__ == '__main__':
    sys.exit(main())
