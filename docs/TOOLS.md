# Tools and workflow

There are two groups of tools, both in this repository:

- **Verification tools** (`tools/`, `rebuild/`). They use the Python standard library only and run with
  plain `python3`. They decide whether the work is correct. Nothing third-party runs in the same
  process as the proprietary compiler.
- **Analysis tools** (`tools/analysis/`). They help find and match functions, and need `rabbitizer`,
  `m2c` and `splat64` (pinned in `tools/analysis/requirements.txt`). They read the game from your
  local files at run time and never store any of it in the repository.

All of them keep their output short. They print summaries by default, and the full detail only with a
flag. Use them instead of reading raw disassembly or large dumps.

## Setup

```bash
python3 -m venv ../whirl-tour-work/venv
../whirl-tour-work/venv/bin/pip install -r tools/analysis/requirements.txt
source ../whirl-tour-work/venv/bin/activate     # then: python3 tools/analysis/<tool>.py ...
```

Call the venv's Python through the activated venv or an absolute path. With a path like `../...`,
Python prints a `sys.prefix` warning. Every tool finds the game files through `WHIRL_COMPILERS`,
`WHIRL_SLUS` and `WHIRL_SPLIT`, which default to `../whirl-tour-work/{compilers,SLUS_204.89,split}`
(the same defaults as `check_all.py`, set in `tools/analysis/whirl_paths.py`).

## Loop for one function

1. **Pick a target:** run `scan_candidates.py --level 1|2|3`, `map_tus.py --class X` or
   `inspect_tu.py --class X` / `--range A B` (that one includes m2c drafts).
2. **Write the C++** in `src/game/`, and add the address to `config/symbols.txt`. For a class with a
   vtable, also add a line to `config/vtables.txt`, and add the class to `HAND_WRITTEN` in
   `tools/gen_rtti_stubs.py`.
3. **Diff:** run `diff_func.py src/game/X.cpp <mangled>`. To try several rewrites in one run, use
   `--variants file.json`.
4. **If it is stuck on details** (registers, scheduling, a stray `nop`):
   - `scratch_cc.py snippet.cpp --vs <addr>` tries a loose idea without touching `src/`.
   - `scratch_cc.py ... --regs` explains register choices (see [MATCHING.md](MATCHING.md)).
   - `find_pattern.py '<insns>'` checks whether the game has the same idiom elsewhere.
   - If it still does not match, keep it under `#ifdef NON_MATCHING`.
5. **Check everything:** `python3 tools/check_all.py` (4 lines; `--no-rebuild` while iterating).
6. **Update the numbers:** `python3 tools/progress.py --write` rewrites the README progress table. Also
   update the README subsystem table and `TODO.md` by hand, then commit.

## Verification tools (`python3`)

| Tool | What it does |
| :--- | :--- |
| `tools/check_all.py [--no-rebuild]` | Runs `verify -q`, `verify_vtables -q`, `rebuild -q --allow-kept` and `check_repo`; one summary line each. |
| `tools/verify.py [-q\|-v] [file.cpp ...]` | Builds `src/` with the game's compiler and compares every function with `SLUS_204.89`. `-v` lists each match with address and size. Its `assemble()` (also used by `verify_vtables`, `rebuild` and `scratch_cc`) adds the retail assembler's `mtc1` pair nops first (see [MATCHING.md](MATCHING.md)). |
| `tools/verify_vtables.py [-q\|-v]` | Compares each vtable declared in `config/vtables.txt` slot by slot. Destructor and pure-virtual slots are not counted. |
| `tools/progress.py [--write] [--no-rebuild]` | Computes the README progress table (bytes per binary-map region included) and writes it between the `progress:begin/end` markers. It refuses to write while a check fails. |
| `rebuild/rebuild.py -q --allow-kept` | Relinks the compiled functions into the split assembly and checks the SHA-1 of the result. |
| `tools/check_repo.py` | Rejects game data, binaries and build output (also the pre-commit hook). |
| `tools/extract_rtti.py`, `tools/gen_rtti_stubs.py` | Extract RTTI and vtables from the binary, and generate the `src/rtti/` probe stubs. |

`check_all.py` and `progress.py` default the `WHIRL_*` variables themselves. Set them yourself to run
the other tools directly.

## Analysis tools (`tools/analysis/`, venv `python3`)

| Tool | What it does |
| :--- | :--- |
| `inspect_tu.py --class C \| --range A B \| --func A [--m2c] [--dis]` | Functions of a class or range: size, match status, calls, strings, floats, `$a0` field accesses, C++ drafts for trivial functions, m2c output. |
| `scan_candidates.py --level {1,2,3} [--limit N] [--class S]` | Unmatched candidates: leaf getters/setters, one-call wrappers, or vtable methods sorted by size. |
| `map_tus.py [--filter S] [--class C]` | Groups the 182 vtables into probable translation units and infers `_vptr` offsets and fields. |
| `diff_func.py file.cpp <mangled> [--all] [-D X] [--variants v.json]` | Side-by-side R5900 diff of one repository function, or a batch of source variants (`{"target": "...", "candidates": [...]}`). |
| `scratch_cc.py snippet.cpp\|- [--func S] [--vs ADDR] [--asm] [--regs] [-D X]` | Compiles a loose snippet in `build/scratch/` with the exact flags of `verify.py` (it can include repository headers). Shows its disassembly with relocations, or a side-by-side diff against any game address (`--vs`), GCC's `.s` (`--asm`), and the register-allocation table (`--regs`). |
| `find_pattern.py '<re1>; <re2>; ...' [--range A B] [--context N] [--count]` | Searches `.text` for a sequence of instructions (one regex per instruction, `*` matches any). Each hit is labelled with the nearest known symbol. About 0.5 s for the whole binary. Put the pattern in single quotes so the shell keeps `\$`. |

Examples (venv active, from the repository root):

```bash
python3 tools/analysis/scratch_cc.py idea.cpp --func revived --vs 117340   # does this idea match?
python3 tools/analysis/scratch_cc.py idea.cpp --func revived --regs        # why these registers?
printf 'struct S { int x; void f(); };\nvoid S::f() { x = 3; }\n' | python3 tools/analysis/scratch_cc.py - --asm
python3 tools/analysis/find_pattern.py 'b\S*; *; sw; nop; jr \$ra; nop'    # same idiom elsewhere?
python3 tools/analysis/find_pattern.py 'jr \$ra; *' --count                # 7069 returns
```
