# Working on this repository (for coding agents)

How to work here, whichever agent you are. `CLAUDE.md` and `GEMINI.md` only import this file.

## Read first

- `docs/STANDARDS.md`: the rules (byte-identical code only, names from evidence, what never goes in the repo).
- `TODO.md`: the plan, open decisions and the functions left in `NON_MATCHING`.
- `docs/MAP.md`: what each 16 KB block of the binary holds and how much of it is matched.
- `docs/TOOLS.md`: every tool and the loop for one function. `docs/MATCHING.md`: source patterns that
  ee-gcc 2.95.3 needs; read it before trying variants.

Game files, compilers and the analysis venv live outside the repository (`../whirl-tour-work` by default,
or the `WHIRL_*` variables; machine-specific paths go in an untracked file such as `CLAUDE.local.md`).
Put temporary files there too, never in the repository, and delete them when done.

## Keep the output small

The tools print summaries; use them instead of reading raw disassembly or hex. Large dumps waste context
and can trip output filters.

- `inspect_tu.py --func A` prints a three-line summary; add `--m2c` for the draft. Use `--dis` only for
  the few instructions the diff cannot explain. `--range A B` lists a TU; an address inside a function
  is reported and replaced by that function's start.
- `diff_func.py file.cpp <mangled>` shows only the differing lines. To try rewrites, pass bodies on stdin:
  `diff_func.py file.cpp <mangled> --bodies - [--apply] <<'BODIES' ... --- ... BODIES` (one line per
  candidate; `--apply` keeps the best). Pick a heredoc delimiter that does not appear in the text.
- `m2c_sweep.py report [--range A B] [--status match|regs]` ranks unmatched functions by how close their raw
  m2c draft compiles to the game (refresh with `m2c_sweep.py run`, unattended); `show ADDR` prints the draft.
- `dump_data.py ADDR` for tables (vtables, jump tables, keyword tables), `coverage.py` and `docs/MAP.md`
  to choose what to work on, `gen_accessors.py --range A B --class C` to draft runs of trivial methods,
  `scratch_cc.py --regs` for register-allocation questions and `--cflag` for compiler-flag experiments.
- `check_all.py` prints four lines; use `--no-rebuild` while iterating and the full run before a commit.

## Loop for one function

1. Choose a target from `TODO.md` or `docs/MAP.md`; prefer finishing a TU in address order.
2. Draft from `inspect_tu.py --func A --m2c`, with names from strings, keyword tables and callers.
3. `diff_func.py`, then batches of `--bodies` variants guided by `docs/MATCHING.md`. Usual causes, in
   order: statement and comparison form (`-ffast-math` lets GCC invert float compares), early returns
   versus nested `if`, `case` order, scalars before struct stores, `do { } while (0)` around a group of
   stores, a local pointer for a repeated address, `this` left in `$a0` (the callee is a method).
4. If a few batches leave only register or scheduling differences, put the function under
   `#ifdef NON_MATCHING` with a note of what matches and what was tried, add it to `TODO.md`, and move on.
5. `python3 tools/check_all.py`, then `python3 tools/progress.py --write`, update the README subsystem
   table and `TODO.md`, and regenerate `docs/MAP.md` after a batch of matches.

## Rules

- Commit or push only when the owner says so. One commit per coherent batch, with a message that explains
  what each function does and which source form was needed.
- Never commit game data, disassembly listings or build output (`tools/check_repo.py` and the pre-commit
  hook enforce it). Names come from evidence (RTTI, strings, keyword tables, callers) or are offset or
  address based (`func_<addr>`, `mField<off>`, `Action<callee>` for one-call wrappers).
- When a one-off script turns out reusable, make it a documented tool in `tools/analysis/` (it reads the
  game at run time and stores none of it) and add it to `docs/TOOLS.md`.
- Record what you learn where the next agent will look: patterns in `docs/MATCHING.md`, open work in
  `TODO.md`, tool changes in `docs/TOOLS.md`, not only in private notes.
