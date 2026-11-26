#!/usr/bin/env python3
"""Prepare a self-contained prompt for a chat model without tool access (for example Gemini on the web),
and test its answer locally.

  gemini_handoff.py select [--status regs|diff] [--region R] [--range A B] [--max-size N] [--min-score X]
                           [--skip ADDR] [--no-rules]
  gemini_handoff.py identify [--region runtime] [--count 60] [--min-size 16] [--max-size 400] [-o OUT]
  gemini_handoff.py pack --func ADDR [--file src/game/X.cpp --sym MANGLED] [--body FILE] [--note TEXT]
                         [--context A B]
                         [--no-rules] [-o OUT]
  gemini_handoff.py test RESPONSE.md [--file src/game/X.cpp --sym MANGLED] [--apply]

Three steps, one skill each (.agents/skills/): `select` (gemini-web-select), the chat's instructions
(gemini-web-match, whose body is the task text of the prompt), `test` (gemini-web-apply).

`select` picks the next target from the m2c sweep (`m2c_sweep.py run` first), skipping the ones listed in
../whirl-tour-work/handoff/tried.txt, builds its prompt like `pack` and writes
../whirl-tour-work/handoff/ticket.json (address, file, symbol, prompt path) that `test` reads when
--file/--sym are missing.

`pack` writes one Markdown prompt (task, rules, m2c draft, current diff, the output format to use) to
OUT (default: ../whirl-tour-work/handoff/func_<ADDR>.md, outside the repository) and prints its path and
size. Paste the file into the chat. The prompt asks for candidate function bodies in one fenced block,
separated by `---` lines, which is the format `diff_func.py --bodies -` reads.

`test` takes the chat's answer saved to a file, extracts the first fenced block and runs it through
`diff_func.py --bodies -` (one line per candidate; `--apply` keeps the best one).

The prompt holds output of the game's m2c draft; it stays in the work folder and must not be committed.
"""
import argparse
import json
import re
import subprocess
import sys

import whirl_paths
from whirl_paths import REPO, WORK

TOOLS = REPO / 'tools' / 'analysis'
FENCE = re.compile(r'```[a-zA-Z+]*\n(.*?)```', re.S)

MATCH_SKILL = REPO / '.agents' / 'skills' / 'gemini-web-match' / 'SKILL.md'
TICKET = WORK / 'handoff' / 'ticket.json'
TRIED = WORK / 'handoff' / 'tried.txt'


def task_text():
    """Body of the gemini-web-match skill (without its front matter): the instructions for the chat."""
    text = MATCH_SKILL.read_text()
    return text.split('---', 2)[2].strip() + '\n'


RULES_HEAD = "\n# Source rules for ee-gcc 2.95.3 (project notes)\n\n"


def run(cmd, **kw):
    return subprocess.run(cmd, capture_output=True, text=True, cwd=REPO, **kw)


def pack(a):
    out = [task_text(), '\n## Target\n\nAddress: `%s`\n' % a.func]
    if a.sym:
        out.append('Symbol: `%s`\n' % a.sym)
    if a.note:
        out.append('\nNote from me: %s\n' % a.note)
    summary = run([sys.executable, str(TOOLS / 'inspect_tu.py'), '--func', a.func, '--m2c'])
    if summary.returncode:
        sys.exit('inspect_tu.py failed:\n' + summary.stderr[-800:])
    out.append('\n## m2c draft and summary\n\n```\n%s```\n' % summary.stdout)
    if a.body:
        out.append('\n## My current attempt\n\n```cpp\n%s\n```\n' % open(a.body).read().rstrip())
    if a.file and a.context:
        lines = (REPO / a.file).read_text().splitlines()[a.context[0] - 1:a.context[1]]
        out.append('\n## Class layout and neighbours (from %s)\n\n```cpp\n%s\n```\n' % (a.file, '\n'.join(lines)))
    if a.context_file:
        out.append('\n## Declarations (%s)\n\n```cpp\n%s\n```\n'
                   % (a.context_file, (REPO / a.context_file).read_text().rstrip()))
    if a.file and a.sym:
        d = run([sys.executable, str(TOOLS / 'diff_func.py'), a.file, a.sym]
                + ['-D', a.define] * bool(a.define))
        text = (d.stdout + d.stderr).strip()
        out.append('\n## Differences against the target (from diff_func.py)\n\n```\n%s\n```\n'
                   % text[:6000])
    if not a.no_rules:
        out.append(RULES_HEAD)
        out.append((REPO / 'docs' / 'STANDARDS.md').read_text())
        out.append('\n')
        out.append((REPO / 'docs' / 'MATCHING.md').read_text())
    path = a.o or (WORK / 'handoff' / ('func_%s.md' % a.func.replace('0x', '').upper()))
    path = type(WORK)(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(''.join(out))
    print('%s  (%d bytes)' % (path, path.stat().st_size))
    print('Paste it into a new chat, save the answer to a file, then run: gemini_handoff.py test <file>')
    return path


def select(a):
    cmd = [sys.executable, str(TOOLS / 'm2c_sweep.py'), 'report', '--status', a.status,
           '--region', a.region, '--top', '400']
    if a.range:
        cmd += ['--range'] + a.range
    if a.max_size:
        cmd += ['--max-size', str(a.max_size)]
    r = run(cmd)
    skip = {x.upper().replace('0X', '') for x in a.skip}
    if TRIED.is_file():
        skip |= {l.split()[0].upper() for l in TRIED.read_text().splitlines() if l.strip()}
    pick = None
    for line in r.stdout.splitlines():
        m = re.match(r'\s+([0-9A-F]{8})\s+(\d+) B\s+(\S+)\s+([\d.]+)', line)
        if m and m.group(1) not in skip and float(m.group(4)) >= a.min_score:
            pick = m
            break
    if not pick:
        sys.exit('no candidate left (try --status diff, a lower --min-score, or empty tried.txt)')
    addr = '0x' + pick.group(1)
    print('target %s  %s B  %s  score %s' % (addr, pick.group(2), pick.group(3), pick.group(4)))
    a.func, a.file, a.sym, a.body, a.note, a.o = addr, None, None, None, None, None
    a.context = a.context_file = a.define = None
    path = pack(a)
    TICKET.write_text(json.dumps({'func': addr, 'prompt': str(path)}))
    TRIED.parent.mkdir(parents=True, exist_ok=True)
    with open(TRIED, 'a') as f:
        f.write('%s\n' % pick.group(1))


IDENTIFY = """\
# Identification task: which well-known routines are these?

I am decompiling a PS2 game (MIPS R5900, 2002, built with ee-gcc 2.95.3 `-O2`). The code below is from its
runtime region (libgcc, libc, the C++ runtime that the compiler links in, and Sony SDK libraries). Each item
is a raw draft from the m2c decompiler: field names (`unkXX`), types and control flow are approximate.
Use web search: GCC 2.95 libgcc2 / fp-bit / `__eh_*` / tinfo sources, newlib (mprec, dtoa, vfprintf,
strtod, memcpy...), the PS2 `ee-gcc` libc, public PS2 SDK knowledge. Take your time and check the
sources; I prefer fewer, certain answers over many guesses.

For every function, answer with:
1. **Name**: the standard routine it implements, or `unknown`. Confidence: high, medium or low.
2. **Reason**: at most two lines naming the instructions or constants that identify it.
3. **Source**: the standard C or C++ source of that routine from the library you think it came from, as it
   appears there (not cleaned up), in a fenced block, or `none`. It must compile with a 2002 compiler:
   no `long long` tricks the original did not use, no C99.
4. **Origin**: libgcc / libc / libm / C++ runtime / Sony SDK / game code.

Neighbours are usually from the same file: functions with close addresses often belong to one library
source file (the list is in address order). Use that to identify the unknown ones, and say which file you
think a run of functions comes from. Do not invent; `unknown` is a valid answer.

Format: one `## 0xADDRESS` heading per function with the four items. At the end, a table
`address | name | origin | confidence` and, below it, the likely library source files in address order.

"""


def identify(a):
    r = run([sys.executable, str(TOOLS / 'm2c_sweep.py'), 'report', '--region', a.region, '--status', 'diff',
             '--max-size', str(a.max_size), '--top', '2000'])
    r2 = run([sys.executable, str(TOOLS / 'm2c_sweep.py'), 'report', '--region', a.region, '--status',
              'match', '--top', '2000'])
    items = {}
    for text in (r.stdout, r2.stdout):
        for line in text.splitlines():
            m = re.match(r'\s+([0-9A-F]{8})\s+(\d+) B\s+(\S+)\s+([\d.]+)', line)
            if m and int(m.group(2)) >= a.min_size and float(m.group(4)) >= a.min_score:
                items[m.group(1)] = int(m.group(2))
    done = set()
    if TRIED.is_file():
        done = {l.split()[0].upper() for l in TRIED.read_text().splitlines() if l.strip()}
    picks = sorted(x for x in items if x not in done)[:a.count]
    out = [IDENTIFY]
    for addr in picks:
        d = run([sys.executable, str(TOOLS / 'inspect_tu.py'), '--func', '0x' + addr, '--m2c'])
        out.append('## 0x%s\n```c\n%s```\n\n' % (addr, d.stdout))
    path = type(WORK)(a.o or WORK / 'handoff' / ('identify_%s.md' % a.region))
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(''.join(out))
    with open(TRIED, 'a') as f:
        f.writelines('%s\n' % x for x in picks)
    print('%s  (%d functions, %d bytes)' % (path, len(picks), path.stat().st_size))


def test(a):
    if not (a.file and a.sym):
        sys.exit('give --file and --sym (the function must be in src/ to be diffed; see the '
                 'gemini-web-apply skill for a function that is not there yet)')
    text = open(a.response).read()
    blocks = FENCE.findall(text)
    if not blocks:
        sys.exit('no fenced code block in %s' % a.response)
    cmd = [sys.executable, str(TOOLS / 'diff_func.py'), a.file, a.sym, '--bodies', '-']
    if a.define:
        cmd += ['-D', a.define]
    if a.apply:
        cmd.append('--apply')
    r = run(cmd, input=blocks[0])
    sys.stdout.write(r.stdout)
    sys.stderr.write(r.stderr[-1500:])
    sys.exit(r.returncode)


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawTextHelpFormatter)
    sub = p.add_subparsers(dest='cmd', required=True)
    k = sub.add_parser('pack')
    k.add_argument('--func', required=True, help='function address, for example 0x001562E8')
    k.add_argument('--file', help='repository .cpp that holds the current attempt')
    k.add_argument('--sym', help='mangled name of the function in that file')
    k.add_argument('--body', help='text file with the current attempt')
    k.add_argument('--note')
    k.add_argument('--context-file', help='whole header with the class and globals to include')
    k.add_argument('--define', help='macro for diff_func.py -D (NON_MATCHING for a parked function)')
    k.add_argument('--context', type=int, nargs=2, metavar=('A', 'B'),
                   help='lines A..B of --file (the struct) to include')
    k.add_argument('--no-rules', action='store_true', help='leave out STANDARDS.md and MATCHING.md')
    k.add_argument('-o')
    k.set_defaults(f=pack)
    i = sub.add_parser('identify')
    i.add_argument('--region', default='runtime', choices=['game', 'physics', 'runtime', 'all'])
    i.add_argument('--count', type=int, default=60)
    i.add_argument('--min-size', type=int, default=16)
    i.add_argument('--max-size', type=int, default=400)
    i.add_argument('--min-score', type=float, default=0.5)
    i.add_argument('-o')
    i.set_defaults(f=identify)
    q = sub.add_parser('select')
    q.add_argument('--status', default='regs', choices=['regs', 'diff', 'match'])
    q.add_argument('--region', default='game', choices=['game', 'physics', 'runtime', 'all'])
    q.add_argument('--range', nargs=2)
    q.add_argument('--max-size', type=int, default=200)
    q.add_argument('--min-score', type=float, default=0.0)
    q.add_argument('--skip', nargs='*', default=[])
    q.add_argument('--no-rules', action='store_true')
    q.set_defaults(f=select)
    t = sub.add_parser('test')
    t.add_argument('response')
    t.add_argument('--file')
    t.add_argument('--sym')
    t.add_argument('--define', help='macro for diff_func.py -D (NON_MATCHING for a parked function)')
    t.add_argument('--apply', action='store_true')
    t.set_defaults(f=test)
    a = p.parse_args()
    a.f(a)


if __name__ == '__main__':
    main()
