# Tools and workflow

There are two groups of tools, both in this repository:

- **Verification tools** (`tools/`, `rebuild/`). They use the Python standard library only and run with
  plain `python3`. They decide whether the work is correct. Nothing third-party runs in the same
  process as the proprietary compiler, and the compiler never gets network access: before it runs,
  `verify.enter_sandbox()` re-executes the tool inside a network namespace with only `lo`
  (`bwrap --unshare-net`, or `unshare -rn` where `bwrap` is missing). If neither works, the tool
  stops. On Ubuntu with `apparmor_restrict_unprivileged_userns=1`, `unshare -rn` is refused but
  `bwrap` works through the distribution's own AppArmor profile, so no system change is needed.
- **Analysis tools** (`tools/analysis/`). They help find and match functions, and need `rabbitizer`,
  `m2c` and `splat64` (pinned in `tools/analysis/requirements.txt`). They read the game from your
  local files at run time and never store any of it in the repository.

All of them keep their output short. They print summaries by default, and the full detail only with a
flag. Use them instead of reading raw disassembly or large dumps.

## Setup

System packages: `wine` (runs the compiler), `bubblewrap` (network sandbox) and
`binutils-mips-linux-gnu` (used by `rebuild.py`).

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

1. **Pick a target:** look at `docs/MAP.md` (what each block of the binary holds and how much is matched),
   run `m2c_sweep.py report` (after one `m2c_sweep.py run`: functions whose raw m2c draft already
   matches or nearly does), `scan_candidates.py --level 1|2|3`, `map_tus.py --class X` or
   `inspect_tu.py --class X` / `--range A B` (that one includes m2c drafts).
   For a run of trivial methods of one class, `gen_accessors.py --range A B --class X` drafts the C++.
2. **Write the C++** in `src/game/`, and add the address to `config/symbols.txt`. For a class with a
   vtable, also add a line to `config/vtables.txt`, and add the class to `HAND_WRITTEN` in
   `tools/gen_rtti_stubs.py`.
3. **Diff:** run `diff_func.py src/game/X.cpp <mangled>`. To try several rewrites in one run, use
   `--bodies -` with only the new function bodies on stdin, separated by `---` lines (the tool finds
   the definition by name; `--apply` keeps the best one). `--variants file.json` replaces any other
   snippet of the file. Write a first draft from the m2c output and let the diff show what is
   left, instead of reading the whole disassembly (`--dis` prints every instruction). For tables in
   data (vtables, jump tables, keyword tables), use `dump_data.py`, not a hex dump.
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
| `tools/check_all.py [--no-rebuild]` | Runs `verify -q`, `verify_vtables -q`, `rebuild -q` (requiring 0 kept/unlinked functions) and `check_repo`; one summary line each. |
| `tools/verify.py [-q\|-v] [file.cpp ...]` | Builds `src/` with the game's compiler and compares every function with `SLUS_204.89` (verifying `R_MIPS_26`, `R_MIPS_HI16` and `R_MIPS_LO16` relocations whose target is in `config/symbols.txt`, and reporting the remaining local `.rodata` relocations deferred to `rebuild.py`). `-v` lists each match with address and size. A full run (no files, no `-D`) also writes the list of matches to `build/matched.txt`, which the analysis tools read. Its `assemble()` (also used by `verify_vtables`, `rebuild` and `scratch_cc`) adds the retail assembler's `mtc1` pair nops first (see [MATCHING.md](MATCHING.md)). |
| `tools/verify_vtables.py [-q\|-v]` | Compares each vtable declared in `config/vtables.txt` slot by slot. Destructor and pure-virtual slots are not counted. |
| `tools/progress.py [--write] [--no-rebuild]` | Computes the README progress table (bytes per binary-map region included, deriving RTTI class and vtable slot denominators from the binary) and writes it between the `progress:begin/end` markers. It refuses to write while a check fails. |
| `rebuild/rebuild.py [-q]` | Relinks all compiled C++ functions into the split assembly and checks the SHA-1 of the result. Local `.rodata` (strings, float constants, jump tables) is kept only where it equals the game's bytes at the address the game's code uses; a jump table ends where the next relocated word belongs to another function's section. |
| `tools/check_repo.py [--staged\|--self-test]` | Rejects game data, target SHA-1 matches, pasted splat disassembly, binaries and build output (also the pre-commit hook). Runs a built-in negative-control self-test on every invocation. |
| `tools/extract_rtti.py`, `tools/gen_rtti_stubs.py` | Extract RTTI and vtables from the binary, and generate the `src/rtti/` probe stubs. |

`check_all.py` and `progress.py` default the `WHIRL_*` variables themselves. Set them yourself to run
the other tools directly.

## Analysis tools (`tools/analysis/`, venv `python3`)

| Tool | What it does |
| :--- | :--- |
| `inspect_tu.py --class C \| --range A B \| --func A [--m2c] [--dis]` | Functions of a class or range: size, match status, calls, strings, floats, `$a0` field accesses, C++ drafts for trivial functions, m2c output. An address inside a function is reported as such and replaced by that function's start. |
| `scan_candidates.py [--level {1,2,3} \| --twins] [--limit N] [--class S]` | Unmatched candidates: leaf getters/setters (`--level 1`), one-call wrappers (`--level 2`), vtable methods sorted by size (`--level 3`), or structural twin families grouped by normalized instruction skeleton (`--twins`). |
| `coverage.py [--region game\|physics\|runtime\|all] [--top N] [--block KB] [--map FILE]` | What is left, per region of the binary map: matched/total functions and bytes, unmatched functions in an RTTI vtable, unmatched bytes by function size, the largest unmatched functions, and the address blocks with the most unmatched bytes (labelled with nearby RTTI classes). `--map docs/MAP.md` writes the per-block map instead: share matched, RTTI classes, our files and the keywords each block's code uses. |
| `gen_accessors.py --range A B --class C [--data-start OFF] [--all]` | Drafts a class's trivial methods in a range (getters, address getters, setters, float add/subtract, empty methods, constants): declarations with the field layout the accesses imply, definitions, and `symbols.txt` lines. Marks vtable slots and lists what it does not recognise. `--all` includes matched functions, to check it against hand-written code. |
| `map_tus.py [--filter S] [--class C]` | Groups the RTTI vtables (193) into probable translation units and infers `_vptr` offsets and fields. |
| `diff_func.py file.cpp <mangled> [--all] [-D X] [--bodies f\|- \| --variants v.json] [--apply]` | Side-by-side R5900 diff of one repository function, or a batch of candidates with one line each (diff count and first differing offset). `--bodies`: only function bodies, separated by `---` lines; a `@@` line puts the text above it before the function (inline helpers). `--variants`: `{"target": "...", "candidates": [...]}` for any snippet. `--apply` writes the best candidate into the file. |
| `scratch_cc.py snippet.cpp\|- [--func S] [--vs ADDR] [--asm] [--regs] [-D X] [--cflag F]` | Compiles a loose snippet in `build/scratch/` with the exact flags of `verify.py` (it can include repository headers). Shows its disassembly with relocations, or a side-by-side diff against any game address (`--vs`), GCC's `.s` (`--asm`), and the register-allocation table (`--regs`). `--cflag` adds a compiler flag for experiments (this is how `-ffast-math` was confirmed). |
| `dump_data.py ADDR [-n N] [--vtable] [--string]` | Words at a data address with what each points to: a symbol (and whether it matches), a string, the function and offset of a jump-table target, or a float. `--vtable` lists a vtable's slots. |
| `m2c_sweep.py run\|report\|show [--region R] [--range A B] [--max-size N] [--status S]` | Batch run, left alone (the whole binary in minutes, 16 jobs): for each unmatched function it compiles m2c's `--valid-syntax` C draft with the game's `cc1` at `verify.py`'s flags and compares it with the game. Results (`results.tsv`) and drafts go to `../whirl-tour-work/sweep` (`WHIRL_SWEEP`); the run resumes where it stopped (`--redo` to redo). Status: `match` (the raw draft gives the game's bytes), `regs` (same mnemonics, only registers or immediates differ), `diff` (score = mnemonic similarity 0..1), `asm` (VU0/MMI instructions m2c cannot express), `m2c-error`, `cc-error`. `report` drops functions matched since and ranks the rest; `show ADDR` prints one result and its draft. The drafts are C, a starting point for the C++ and its names, not code to commit. m2c's input names the globals (`lui`/`%lo` pairs become `%hi(sym)`/`%lo(sym)`, with the name from `symbols.txt` or `D_<addr>`) and carries the jump tables of switches (`jtbl_<addr>`), and m2c runs through `m2c_ee.py`. When a draft does not compile, a few mechanical fixes are tried and listed in the note: a callee called with varying argument counts loses its prototype (`printf`), an untyped `*(a + b)` is read as `*(s32 *)`, undeclared stack slots (`sp14`) are declared. |
| `m2c_ee.py <m2c arguments>` | m2c with fixes for ee-gcc code (also applied by `inspect_tu.py --m2c` and `m2c_sweep.py`): the address of the stack slot at offset 0 (`daddu $a1, $sp, $zero`) is `&sp0`, not a bare `sp` passed as an outgoing argument. |
| `keyword_fields.py [--range A B \| --func A] [--class C] [--all] [--tables]` | Names for fields from the game's script parsers: for each call to `UnkParser::func_001C3270` (read a float) or `func_001C2C78` (read a string) it prints the key string (`"speed"`, `"accmax"`, ...) and where the value goes as an incoming argument plus offset (`arg1+0x1C`), following registers in address order and a stack buffer to the store that copies it. `--tables` adds the `{id, "name"}` keyword tables passed to `func_001C1D28`, which name the cases of the switch on `mToken14`. A hint: match the object to a struct by offsets and types, keep the offset in the name when a key repeats. |
| `find_pattern.py '<re1>; <re2>; ...' [--range A B] [--context N] [--count]` | Searches `.text` for a sequence of instructions (one regex per instruction, `*` matches any). Each hit is labelled with the nearest known symbol. About 0.5 s for the whole binary. Put the pattern in single quotes so the shell keeps `\$`. |

A function counts as matched when it is in `build/matched.txt`. `config/symbols.txt` is not enough: it
also names functions that matched code only calls. `inspect_tu.py` shows those as
`UNMATCHED (named ...)`. Without `build/matched.txt` (run `tools/check_all.py` once), the tools fall back
to `symbols.txt` and print a note.

Examples (venv active, from the repository root):

```bash
python3 tools/analysis/diff_func.py src/game/Scooter.cpp SetVec194__7ScooterP5Vec3f --bodies - <<'EOF'
    mVec194.x = v->x; mVec194.y = v->y; mVec194.z = v->z;
---
    Vec3f *d = &mVec194; d->x = v->x; d->y = v->y; d->z = v->z;
EOF
python3 tools/analysis/scratch_cc.py idea.cpp --func revived --vs 117340   # does this idea match?
python3 tools/analysis/scratch_cc.py idea.cpp --func revived --regs        # why these registers?
printf 'struct S { int x; void f(); };\nvoid S::f() { x = 3; }\n' | python3 tools/analysis/scratch_cc.py - --asm
python3 tools/analysis/find_pattern.py 'b\S*; *; sw; nop; jr \$ra; nop'    # same idiom elsewhere?
python3 tools/analysis/find_pattern.py 'jr \$ra; *' --count                # 7069 returns
python3 tools/analysis/dump_data.py 284090 --vtable                        # a vtable's slots
python3 tools/analysis/dump_data.py 284460 -n 8                            # a switch's jump table
```
