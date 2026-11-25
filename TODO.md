# TODO

- **Where the remaining bytes are** (`tools/analysis/coverage.py`, see the README note under the subsystem
  table). The levers, largest first: the IVP source question below (29% of `.text`); the runtime region
  (13%: libgcc/libc might be built from their GPL/BSD sources with the same compiler, the Sony SDK libraries
  stay assembly and could leave the denominator); then game code TU by TU in address order, using strings
  and keyed tables for names (most of it has no vtable).
- **IVP / Havok reference (undecided).** Many classes are Ipion Virtual Physics (`IVP_*`). Valve may have
  published an IVP source release; not checked. Before using it: find the exact repo and version, read its
  license, and decide whether to only consult it or copy from it. Until then nothing from it is in this repo.
  IVP method names in `src/game/CollFilt.h`, `CollisionListeners.h` and `Controllers.h` were written from memory
  and are unverified (the vtable slot order is verified). This includes the `IVP_Listener_Phantom` methods,
  `IVP_Mindist_Base::get_objects` and the class name `IVP_Controller_Phantom` (which has no RTTI).
- `Player` (32 methods and all 13 `player_*` collision callbacks: the whole TU), the non-virtual accessors of `AI_Pedestrian` (43), `AI_Race` (43) and `AI_Vehicle` (21), `Scooter` (38 of the TU's 39 functions; called ScootCtrl before, see `Scooter.h`), `Pickup` + all 10 subclasses, `FEScreen` (15 methods), `FEQuitScreen` (all 6 methods), `FEStartScreen` (5 methods), `FETrickScreen` (all 5 methods), `FEMcScreen` (all 6 methods), and 42 methods across the remaining 10 `FE*Screen` subclasses (`FEPlaylistScreen`, `FEChooseScreen`, `FEMovScreen`, `FEMonsterScreen`, `FECharacterScreen`, `FELevelScreen`, `FELoadStateScreen`, `FENameSelectScreen`, `FEOptionsScreen`, `FEScooterScreen`), plus the collision/event listeners `IVP_Listener_Object`, `IVP_Listener_Collision`, `IVP_Listener_Phantom`, `DD_Event_Listener`, `DD_Collision_Listener`, `Global_Phantom_Listener`, `MBCL`, `ScootCL`, `LunActCL`, `MarActCL` and `AI_PedestrianCL` (all 45 functions, `src/game/CollisionListeners.h`; the `DD_Event_Listener.cpp` TU `0x00116B00..0x00117727` is complete) are matched, all 46 vtables (207 slots, 0 unchecked) confirmed with `verify_vtables.py`, and all 381 matched functions link cleanly in `rebuild.py` (0 kept as assembly). Next: the remaining larger `VirtSlot2`/`VirtSlot3`/constructor functions of the 10 `FE*Screen` subclasses, the last function of the Pickup TU (`Pickup::Pickup` `0x0011B060`, in `NON_MATCHING`, 123/144 instructions: only the scheduling of the loop counter's `i = 0` and two FP registers in the copy into `mPos50` are left, see the note in `KeyPickup.cpp`), `Scooter::ConsumeAdrenaline` (`NON_MATCHING`, register allocation only; see the note in `Scooter.cpp`).
- AI vtables: `AI_Race`, `AI_Vehicle`, `AI_Pedestrian` and `AI_Boss` derive from `AI_Agent` (`_vptr` at
  +0x9C). Slots 5, 6 and 7 return the position (matrix row 3, or `AI_Race::mPos128`), row 2 and the
  matrix (`AI_Vehicle` has its own at +0xA0, `AI_Race` uses its Player's). Before declaring the vtables:
  slots 9 and 10 of `AI_Boss` are `0x0010B910`/`0x0010B918`, the two empty functions just before
  `__tf7AI_Race`, although RTTI says `AI_Boss : AI_Agent`; find out why first.
- Controllers: `IVP_Controller`, `IVP_Controller_Independent` and the six game controllers (`MotionCtrl`, `IP_PosCtrl`, `IP_RotCtrl`, `IP_AnimCtrl`, `MBCtrl`, `ScootCtrl`) have all slots but one matched and their vtables confirmed. Next: each controller's simulation step (slot 5: `MotionCtrl` `0x00117728` 1028 B, `IP_RotCtrl` `0x00118080` 552 B, `IP_AnimCtrl` `0x0016F128` 1288 B). `IP_RotCtrl`'s has a block of VU0 macro instructions (`lqc2`/`vmulx`/`vadd`/`sqc2`) that GCC does not generate, so it needs inline `asm`. (The `MBCL` and `ScootCL` constructors are inlined at `0x0015F7AC` / `0x00171534` and have no out-of-line copy.)
