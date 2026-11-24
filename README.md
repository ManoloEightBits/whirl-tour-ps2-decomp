# Whirl Tour (PS2) decompilation

A hobby reverse-engineering project for the US PS2 release of *Whirl Tour* (`SLUS_204.89`). The goal is clean, from-scratch C++ source code that compiles and links into a byte-identical copy of the original executable.

**This repository contains no game data, assets, or proprietary binaries.** You must supply your own legally obtained copy of the disc image to extract `SLUS_204.89` and run the verification suite. `pkg/target.sha1` stores only the SHA-1 checksum of the target binary.

---

## Decompilation Progress

<!-- progress:begin -->
| Metric | Matched / Confirmed | Total in `.text` | Share | Progress |
| :--- | ---: | ---: | ---: | :--- |
| **Total `.text` bytes** | **19,064 B** | 1,401,448 B | **1.360%** | `█░░░░░░░░░░░░░░░░░░░` |
| **Game logic bytes** (`0x100000..0x1C62CF`) | **14,984 B** | 811,728 B | **1.846%** | `█░░░░░░░░░░░░░░░░░░░` |
| **Matched functions (`verify.py`)** | **257** | ~7,125 | **3.607%** | `█░░░░░░░░░░░░░░░░░░░` |
| **Confirmed vtable slots (`verify_vtables.py`)** | **80** | ~820 | **9.756%** | `██░░░░░░░░░░░░░░░░░░` |
| **Confirmed RTTI classes (`vtables.txt`)** | **24** | 182 | **13.187%** | `███░░░░░░░░░░░░░░░░░` |
| **Full binary relink (`rebuild.py`)** | **234 linked** | `02f39f20...0744` | **SHA-1 MATCH** | `████████████████████` |
<!-- progress:end -->

### Binary `.text` Map (`0x00100000..0x00256268`)

| Region | Address Range | Size | Share | Functions | RTTI Vtables | Notes |
| :--- | :--- | ---: | ---: | ---: | ---: | :--- |
| **Game code** | `0x00100000..0x001C62CF` | 792.7 KB | 57.9% | ~3,907 | 50 | Gameplay, UI, AI, audio, rendering, controllers |
| **Physics engine (`IVP_*`)** | `0x001C62D0..0x00228F2F` | 395.1 KB | 28.9% | ~2,157 | 122 | Rigid-body physics, collision solvers, constraints |
| **Runtime & system libraries** | `0x00228F30..0x00256268` | 180.8 KB | 13.2% | ~1,061 | 10 | Static C/C++ runtime (`libgcc`, `libc`) and system libs |

### Subsystem Breakdown (Game Code)

| Subsystem / Translation Unit | Classes | Matched Functions | Vtable Slots | Status |
| :--- | :--- | ---: | ---: | :--- |
| **Collision Filter (`CollFilt`)** | `CollFilt`, `IVP_Collision_Filter` | 7 / 7 | 2 / 2 | `██████████` **100%** |
| **Pickups (`Pickup`, `KeyPickup`, +9)** | `EnvObj`, `Pickup` + 10 subclasses | 53 / 59 | 22 / 22 | `█████████░` **90%** (9 subclasses 100%, all vtables confirmed; 6 functions left in the TU) |
| **Front-End UI (`FEScreen` hierarchy)** | `FEScreen`, `FEQuitScreen`, `FEStartScreen`, `FETrickScreen` (+10 pending) | 31 / ~160 | 28 / 112 | `███░░░░░░░` **25%** (`FEQuitScreen` & `FETrickScreen` 100%) |
| **Player & Scooter (`Player`, `ScootCtrl`)** | `Player`, `ScootCtrl` | 46 / ~90 | 0 / 7 | `█████░░░░░` **51%** (stat/boost/adrenaline/health methods matched) |
| **Motion & Interpolation Controllers** | `MotionCtrl`, `IP_PosCtrl`, `IP_RotCtrl`, `IP_AnimCtrl`, `MBCtrl` | 4 / ~45 | 0 / 35 | `█░░░░░░░░░` **9%** (RTTI `__tf` matched) |
| **Collision & Event Listeners** | `DD_Event_Listener`, `DD_Collision_Listener`, `ScootCL`, `MBCL`, `LunActCL`, `MarActCL` | 28 / ~55 | 24 / 33 | `█████░░░░░` **51%** (`DD_Event_Listener`, `DD_Collision_Listener`, `MBCL`, `ScootCL`, `LunActCL` & `MarActCL` 100%; IVP base classes `IVP_Listener_Object` & `IVP_Listener_Collision` also 100%) |
| **AI & Boss Attacks** | `AI_Agent`, `AI_Pedestrian`, `AI_Race`, `AI_Vehicle`, `AI_Boss`, `AI_Attack*` | 9 / ~340 | 0 / 73 | `░░░░░░░░░░` **3%** (RTTI `__tf` matched) |
| **Single-inheritance RTTI (`src/rtti/`)** | 87 polymorphic classes | 87 / 87 | — | `██████████` **100%** (probe-generated `__tf*` functions) |

---

## Technical Findings

- **Target binary:** ELF32 MIPS R5900 (`SLUS_204.89`, entry `0x00100008`), stripped of symbol tables, but compiled **with C++ RTTI enabled**: 199 `__tf*` RTTI functions and 182 virtual function tables (8-byte slots: `{s16 delta, s16 index, void *func}`) are present in `.text` and `.rodata` (`tools/extract_rtti.py`).
- **Compiler & flags:** SN Systems ProDG `ee-gcc 2.95.3 build 1.14` (`ee-gcc2.95.3-114`) with `-O2 -G0 -fno-exceptions` (RTTI enabled), assembled with `ps2eeas.exe` from the `ee-gcc 2.95.2-273a` package (which inserts a `nop` after `mtc1` before a dependent FP instruction and does not pad short backward loops). The retail assembler, which none of the available packages reproduces, also inserts that `nop` when the next instruction reads the *partner* register of the even/odd FP pair. `tools/verify.py` adds those nops to GCC's output before assembling (see `docs/MATCHING.md`).
- **Register saving convention:** Game and physics code (`0x00100000..0x00228F2F`) saves 128-bit registers (`sq`/`lq`) in function prologues; static runtime libraries (`0x00228F30..0x00256268`) save 64-bit registers (`sd`/`ld`).

---

## Repository Layout

- `src/game/` — Decompiled C++ game classes and methods.
- `src/rtti/` — Probe sources matching single-inheritance `__tf*` RTTI functions (`tools/gen_rtti_stubs.py`).
- `include/common/` — Fixed-width R5900 types and math structs (`types.h`).
- `config/symbols.txt` — Function and data symbol addresses in `SLUS_204.89`.
- `config/vtables.txt` — Virtual function table addresses and declaring headers.
- `config/splat/` — Configuration for splitting `SLUS_204.89` with `splat`.
- `tools/` — Verification scripts, standard library only (`verify.py`, `verify_vtables.py`, `check_all.py`, `progress.py`, `extract_rtti.py`, `check_repo.py`).
- `tools/analysis/` — Analysis tools that need a venv (`requirements.txt`): `inspect_tu.py`, `scan_candidates.py`, `map_tus.py`, `diff_func.py`, `scratch_cc.py`, `find_pattern.py`.
- `rebuild/` — Full ELF/binary relinker (`rebuild.py`) that splices compiled C++ functions into the split assembly and verifies the final SHA-1.
- `docs/STANDARDS.md` — Coding, verification, and repository cleanliness rules.
- `docs/TOOLS.md` — Setup and usage of every tool and the step-by-step loop for matching a function.
- `docs/MATCHING.md` — Compiler quirks and source patterns needed to match ee-gcc 2.95.3 output (register allocation, scheduling, layout).

---

## Verification & Usage

```bash
git config core.hooksPath .githooks
export WHIRL_COMPILERS=<dir with ee-gcc2.95.3-114 and ee-gcc2.95.2-273a>
export WHIRL_SLUS=<path to your extracted SLUS_204.89>
export WHIRL_SPLIT=<path to splat output dir>

# Run all checks (byte-level function match, vtable slot verification, full binary rebuild, repo hygiene):
python3 tools/check_all.py

# Recompute the progress table above and write it into this README:
python3 tools/progress.py --write
```

Compilers (from [decompme/compilers](https://github.com/decompme/compilers)), disc images, and extracted binaries must live outside this repository (e.g. `../whirl-tour-work`). `tools/verify.py` automatically runs the Windows compiler binaries under Wine inside an isolated, networkless Linux namespace (`unshare -rn`).

---

## License & Disclaimer

The original build scripts, analysis tools, and documentation in this repository are licensed under the [MIT License](LICENSE). No original game code, assets, or third-party proprietary materials are distributed here.

*Whirl Tour* is a trademark of its respective owners. This independent educational reverse-engineering project is not affiliated with or endorsed by them.
