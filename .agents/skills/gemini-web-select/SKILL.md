---
name: gemini-web-select
description: >-
  Step 1 of 3 of the Gemini web workflow (use when the agent has no quota left or the user wants to match
  a function with the web chat). Picks the next target function from the m2c sweep and builds the prompt
  file the user pastes into Gemini web. Next: gemini-web-match (in the chat), then gemini-web-apply.
---

# Step 1: select a target and build the prompt

The web chat cannot read the repository or run the compiler. This step runs locally and produces one
file to paste.

```bash
source ../whirl-tour-work/venv/bin/activate        # rabbitizer and m2c live there
python3 tools/analysis/gemini_handoff.py select [--status regs|diff] [--region game] \
    [--range A B] [--max-size 200] [--min-score 0.9] [--no-rules]
```

- It reads the sweep (`m2c_sweep.py run` first if there is no result), takes the first function that
  fits, skips the ones in `../whirl-tour-work/handoff/tried.txt`, and records the pick there.
- Default is `--status regs` (draft compiles and differs only in registers: best odds) and small
  functions. Widen with `--status diff --min-score 0.9`, then larger `--max-size`.
- To choose by hand instead: `python3 tools/analysis/gemini_handoff.py pack --func 0xADDR
  [--file src/game/X.cpp --sym MANGLED] [--body FILE] [--note TEXT]`.
- **Fields:** the m2c draft of a function that touches struct fields (`arg0->unk18A4`) is not enough for
  the chat. First put the function in its class in `src/` (see `gemini-web-apply`, section 1), then
  rebuild the prompt with `pack --func A --file F --sym M --context A B` (`A B`: the struct's lines) so
  the chat sees the layout.
- Output: the target line, the prompt path (`../whirl-tour-work/handoff/func_<ADDR>.md`, about 24 KB,
  outside the repo) and `ticket.json` with the address.

## What to tell the user

1. Open gemini.google.com, start a **new chat**, paste the whole prompt file, send. If the chat refuses
   the size, rerun with `--no-rules`.
2. Copy the full reply into `../whirl-tour-work/handoff/answer.md`.
3. Then run the `gemini-web-apply` skill.

Do not commit anything in `handoff/` and do not paste game data into the repository.
