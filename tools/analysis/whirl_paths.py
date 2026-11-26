"""Paths shared by the analysis tools.

Same environment variables and defaults as tools/check_all.py: WHIRL_COMPILERS, WHIRL_SLUS and
WHIRL_SPLIT, each defaulting to a folder in ../whirl-tour-work next to the repository. Importing
this module also makes the repository tools (verify, extract_rtti, ...) importable.
"""
import os
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
WORK = REPO.parent / 'whirl-tour-work'
COMPILERS = Path(os.environ.get('WHIRL_COMPILERS', WORK / 'compilers'))
SLUS = Path(os.environ.get('WHIRL_SLUS', WORK / 'SLUS_204.89'))
SPLIT = Path(os.environ.get('WHIRL_SPLIT', WORK / 'split'))

sys.path.insert(0, str(REPO / 'tools'))

MATCHED_LIST = REPO / 'build' / 'matched.txt'


def matched_addresses(addr_to_sym):
    """Every word address inside a matching function, from the list the last full `verify.py` run wrote.

    A test `a in matched` is true for a function start and for any address inside a matched function, so
    the pieces the function list split off a matched one (the cases of a `switch` that returns after each
    case, as in GetVersusTime154EA8) count as matched too.
    config/symbols.txt also names functions that are only declared (called from matched code), so it
    is not a list of matches. Without build/matched.txt, fall back to it and say so."""
    if MATCHED_LIST.is_file():
        covered = set()
        for line in MATCHED_LIST.read_text().splitlines():
            if line.strip():
                address, size = line.split()[:2]
                start = int(address, 16)
                covered.update(range(start, start + max(int(size), 4), 4))
        return covered
    print('note: %s is missing (run tools/check_all.py); every named function counts as matched'
          % MATCHED_LIST.relative_to(REPO), file=sys.stderr)
    return set(addr_to_sym)
