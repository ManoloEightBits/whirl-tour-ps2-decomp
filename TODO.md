# TODO

What to do next. What is already done lives in the README (progress tables), `docs/MAP.md` (per-block
map of the binary, regenerated with `tools/analysis/coverage.py --map docs/MAP.md`) and `git log`.

## Open decisions

- **IVP source (29% of `.text`).** Many classes are Ipion Virtual Physics (`IVP_*`). Check whether an
  official IVP source release exists, its exact version and its license, and decide whether to only
  consult it or copy from it. Copies that come from leaks must not be used. Until then nothing from it is
  in this repo. If there is no usable release, IVP is done by hand like game code; decide its priority.
- **Runtime region (13%).** libgcc/libc might be built from their GPL/BSD sources with the same compiler;
  the Sony SDK libraries stay assembly. Decide whether progress should also be reported without them.
- **decomp-permuter.** Setting it up (Wine `cc1plus` plus the `mtc1` pair nops of `verify.assemble`) would
  search the register-allocation cases below automatically. Its output is a hint, to be rewritten into
  readable code, not code to commit as is.

## Next, in order

0. **Raw m2c matches from `tools/analysis/m2c_sweep.py`.** The first sweep (2026-11-25, 185 s) found 1119
   unmatched functions whose raw m2c draft already compiles to the game's bytes (618 game, 466 physics, 35
   runtime; 549 are <= 16 B) and 263 more that differ only in registers or immediates. Game code only for now.
   - **Phase 1 done:** the 226 game functions whose draft touches no fields (empty functions, constants,
     one-call wrappers, allocate-then-construct helpers) are in `src/game/blocks/Block_<16 KB block>.cpp`
     with address names; move them to their TU's file when one is identified. Left out on purpose: the 11
     AI vtable slots (`0x00106568`, `0x0010B910`/`B918`/`BA20`/`BB88`/`BD60`, `0x0010E310`/`E318`/`E328`,
     `0x0015EE28`, `0x0018D270`; see step 2), `__builtin_new`/`delete`/`vec_new`/`vec_delete`
     (`0x00100BE8..0x00100C48`, the game's own `operator new`/`delete`), `EnvObjCleanup14FB70` and its 4
     callers plus `0x00183CB8` (they need `EnvObj`/`UnkModel1B7` types), and 16 functions at addresses
     4 mod 8 (`0x00154EDC..0x00154F6C` float constants, `0x001C4084..0x001C40AC` int constants): they
     match in `verify.py`, but cc1plus aligns every function to 8 (`.align 3`), so `rebuild.py` cannot place
     them; find out how the original got 4-byte alignment there before adding them.
   - **Phase 2:** the ~354 whose draft reads or writes fields. They need the struct or class each pointer is
     (one definition per structure, no raw casts), so take them TU by TU with
     `m2c_sweep.py report --range A B --status match` and `gen_accessors.py`. Lead to check:
   the calls in `0x00168A40` use OpenGL enum values (`0x1406` GL_FLOAT, `0x8074` GL_VERTEX_ARRAY, `0xDE1`
   GL_TEXTURE_2D, `0xBE2` GL_BLEND), so `0x001A1938..0x001A4930` looks like a GL-style render layer
   (`glVertexPointer`/`glEnableClientState`/`glDrawArrays`-like); confirm from more callers before naming.
1. **Trivial batches with `tools/analysis/gen_accessors.py`.** About 380 leaf getters/setters are left
   (`scan_candidates.py --level 1`). Take one class TU at a time (ranges in `docs/MAP.md`), review the
   draft (names with evidence, field types, the `+0x...` that are pointers), and leave the vtable slots
   for step 2. Done: `AI_Pedestrian`, `AI_Race`, `AI_Vehicle`, `AI_Boss`, `Player`, `Scooter`,
   `LunAct`/`MarAct`/`UnkBody`, `IP_PosCtrl`/`MotionCtrl`/`IP_RotCtrl`/`IP_AnimCtrl`/`MBCtrl`/`ScootCtrl`,
   `FEScreen`, `UnkObj11F`, `UnkActor11A`/`UnkDef11AB`/`UnkSkel1B6`/`UnkKey1B76`/`UnkModel1B7`/`UnkClip1B7`/`UnkAnim1B8`/`UnkScene1B9`/`UnkTex1BA`,
   `Tricks` (`0x001255C8..0x00125F70`).
2. **AI vtables.** `AI_Race`, `AI_Vehicle`, `AI_Pedestrian` and `AI_Boss` derive from `AI_Agent` (`_vptr`
   at +0x9C). Slots 5, 6 and 7 return the position (matrix row 3, or `AI_Race::mPos128`), row 2 and the
   matrix (`AI_Vehicle` has its own at +0xA0, `AI_Race` uses its Player's); `AI_Boss` slot 8 returns
   `mField138`. Before declaring the vtables (which moves each `__tf` out of `src/rtti/`): slots 9 and 10
   of `AI_Boss` are `0x0010B910`/`0x0010B918`, the two empty functions just before `__tf7AI_Race`,
   although RTTI says `AI_Boss : AI_Agent`; find out why first. Each AI TU also ends with its own copies
   of `__tf8AI_Agent` and `__tf6EnvObj` (16 such copies), which only appear once the TU has whatever
   uses them.
3. **Game code TU by TU, in address order.** Use the keywords in `docs/MAP.md` for names. Started: the
   tricks script TU (`0x00123CD0..0x00125FF0`, `src/game/Tricks.cpp`: 35 of 59 functions matched, the
   `tricklist` parser is in `NON_MATCHING`, the larger parsers/evaluators and the 9 `cvt.w.s` + `dsll32`/`dsra32`
   functions are left).
4. **Controllers' simulation steps** (slot 5): `MotionCtrl` `0x00117728` 1028 B, `IP_RotCtrl` `0x00118080`
   552 B, `IP_AnimCtrl` `0x0016F128` 1288 B. `IP_RotCtrl`'s has a block of VU0 macro instructions
   (`lqc2`/`vmulx`/`vadd`/`sqc2`) that GCC does not generate, so it needs inline `asm`. (The `MBCL` and
   `ScootCL` constructors are inlined at `0x0015F7AC` / `0x00171534` and have no out-of-line copy.)
5. **Front end:** the remaining larger `VirtSlot2`/`VirtSlot3`/constructor functions of the 10
   `FE*Screen` subclasses.

## NON_MATCHING (register allocation or scheduling; the notes are in the source)

- `Pickup::Pickup` `0x0011B060`, 123/144 (`KeyPickup.cpp`): the loop counter's `i = 0` and two FP registers.
- `Scooter::ConsumeAdrenaline` `0x0017ED28`, 5/12 (`Scooter.cpp`): FP registers; `-ffast-math` did not help.
- `FELevelScreen::VirtSlot4` `0x0016A9C8`, 1/8 (`FEScreens.cpp`).
- `func_001240F8` (`tricklist` parser), 93/97 (`Tricks.cpp`): one pointer in `$s0` instead of `$v0`.

## Unverified names

- IVP method names in `src/game/CollFilt.h`, `CollisionListeners.h` and `Controllers.h` were written from
  memory (the vtable slot order is verified). This includes the `IVP_Listener_Phantom` methods,
  `IVP_Mindist_Base::get_objects` and the class name `IVP_Controller_Phantom` (which has no RTTI).
