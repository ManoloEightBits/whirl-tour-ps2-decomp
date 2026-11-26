---
name: gemini-web-apply
description: >-
  Step 3 of 3 of the Gemini web workflow: processes the answer saved from the Gemini web chat. Tests each
  candidate against the game's code with diff_func.py, applies the one that matches, runs check_all.py,
  or prepares the next round. Use after gemini-web-select and gemini-web-match.
---

# Step 3: process the chat's answer

Candidates are function **bodies** (statements only). Try the plain m2c form first: it often matches
alone, as with `SetFields189C` (`0x00128E18`). Never trust a candidate until `diff_func.py` reports zero differences.

## 1. Make sure the function is in `src/`

`diff_func.py` needs the function in a repository file. If the target is not there yet (most sweep
targets), first put the m2c draft in the right block file with `draft_to_cpp.py` or `edit_funcs.py`
(see `docs/TOOLS.md`) and add the address to `config/symbols.txt`. Then you know the file and the mangled
name.

## 2. Test the answer

```bash
source ../whirl-tour-work/venv/bin/activate
python3 tools/analysis/gemini_handoff.py test ../whirl-tour-work/handoff/answer.md \
    --file src/game/X.cpp --sym MANGLED
```

It takes the first fenced block of the answer and prints one line per candidate (diff count, first
differing offset).

## 3. Decide

| Result | Do this |
|---|---|
| A candidate with 0 differences | Rerun with `--apply`; check the names are from evidence (reject invented ones); `python3 tools/check_all.py`; `progress.py --write`; update `TODO.md` and the README table; add any new pattern to `docs/MATCHING.md`. |
| Close but not 0 | Make a new prompt with `gemini_handoff.py pack --func ADDR --file F --sym M --note "best form: ..."` (or paste the best candidate and the differing lines into the same chat) and repeat. Two or three rounds at most. |
| Does not compile / all far off | Paste the compiler error into the chat, or try `docs/MATCHING.md` patterns by hand. |
| Stuck after 3 rounds | Put the function under `#ifdef NON_MATCHING` with a note of what matches and add it to `TODO.md`. |

Then go back to `gemini-web-select` for the next function. Do not commit or push unless the owner says
so, and never commit files from `handoff/`.
