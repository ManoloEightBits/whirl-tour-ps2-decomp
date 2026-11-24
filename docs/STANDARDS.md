# Standards
Same rules as the castaway-ps2-decomp project, adapted:
- Only matching code goes in `src/`; unfinished work sits under `#ifdef NON_MATCHING` or on a branch.
- Never commit: ISO/ELF/SLUS files, extracted assets, compilers, Ghidra projects, splat output, build output. `.gitignore`, `tools/check_repo.py` and the pre-commit hook enforce it.
- Compiler is GCC 2.95.3: no `nullptr`, `auto`, range-for.
- Names come from RTTI/strings; unknown ones are `func_<addr>` / `field_0x<off>`.
- Commit/push only with the owner's go-ahead.
