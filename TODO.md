# TODO

- **IVP / Havok reference (undecided).** Many classes are Ipion Virtual Physics (`IVP_*`). Valve may have
  published an IVP source release; not checked. Before using it: find the exact repo and version, read its
  license, and decide whether to only consult it or copy from it. Until then nothing from it is in this repo.
  Method names in `src/game/CollFilt.h` for the IVP base class were written from memory and are unverified.
- Resolve the 14 RTTI functions that `rebuild.py` keeps as assembly (two `type_info` copies, see rebuild/README.md).
- `Player::AddKey` (0x00123548) is matched; the class and field names (`Player`, `mKeys`) are hypotheses. Next: the other Pickup subclasses' slot 3 (0x11D190, 0x11D220, ...).
