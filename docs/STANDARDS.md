# Standards

Rules adapted from `castaway-ps2-decomp` and the `BFM-decomp` day-one decomp guide:

## Byte gate & matching
- Only byte-identical matching code goes in `src/`; unfinished drafts sit under `#ifdef NON_MATCHING` or on a branch.
- Every matched function must also link cleanly in `rebuild/rebuild.py` (0 unlinked/kept functions) so the rebuilt ELF reproduces `pkg/target.sha1`.
- Compiler is SN Systems `ee-gcc 2.95.3-114` (`-O2 -G0 -fno-exceptions -ffast-math`, RTTI enabled): no `nullptr`, `auto`, or range-for.

## Readability at draft time
- **Canonical types & no raw address casts:** One definition per structure across `include/` and `src/game/*.h`, with field widths/signedness proven by the instructions. Never bank raw address casts (`*(int *)0x0026...`); declare every global or function as a typed symbol and list its address in `config/symbols.txt`.
- **Evidence-based names:** Class and vtable names come from RTTI and `.rodata` strings; unknown functions and fields use address/offset names (`func_<addr>`, `field_0x<off>`, `mField<off>`).
- **Translation-unit layout:** Keep separate original TUs in separate `.cpp` files when their key functions or `.rodata` islands are distinct, so GCC emits inline members and `__tf` helpers in the same TU as the retail build.

## What never goes in the repo (ROM firewall)
- Never commit: ISO/ELF/SLUS files, extracted assets, proprietary compilers, Ghidra databases (`.gpr`/`.rep`), `splat` disassembly output (`asm/`, `assets/`), pasted `splat` disassembly listings, or `build/` artifacts.
- `.gitignore`, `tools/check_repo.py` (with its built-in negative-control self-test) and `.githooks/pre-commit` enforce this on every check and commit.
- Commit/push only with the owner's go-ahead.
