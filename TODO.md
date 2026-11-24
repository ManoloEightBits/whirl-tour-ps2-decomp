# TODO

- **IVP / Havok reference (undecided).** Many classes are Ipion Virtual Physics (`IVP_*`). Valve may have
  published an IVP source release; not checked. Before using it: find the exact repo and version, read its
  license, and decide whether to only consult it or copy from it. Until then nothing from it is in this repo.
  Method names in `src/game/CollFilt.h` for the IVP base class were written from memory and are unverified.
- Resolve the 14 RTTI functions that `rebuild.py` keeps as assembly (two `type_info` copies, see rebuild/README.md).
- `Player` (22 methods), `ScootCtrl` (23 methods), and `Pickup` + all 10 subclasses' `OnCollected` (vtable slot 3) are matched and their 11 vtables confirmed with `verify_vtables.py`. Next: `KeyPickup::Update` (`0x0011CF18`), `Pickup` and subclass constructors/destructors, and the two `NON_MATCHING` methods in `ScootCtrl.cpp` (`IsGrounded`, `ConsumeAdrenaline`).
