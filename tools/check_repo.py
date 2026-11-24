#!/usr/bin/env python3
"""Refuse commits that contain game data, proprietary tools, binaries or secrets.

Usage: check_repo.py [--staged]

Checks every tracked file, or with --staged only the files about to be committed. It
reads file contents from the git index, so it judges what will be committed and not
whatever is in the working folder. Exit status is 0 when nothing is found.
"""
import re
import subprocess
import sys

MAX_BYTES = 2 * 1024 * 1024

FORBIDDEN_NAMES = re.compile(
    r'(^|/)(S[CL][UEP][SM]_\d{3}\.\d{2})$'
    r'|\.(iso|bin|img|mdf|elf|exe|dll|o|obj|gpr|pss|vag|irx|ps2)$', re.IGNORECASE)

MAGIC = {b'\x7fELF': 'an ELF executable or object', b'MZ': 'a Windows executable'}

DECOMPILER_OUTPUT = re.compile(rb'^// Ghidra decompiler output', re.MULTILINE)

SECRETS = [
    (re.compile(rb'-----BEGIN [A-Z ]*PRIVATE KEY-----'), 'a private key'),
    (re.compile(rb'\bgh[pousr]_[A-Za-z0-9]{36,}\b'), 'a GitHub token'),
    (re.compile(rb'\bsk-ant-[A-Za-z0-9_-]{20,}\b'), 'an Anthropic API key'),
    (re.compile(rb'\bAKIA[0-9A-Z]{16}\b'), 'an AWS access key'),
]


def git(*args):
    return subprocess.run(['git', *args], check=True, capture_output=True).stdout


def problems_in(path, data):
    if FORBIDDEN_NAMES.search(path):
        yield 'file name or type is never allowed in this repo'
    if len(data) > MAX_BYTES:
        yield 'is %d bytes; the limit is %d' % (len(data), MAX_BYTES)
    for magic, what in MAGIC.items():
        if data.startswith(magic):
            yield 'is ' + what
    if b'\0' in data:
        yield 'is a binary file; the repo holds text only'
    if DECOMPILER_OUTPUT.search(data):
        yield 'is Ghidra decompiler output, which is derived from the executable'
    for pattern, what in SECRETS:
        if pattern.search(data):
            yield 'contains what looks like ' + what


def main():
    staged = '--staged' in sys.argv[1:]
    if staged:
        listing = git('diff', '--cached', '--name-only', '--diff-filter=ACMR', '-z')
    else:
        listing = git('ls-files', '-z')
    paths = [p.decode('utf-8', 'replace') for p in listing.split(b'\0') if p]
    failed = 0
    for path in paths:
        for problem in problems_in(path, git('show', ':' + path)):
            print('%s: %s' % (path, problem))
            failed += 1
    if failed:
        print('check_repo: %d problems. See docs/STANDARDS.md, "What never goes in the repo".' % failed)
        return 1
    print('check_repo: %d files clean' % len(paths))
    return 0


if __name__ == '__main__':
    sys.exit(main())
