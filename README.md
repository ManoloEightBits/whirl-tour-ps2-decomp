# Whirl Tour (PS2) decompilation

A hobby reverse-engineering project for the US PS2 release of *Whirl Tour* (`SLUS_204.89`). The goal is clean, from-scratch C++ source code that compiles and links into a byte-identical copy of the original executable.

**This repository contains no game data, assets, or proprietary binaries.** You must supply your own legally obtained copy of the disc image to extract `SLUS_204.89` and run the verification suite. `pkg/target.sha1` stores only the SHA-1 checksum of the target binary.

---

## Decompilation Progress

<!-- progress:begin -->
| Metric | Matched / Confirmed | Total in `.text` | Share | Progress |
| :--- | ---: | ---: | ---: | :--- |
| **Total `.text` bytes** | **81,500 B** | 1,401,448 B | **5.815%** | `██░░░░░░░░░░░░░░░░░░` |
| **Game logic bytes** (`0x100000..0x1C62CF`) | **77,096 B** | 811,728 B | **9.498%** | `██░░░░░░░░░░░░░░░░░░` |
| **Matched functions (`verify.py`)** | **1640** | ~7,125 | **23.018%** | `█████░░░░░░░░░░░░░░░` |
| **Confirmed vtable slots (`verify_vtables.py`)** | **246** | ~889 | **27.672%** | `██████░░░░░░░░░░░░░░` |
| **Confirmed RTTI classes (`vtables.txt`)** | **51** | 193 | **26.425%** | `██████░░░░░░░░░░░░░░` |
| **Full binary relink (`rebuild.py`)** | **1640 linked** | `02f39f20...0744` | **SHA-1 MATCH** | `████████████████████` |
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
| **Pickups (`Pickup`, `KeyPickup`, +9)** | `EnvObj`, `Pickup`, `PickupDef` + 10 subclasses | 58 / 59 | 22 / 22 | `█████████░` **98%** (`KeyPickup` and 9 subclasses 100%, all vtables confirmed, `Pickup::Update` and the `PickupDef` parser matched; only `Pickup::Pickup` left, in `NON_MATCHING`) |
| **Front-End UI (`FEScreen` hierarchy)** | `FEScreen` + all 14 `FE*Screen` subclasses, `FEMenu`, `FESlider`, `FEOwner` | 121 / ~160 | 105 / 112 | `████████░░` **76%** (`FEMcScreen`, `FEQuitScreen` & `FETrickScreen` 100%, `FEMenu` 14 of 15, the options menu and most draw functions; all 15 vtables confirmed; screens, menus and options named from play, see `TODO.md`) |
| **Game context & progress (`GameCtx`)** | `GameCtx` (no RTTI; the 0x6E0-byte context at `gGameCtx262250`) | 65 / ~120 | — | `█████░░░░░` **54%** (`GameCtx.cpp`, `0x00153C10..0x001566F8`: life cycle, goals and level flags, unlocks, mode tests, Versus time, each player's character, scooter and controller, collectibles; `UnlockScooterGlobal` in `NON_MATCHING`; the constructor, its filler and `0x00153C10..0x00154E80` left) |
| **Text objects (`TextObj`)** | `TextObj` (no RTTI) | 28 / 52 | — | `█████░░░░░` **54%** (`0x00198E48..0x0019B800`: create, init, release and draw in `TextObj.cpp`, the rest still in `blocks/Block_00198000.cpp`) |
| **Player & Scooter (`Player`, `Scooter`)** | `Player`, `Scooter`, `UnkObj11F` (no RTTI; names are ours) | 183 / 184 | — | `█████████░` **99%** (Player `0x00122D08..0x00123CCF`, 94 functions including 49 wrappers/getters and the 13 `player_*` collision callbacks, `UnkObj11F` `0x0011F8E8..0x0011FA40`, 13 functions, and Scooter `0x0017E0E0..0x0017F8E8`, 74 functions; only `Scooter::ConsumeAdrenaline` is left, in `NON_MATCHING`) |
| **Animated Model & Clip Helpers (`AnimModel`)** | `UnkActor11A`, `UnkTable11A8`, `UnkDef11AB`, `UnkSkel1B6`, `UnkKey1B76`, `UnkModel1B7`, `UnkClip1B7`, `UnkAnim1B8`, `UnkScene1B9`, `UnkTex1BA` (no RTTI) | 142 / ~165 | — | `████████░░` **85%** (`0x0011A198..0x0011AC98`, `0x001B6950..0x001BAA90`) |
| **Tricks System (`Tricks`)** | `UnkTrickScores`, `UnkTrickDef`, `UnkTrickSeq`, `UnkTrickState`, `UnkObj125F` (no RTTI) | 35 / 59 | — | `██████░░░░` **59%** (`0x001255C8..0x00125F70`: score table getters, trick lookup by name, 12 trick definition getters, sequence & state accessors; `tricklist` parser in `NON_MATCHING`) |
| **Motion & Interpolation Controllers** | `MotionCtrl`, `IP_PosCtrl`, `IP_RotCtrl`, `IP_AnimCtrl`, `MBCtrl`, `ScootCtrl` (+ IVP bases `IVP_Controller`, `IVP_Controller_Independent`) | 52 / ~65 | 36 / 42 | `████████░░` **80%** (all vtables confirmed; `IP_PosCtrl`, `MBCtrl` and `ScootCtrl` 100% including constructors and accessors; the simulation step of `MotionCtrl`, `IP_RotCtrl` and `IP_AnimCtrl` left) |
| **Collision & Event Listeners** | `DD_Event_Listener`, `DD_Collision_Listener`, `Global_Phantom_Listener`, `ScootCL`, `MBCL`, `LunActCL`, `MarActCL`, `AI_PedestrianCL` | 57 / ~67 | 31 / 40 | `█████████░` **85%** (all 8 listeners 100%, `LunActCL`/`MarActCL` constructors and `LunAct`/`MarAct`/`UnkBody` accessors matched, and the whole `DD_Event_Listener` TU `0x00116B00..0x00117727`; IVP base classes `IVP_Listener_Object`, `IVP_Listener_Collision` & `IVP_Listener_Phantom` also 100%) |
| **AI & Boss Attacks** | `AI_Agent`, `AI_Pedestrian`, `AI_Race`, `AI_Vehicle`, `AI_Boss`, `AI_Attack*` | 191 / ~340 | 39 / 73 | `██████░░░░` **56%** (RTTI `__tf` matched; the vtables of `AI_Agent` and its four subclasses confirmed; the non-virtual accessors of `AI_Pedestrian` (43), `AI_Race` (43), `AI_Vehicle` (21) and `AI_Boss` (40), plus 14 short `AI_Race`/`AI_Vehicle` methods) |
| **Address blocks (`src/game/blocks/`)** | 102 `UnkObj<addr>` classes (no RTTI; layout = the fields their methods use) | 539 / 539 | — | `██████████` **100%** of these batches (raw m2c drafts found by `tools/analysis/m2c_sweep.py`, in four phases: free functions (empty functions, constants, one-call wrappers, allocate-then-construct helpers), methods that only touch `this`'s fields, functions on globals, strings and float constants, and hand-fixed drafts (see `TODO.md`); one file per 16 KB block, to be moved to their TUs) |
| **Single-inheritance RTTI (`src/rtti/`)** | 77 polymorphic classes | 77 / 77 | — | `██████████` **100%** (probe-generated `__tf*` functions) |

For a block-by-block view of the whole binary (what each area holds, how much is matched), see
[docs/MAP.md](docs/MAP.md).

This table only lists the classes work has started on: about 1,250 of the ~3,700 functions in game code.
Its bars measure those classes, not the binary. `tools/analysis/coverage.py` shows what is left; on
2026-11-24 it reported:

| Region | Unmatched | In an RTTI vtable | Where the bytes are |
| :--- | ---: | ---: | :--- |
| Game code | 781 KB in 3,336 functions | 36 KB (76 functions) | 70% in functions of 257 B to 4 KB; spread evenly, mostly in code with no RTTI class nearby (`0x0011..0x0018`) |
| Physics engine (`IVP_*`) | 400 KB in 2,018 functions | 54 KB (315 functions) | 62% in functions of 257 B to 4 KB |
| Runtime & system libraries | 185 KB in 966 functions | 2 KB | libgcc/libc and Sony SDK libraries; no `.a` archives in the compiler packages |

Functions of 64 B or less are about 1,470 of the game's unmatched functions but only 5.6% of its
unmatched bytes, so getters and wrappers barely move the total.

---

## Technical Findings

- **Target binary:** ELF32 MIPS R5900 (`SLUS_204.89`, entry `0x00100008`), stripped of symbol tables, but compiled **with C++ RTTI enabled**: 212 `__tf*` RTTI functions and 193 virtual function tables (8-byte slots: `{s16 delta, s16 index, void *func}`) are present in `.text` and `.rodata` (`tools/extract_rtti.py`).
- **Compiler & flags:** SN Systems ProDG `ee-gcc 2.95.3 build 1.14` (`ee-gcc2.95.3-114`) with `-O2 -G0 -fno-exceptions -ffast-math` (RTTI enabled; `-ffast-math` because the game has bare `sqrt.s` and `min.s` where plain `sqrtf()` and `a < b ? a : b` compile to them only with it, and every earlier match is unchanged by it), assembled with `ps2eeas.exe` from the `ee-gcc 2.95.2-273a` package (which inserts a `nop` after `mtc1` before a dependent FP instruction and does not pad short backward loops). The retail assembler, which none of the available packages reproduces, also inserts that `nop` when the next instruction reads the *partner* register of the even/odd FP pair. `tools/verify.py` adds those nops to GCC's output before assembling (see `docs/MATCHING.md`).
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
- `AGENTS.md` — How coding agents work here (what to read, the tools that keep output small, the loop, when to
  park a function); `CLAUDE.md` and `GEMINI.md` import it.
- `docs/MAP.md` — Block-by-block map of the binary (generated by `tools/analysis/coverage.py --map`).
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

Compilers (from [decompme/compilers](https://github.com/decompme/compilers)), disc images, and extracted binaries must live outside this repository (e.g. `../whirl-tour-work`). `tools/verify.py` automatically runs the Windows compiler binaries under Wine inside an isolated, networkless Linux namespace (`bwrap --unshare-net`, or `unshare -rn` where `bwrap` is missing; with neither, the tools stop).

---

## License & Disclaimer

The original build scripts, analysis tools, and documentation in this repository are licensed under the [MIT License](LICENSE). No original game code, assets, or third-party proprietary materials are distributed here.

*Whirl Tour* is a trademark of its respective owners. This independent educational reverse-engineering project is not affiliated with or endorsed by them.
