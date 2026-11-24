#!/usr/bin/env python3
"""Run all verification checks (verify, verify_vtables, rebuild, check_repo) in quiet mode.

Usage:
  check_all.py [--no-rebuild]

Outputs a single 4-line summary when everything passes, or the failure details and exit status 1.
"""
import argparse
import os
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--no-rebuild', action='store_true', help='skip full binary link (faster iteration)')
    args = ap.parse_args()

    work = ROOT.parent / 'whirl-tour-work'
    env = dict(os.environ)
    env.setdefault('WHIRL_COMPILERS', str(work / 'compilers'))
    env.setdefault('WHIRL_SLUS', str(work / 'SLUS_204.89'))
    env.setdefault('WHIRL_SPLIT', str(work / 'split'))

    steps = [
        [sys.executable, 'tools/verify.py', '-q'],
        [sys.executable, 'tools/verify_vtables.py', '-q'],
    ]
    if not args.no_rebuild:
        steps.append([sys.executable, 'rebuild/rebuild.py', '-q', '--allow-kept'])
    steps.append([sys.executable, 'tools/check_repo.py'])

    for cmd in steps:
        p = subprocess.run(cmd, cwd=ROOT, env=env, text=True, capture_output=True)
        out = '\n'.join(l for l in (p.stdout + '\n' + p.stderr).splitlines()
                        if l.strip() and not l.startswith('wine: Unhandled page fault'))
        if out:
            print(out)
        if p.returncode != 0:
            return p.returncode
    return 0


if __name__ == '__main__':
    sys.exit(main())
