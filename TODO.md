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

0. **Raw m2c matches from `tools/analysis/m2c_sweep.py`.** Second sweep of game code (2026-11-25, after
   giving m2c the globals' symbols, the switch jump tables, `&sp0` and `cvt.w.s`, and retrying drafts with
   mechanical fixes): of 2465 unmatched functions, 406 match as drafts (26 KB), 240 differ only in registers,
   428 more score >= 0.9; 126 still do not compile and 8 fail in m2c (was 193 / 178 / 219 / 649 / 175).
   Most of the new matches use globals (data variables, strings, float constants): write strings and floats
   as literals (`rebuild.py` checks them against the game's bytes) and declare variables as typed symbols.
   The first sweep (2026-11-25, 185 s) found 1119
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
   - **Phase 2, first part done:** 171 functions whose draft only touches fields of its first argument are
     methods of 96 `UnkObj<addr>` classes in the same block files. A class groups functions within 0x100 bytes
     of each other, with no matched function of another class between them and no field used with two
     types; many classes have one method, so merge them when callers or layouts show they are the same
     object. Left for hand work (`m2c_sweep.py report --range A B --status match` lists them): the 36 next
     to classes we already have (`AI_Race`, `AI_Boss`, `Player`, `Scooter`, `UnkModel1B7`, `UnkClip1B7`,
     `UnkAnim1B8`, `UnkScene1B9`, `UnkBody`, `MBCL`, `ScootCtrl`, `MBCtrl`, `UnkObj11F`, `UnkTable11A8`),
     which should join those classes (22 done: 10 `AI_Boss` methods, `AI_Race::GetPlayerRow2` and
     `GetPlayerMatrix`, the pointer list `UnkPtrList10C058`, 2 `Scooter`, `UnkModel1B7::Method1B7A68`,
     `UnkObj11A910`, `UnkObj1618D0::SetField2C`, `UnkObj1804E8`; left: the `EnvObj` destroy functions
     `0x0011FA48`, `0x0014CC78`, `0x00161708` and `Player`'s `0x00123258` (they call
     `EnvObjCleanup14FB70(this)`, so their classes derive from `EnvObj`), `0x0017EF30` (passes `mField370`
     to methods of both `UnkObj141A38` and `UnkEffect`), `0x0014CAF0`, `0x0014CCB0`, `0x0015EFF8`,
     `0x0018E758`, `0x001B7CA8`/`0x001B8108` (byte-swap two u16 / u32 in place), `0x001B8B30`, `0x001B8BA0`,
     `0x001B9B30`, whose class is not settled); about 140 whose draft reads fields through a second pointer, does
     arithmetic on the first one or calls a method; and 8 more that the mechanical C++ did not compile or
     match: `0x00111F60`, `0x0012CBA0`, `0x00130B50`, `0x00182FD0`, `0x001830A0`, `0x00197468`,
     `0x001B2948`, `0x001B6F58`. `0x00168900` compiles 2 words off as a method (two stores swapped) though
     the C draft matched. Lead to check:
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
2. **AI vtables (declared and confirmed).** `AI_Agent` and its four subclasses declare their virtuals in
   slot order and `verify_vtables.py` confirms every slot. `AI_Agent` has `__pure_virtual` in slots 1-7 and
   inline defaults in 8-10 (`0x00106568` returns 0.0f, `0x0010B910`/`0x0010B918` are empty): they were
   emitted once, in the first TU that needed them, which is why slot 8 sits in `AI_Pedestrian`'s TU and 9-10
   in `AI_Race`'s, and why `AI_Race`, `AI_Vehicle` and `AI_Boss` share them. Slots 5-7 (`GetPosition`,
   `GetRow2`, `GetMatrix`) return the agent's matrix row 3, row 2 and the matrix. Each subclass declares its
   destructor first and does not define it, so no file of ours emits its vtable and the `__tf` functions
   stay generated stubs in `src/rtti/`. Left: the slot 1 destructors, the big slot 2 functions (one per
   class, 1.3 to 3.6 KB, probably the per-frame update), `AI_Vehicle`/`AI_Pedestrian`/`AI_Boss` slots 3-4
   and `AI_Pedestrian`'s own slots 9-10; and the 16 copies of `__tf8AI_Agent`/`__tf6EnvObj` at the end of
   the AI TUs, which appear only once a TU of ours emits what uses them.
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

## Naming (most matched code still has address names)

Matching gives the bytes, not what the code is for: the game has no symbols, and a small accessor says
nothing about its field. Names have to come from evidence, roughly in this order of yield:

1. **Library functions by behaviour (done for the most called).** newlib, identified from the code
   (`include/common/libc.h`): `malloc`, `memcpy`, `memset`, `printf`, `vfprintf` (symbol only), `rand`,
   `strcmp`. The GL-style layer (`src/game/GL.h`, from the OpenGL enums each one switches on or is called
   with, and from the render state each one reads or writes): `glEnable`, `glDisable`, `glBindTexture`,
   `glDrawArrays`, `gl{Vertex,Color,TexCoord}Pointer`, `gl{Enable,Disable}ClientState`, and immediate mode:
   `glBegin`, `glEnd`, `glVertex3f`, `glTexCoord2f`, `glColor3f`, `glColor4f`, `glMatrixMode`,
   `glPushMatrix`, `glPopMatrix`. The game's allocator and free: `MemAlloc1BD958(size)` (calls
   `func_001BD558(size, 3)`) and `MemFree1BD978(p)`. The dynamic array `UnkArray1BB0D0` (stride, count,
   data; `GetCount`, `Clear`, `Destroy`) with `ArrayGetElement1BB098` and `ArrayGetCount1BB0D0`. Next:
   `0x001A4930` (78 calls; a boolean in the render state, set to 0 before blended drawing and 1 after:
   probably `glDepthMask`, unconfirmed), `0x0020A0E8` (171 calls, physics), and the rest of the GL layer
   (`0x0019F000..0x001A5000`) by call count.
2. **Keyword parsers (tool done, first names applied).** `tools/analysis/keyword_fields.py` lists, for
   each of the ~500 reads of `UnkParser`, the script key and the field it goes to. Applied where the
   object is a struct we already have, matched by offsets and types: `UnkVehicleParams` (`speed`,
   `wheelradius`), `UnkPedParams` (`speed`, `probability`, `timein`, `timeout`, `stoprange`, `time`,
   `lookatrange`) and `UnkScooterParams1C0` (`startacc`, `speedmin`, `adrenaline` (the multiplier applied
   while `Scooter::mFlags18 & 0x400`), `ramplaunch`, `wedgelaunch`), and their accessors (`GetSpeed04`,
   `ScaleRampLaunch`, `RandomStartAcc124`, ...). Declared from their parsers, not used by matched code
   yet: `UnkRaceParams` (0x28 bytes, parser `0x0010B338`) and `UnkBossParams` (0x20C bytes, parser
   `0x0015DD70`); the level loader `0x0012BBB0` parses each into a stack buffer and copies it into a heap
   object of that size. Open: which pointer of `AI_Race`/`AI_Boss` holds them (`AI_Boss::mAttack1D8` may
   be the boss one: its +0x10 is the damage dealt to the player, as `mCollisionDamage10`), which of the
   boss's two `radius` keys is `distancereach`, and about 40 smaller parsers. Keys that repeat in one
   parser (`speed`, `acc`, `startacc`) belong to the sections in its `--tables` output, so keep the offset
   in their names until the section is known.
3. **Known API constants**, such as the OpenGL enums in the GL-style layer (step 0 above).
4. **Watching the retail game run (later, not needed now).** This works on the original game, not on our
   code: the decompilation only says which address holds what. In PCSX2 2.x, *Debug -> Open Debugger*:
   a breakpoint on a function shows when it runs (menu, level load, every frame) with `this` in `$a0`;
   a memory write breakpoint on `this+off` shows which function changes a field and when (it changes when
   the scooter speeds up: it is the speed); a `.pnach` patch that puts `jr $ra; nop` at a function's start
   shows what disappears without it. Useful for code with no strings nearby; it needs a person playing,
   so prepare a short list of addresses and what to look for first.

## NON_MATCHING (register allocation or scheduling; the notes are in the source)

- `Pickup::Pickup` `0x0011B060`, 123/144 (`KeyPickup.cpp`): the loop counter's `i = 0` and two FP registers.
- `Scooter::ConsumeAdrenaline` `0x0017ED28`, 5/12 (`Scooter.cpp`): FP registers; `-ffast-math` did not help.
- `FELevelScreen::VirtSlot4` `0x0016A9C8`, 1/8 (`FEScreens.cpp`).
- `func_001240F8` (`tricklist` parser), 93/97 (`Tricks.cpp`): one pointer in `$s0` instead of `$v0`.

## Unverified names

- IVP method names in `src/game/CollFilt.h`, `CollisionListeners.h` and `Controllers.h` were written from
  memory (the vtable slot order is verified). This includes the `IVP_Listener_Phantom` methods,
  `IVP_Mindist_Base::get_objects` and the class name `IVP_Controller_Phantom` (which has no RTTI).
