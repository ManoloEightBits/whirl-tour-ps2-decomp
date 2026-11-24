# TODO

- **IVP / Havok reference (undecided).** Many classes are Ipion Virtual Physics (`IVP_*`). Valve may have
  published an IVP source release; not checked. Before using it: find the exact repo and version, read its
  license, and decide whether to only consult it or copy from it. Until then nothing from it is in this repo.
  Method names in `src/game/CollFilt.h` for the IVP base class were written from memory and are unverified.
- Resolve the 14 RTTI functions that `rebuild.py` keeps as assembly (two `type_info` copies, see rebuild/README.md).
- `Player` (22 methods), `ScootCtrl` (23 methods), `Pickup` + all 10 subclasses, `FEScreen` (15 methods), `FEQuitScreen` (all 6 methods), `FEStartScreen` (5 methods), `FETrickScreen` (all 5 methods), and the collision/event listeners `IVP_Listener_Object`, `IVP_Listener_Collision`, `DD_Event_Listener`, `MBCL` and `ScootCL` (all 26 functions, `src/game/CollisionListeners.h`) are matched and their 21 vtables (68 slots, 0 unchecked) confirmed with `verify_vtables.py`. Next: the other listeners (`DD_Collision_Listener`, `LunActCL`, `MarActCL`, `Global_Phantom_Listener`), the remaining 11 `FE*Screen` subclasses (`FEMcScreen`, `FEMovScreen`, `FELoadStateScreen`, `FEPlaylistScreen`, etc.), `Pickup::Pickup` (`0x0011B060`), `KeyPickup::KeyPickup` (`0x0011B900`), `Pickup::Update` (`0x0011B3D8`), `KeyPickup::Update` (`0x0011CF18`), and the two `NON_MATCHING` methods in `ScootCtrl.cpp` (`IsGrounded`, `ConsumeAdrenaline`).
