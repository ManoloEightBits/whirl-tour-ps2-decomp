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
   - **Tools:** `tools/analysis/draft_to_cpp.py` does these batches (`plan` lists what converts and the
     traps below), `edit_funcs.py` the hand fixes, `body_variants.py` the variant searches (docs/TOOLS.md).
     `draft_to_cpp.py plan --region physics` finds 176 drafts of the physics engine that convert as they
     are (no struct fields), if the physics code is taken in (see Open decisions).
   - **Phase 4 done (2026-11-25):** of the 134 drafts left that match (98) or differ only in registers (36)
     and read no struct fields, 57 more are in their block files, after hand fixes the drafts needed: m2c
     counts pointer arithmetic in bytes (`int *p; p + 4` is `+4` bytes, not 16), omits parameters it sees
     unused (a function that passes `$a0` through, or only uses `arg1`, still takes them: the callee's
     arguments come out shifted otherwise), and types strings and buffers as `int`. New: `UnkParser`'s value
     parsers (`ParseFloat3_1C37B0`..`IsValueTrue1C3988`, `sscanf` at `0x00231378`), `MemAlloc1BD958`
     (`func_001BD558(size, 3)`), `EnvObjCleanup14FB70` (empty), `glMatrixMode`, the `FESub08`/`FESlider`
     destructors, and the switch `func_001C4058` (a size per type 0..13; `0x001C4084..0x001C40AC` are its
     cases). Left: 16 `__tf` copies (`__tf6EnvObj` and `__rtti_user` ones, one per translation unit: they
     need the class of each TU), 8 `new`/`delete` helpers (runtime), the 6 sound-library functions, 3 whose
     callee's symbol has another arity (`0x00141420`, `0x0016F8D0`, `0x001BFAC0`; fix the callers first),
     about 15 that read data tables (type them first) and 5 that call methods of unknown classes.
   - **Phase 3 done:** 87 of those drafts that touch no struct fields are C++ at the end of their block file
     (section "Matched from the second m2c sweep"): strings and floats as literals, variables as
     `data_<addr>` in `config/symbols.txt`, callees declared with the signature of their symbol. Left out:
     16 more at addresses 4 mod 8 (see Phase 1), 34 that do not compile as C++ as drafted (mostly an `int` parameter used as a pointer, or a string
     passed to a callee whose symbol says `int`: fix the callee's signature first), 9 `__tf` copies
     (`__rtti_user`), the `operator new`/`delete` helpers and their 2 callers, `glMatrixMode`
     (`0x001A3638`, would go in a GL file) and its caller `0x00181800`, `0x0018D270`
     (`AI_AttackQuake` slot 7), and 6 functions of the sound library (below). About 240 more drafts that
     match read fields through pointers and need struct types.
   - **Sound library, not game code:** `0x001A5998..~0x001AC000` is a sound library linked into the game
     region (`SOUND_StartCommand`, "Set SOUND_DTS_ENABLE to 1 (in Sound.C)", DTS licensing messages; the IOP
     modules `sdrdrv`/`libsd` are loaded at `0x001AD650`). Like the runtime, decide whether it belongs in
     `src/` (see Open decisions). Earlier phases already put 5 small functions of it in
     `Block_001A8000.cpp` (`0x001A9370`, `UnkObj1A9768`, `0x001AB370`, `0x001ABD60`, `0x001ABE88`).
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
     them. They are not functions: the float ones are the cases of `GetVersusTime154EA8` and the int ones
     at `0x001C4084` the cases of `func_001C4058`; both switches are matched now.
   - **Phase 2, first part done:** 171 functions whose draft only touches fields of its first argument are
     methods of 96 `UnkObj<addr>` classes in the same block files. A class groups functions within 0x100 bytes
     of each other, with no matched function of another class between them and no field used with two
     types; many classes have one method, so merge them when callers or layouts show they are the same
     object. Left for hand work (`m2c_sweep.py report --range A B --status match` lists them): the 36 next
     to classes we already have (`AI_Race`, `AI_Boss`, `Player`, `Scooter`, `UnkModel1B7`, `UnkClip1B7`,
     `UnkAnim1B8`, `UnkScene1B9`, `UnkBody`, `MBCL`, `ScootCtrl`, `MBCtrl`, `UnkObj11F`, `UnkTable11A8`),
     which should join those classes (36 done: 10 `AI_Boss` methods, `AI_Race::GetPlayerRow2` and
     `GetPlayerMatrix`, the pointer list `UnkPtrList10C058`, 2 `Scooter`, `Scooter::func_0017EF30` with
     `UnkObj141A38` merged into `UnkEffect`, `UnkModel1B7::Method1B7A68`, `UnkObj11A910`,
     `UnkObj1618D0::SetField2C`, `UnkObj1804E8`, the `EnvObj` destroy helpers `UnkObj11FA48`,
     `UnkObj14CAF0` (`0x0014CAF0`/`CC78`/`CCB0`), `UnkObj161708` and `Player::Destroy123258`, `UnkObj15EFF8`,
     `UnkObj18E758`, `UnkObj1B7CA8`/`1B8108`, `UnkObj1B8B30`, `UnkObj1B8BA0`, `UnkObj1B9B30`); about 140 whose draft reads fields through a second pointer, does
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
5. **Front end:** left: the `VirtSlot2` updates, the constructors of `FEChooseScreen`,
   `FECharacterScreen`, `FENameSelectScreen` and `FEScooterScreen`, and the draw functions of
   `FENameSelectScreen` (`0x0016C0D8`) and `FEPlaylistScreen` (`0x00112578`). Done: `FEMenu` (14 of 15),
   `FEScreen::VirtSlot3`/`AddOwnerRecords`, `FEOptionsScreen::InitMenu16C6D8` (the three option menus,
   with `FESlider` for the volume bars), and the draw functions (`VirtSlot3`) of `FELevelScreen`,
   `FEChooseScreen`, `FECharacterScreen`, `FEMovScreen`, `FEStartScreen` and `FEScooterScreen`. The key
   to the draw functions is the `TEXT_SET_*` macros (docs/MATCHING.md): run each text statement plain and
   wrapped through `diff_func.py --bodies`. Typed on the way: `FEOwner` (model ids, text scale and
   colours, title), `FESub08`, `TextObj` (`SetColor`, `mWidth34`), the per-player definitions and model
   pairs of the choose/scooter screens, and the GL calls `glLoadMatrixf`/`glRotatef`/`glTranslatef`/
   `glMultMatrixf`/`glBlendFunc`.

6. **Text library (`0x00198000..0x0019C000`).** Done: `TextObj.cpp` (`CreateTextObj198E48`, `Init`,
   `Release198F38`, `DrawText19B758`/`DrawText19B778`), the front end's start-up/shut-down
   (`func_00198F58`/`func_00199030`: memory pool, the four pads and their copies at `0x002659B0`), and
   `TextObj`'s fields (alignment flags, offset, width/height) from the renderer. Left:
   `DrawTextEx19B2C0` (1176 B, the renderer: alignment, two-byte glyphs after 0x80, `\n`,
   `\c{...}` colour codes, clipping to a width), `MeasureText19B138` (uses MMI instructions), the
   debug vector font (`func_001990E8` draws a string as line strips from the table at `0x002658F0`,
   scaled by `data_002659E0..E8`, coloured by `func_001994D0`; `0x00199358`/`0x001993D0` are its
   printf-style wrappers, varargs), and a scene object of 0x318 bytes at `0x00198090..0x00198640` with
   three linked lists (not text).

7. **Front-end flow (from playing the PAL release, checked against the NTSC code).** At start-up the
   game plays two skippable intro movies (`FEMovScreen`), then the title screen (`FEStartScreen`: the
   background picture and string 3, "press Start"; `FEMovScreen` can show string 3 over a movie too),
   then New/Load, then the main menu: Arcade, Story, Entertainment, Multiplayer, Options, Extras, Save,
   Exit. `UpdateFrontEnd110B60` (`0x00110B60`, 3536 B, not decompiled) is the state machine behind it:
   in its state 9 it greys out menu item 3 (Multiplayer) while pad 2 is not connected
   (`FEPad::mConnected00`). `FEScreen`'s first constructor argument is the title's string id
   (`mTitleId28`); `FELoadStateScreen` uses 0x20 or 0x22 by mode (likely load and save). The PAL
   strings differ by language, so use these observations for meaning, not for text.
   `CreateScreen1101A8` (`0x001101A8`, not decompiled) builds each screen by its definition's name
   (`FindScreenDef113B48`): "newload" and "main" are plain `FEScreen`s with menus of 2 and 8 items
   (`gNewLoadMenuIds259E00`, `gMainMenuIds259E08`), "playlevel" is `FEChooseScreen`, the play menu of both
   Arcade and Story mode (Play level, Select character, Select scooter, Trick setup;
   `gPlayLevelMenuIds259E28`); the others
   are "mcscreen", "save", "quitconfirmation", "movie", "start", "load", "name", "multi", "monster",
   "level", "character", "scooter", "tricksetup", "options", "playlist". Options
   (`FEOptionsScreen::InitMenu16C6D8`, tables `gOptionsMenuIds2627A8` and the like): Action cameras,
   Vibration, Balance meter (on/off), 2 player options, Audio options, Playlist (`FEPlaylistScreen`,
   title 0x67), Default settings, Accept (PAL adds Language first); Audio: In-game music, Music volume,
   Fx volume; 2 player: Versus time (`GetVersusTime154EA8`), Versus degradation. The values live in
   `GameCtx` (`mActionCameras`..`mInGameMusic`). Levels (Play level, `GetLevelMenuIds155228`): Castle,
   Theme park, Suburbia, City in the sky, Subway, Deep water rig, Movie set, Tibet; only Castle is open at
   first (`mMaxLevel39C`). Each has 7 goals (`mLevels228[n].mGoals00`, `GetLevelGoals1550D8`) and 20
   "Scooters" collectibles that unlock a scooter (`mScooterParts3E8`, `GetLevelScooters156118`);
   `GetGoalsToUnlock155130` is how many goals the next level still needs (`gUnlockGoals261CB8`).
   The level screen's two icons: a key (`GetLevelKey155310`, a flag per level; shown on every level so
   far, its effect unknown) and a checkered flag when the level can be played as a race
   (`mRaceOpen4D4`); winning the race puts a trophy on it (not found in the code yet).

8. **Game context (`GameCtx.h`, `GameCtx.cpp`).** `gGameCtx262250` now has one type, `GameCtx` (0x6E0
   bytes), with what the menus and the progress functions show. `GameCtx.cpp` holds the module
   `0x00153C10..0x001566F8` (it was `Block_00154000.cpp`): the destructor and `CreateGameCtx154C10`/
   `DestroyGameCtx154C58`, the goals and level flags, the unlock-everything helpers (`func_00155030`,
   `UnlockAllLevels155238`), mode tests and the playlist's current track, the Versus time switch
   (`GetVersusTime154EA8`: 10 to 300 seconds, 11 choices), and each player's choices: character
   (`mCharacter288`, `gCharacterNames261C50` "gavin".."marcus"), scooter (`mScooterModel2D8`,
   `gScooterModels261C90`) and controller (`mPad20`, an index into `gFEPads2659A0`). About 45 functions of
   the module are left: `GameCtx::GameCtx` and `func_00152610` (filling it), the 0x00153C10..0x00154E80
   run, `func_00156200`/`func_00156270`/`func_001565F0` (0.6-0.7) and `func_00156310` (`ldl`/`sdl`
   copies); `mMode00` (0..7) still needs names for its values (Arcade, Story,
   Entertainment, Multiplayer variants...): the tests show which modes count goals (0, 3, 7). Likely
   0 Story and 2 Arcade: the level select (used by both) tests {0, 2}, and the level loaders that test
   {0, 3} would be where collectibles appear, which happens in Story but not in Arcade (seen in play);
   mode 4 uses Versus degradation. `UnlockScooterGlobal` (NON_MATCHING) unlocks one scooter per 20
   collectibles found in all levels (`mScootersUnlocked48C`).

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
- `FEMenu::Draw` `0x0016B4A8`, 7/175 (`FEScreens.cpp`): the text pointer of two statements gets the
  other register; the text macros of `FEScreen.h` fixed the rest.
- `FEMonsterScreen::VirtSlot3` `0x001153B8`, 117/131 and `FEOptionsScreen::VirtSlot3` `0x0016CED0`, 166/186
  (`FEScreens.cpp`): each needs more saved registers than our code (two copies of a global's address,
  hoisted constants; `$fp`), loop forms and the text macros did not change it.
- `FEScreen::FEScreen` `0x0016E458`, 7/85 (`FEScreen.cpp`): the constants 1, 8 and 9 of `mField18..24`
  get other registers; the member initializer list fixes the stores and the vtable pointer.
- `func_001240F8` (`tricklist` parser), 93/97 (`Tricks.cpp`): one pointer in `$s0` instead of `$v0`.
- `UnlockScooterGlobal` `0x00153C10`, 38/55 (`GameCtx.cpp`): a `nop` after the outer loop's `mult` and before
  the inner loop's first load, and the second loop's divide by 20 laid out differently; a row pointer, a
  local context pointer and the count in a local did not help.

## Unverified names

- IVP method names in `src/game/CollFilt.h`, `CollisionListeners.h` and `Controllers.h` were written from
  memory (the vtable slot order is verified). This includes the `IVP_Listener_Phantom` methods,
  `IVP_Mindist_Base::get_objects` and the class name `IVP_Controller_Phantom` (which has no RTTI).
