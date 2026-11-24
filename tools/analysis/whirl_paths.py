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
