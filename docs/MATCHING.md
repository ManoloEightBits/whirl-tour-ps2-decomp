# Matching notes

Source patterns that ee-gcc 2.95.3 (`-O2 -G0 -fno-exceptions`) needs before the output matches the game.
Each one is used by a function that matches in `src/`.

## Register allocation

When the instructions are right but the register numbers differ, the cause is usually the order in
which the global allocator picks pseudo-registers. It sorts them by

    priority = floor_log2(refs) * refs / live_length

with the highest priority first. Temporaries that live inside one basic block are handled earlier by
local-alloc and usually take `$v0`. Ties go to the lower pseudo number. A pseudo used more often in a
shorter range wins, so a pointer that is null-checked, loaded through and stored through (4 refs) usually
beats a value that is loaded, tested and used once (3 refs).

To see the real numbers, compile a small standalone file under `build/scratch/` (git-ignored) with the
`.lreg`/`.greg` dumps enabled:

```bash
T="$WHIRL_COMPILERS/ee-gcc2.95.3-114/lib/gcc-lib/ee/2.95.3"
export WINEPREFIX=~/.wine-ps2 WINEDEBUG=-all WINEARCH=win32
wine "$T/cpp.exe" -lang-c++ -nostdinc -Iinclude -Isrc build/scratch/t.cpp build/scratch/t.ii
wine "$T/cc1plus.exe" -quiet -O2 -G0 -fno-exceptions -dl -dg build/scratch/t.ii -o build/scratch/t.s
grep "Register .* used" build/scratch/t.ii.lreg
# -> Register 118 used 4 times across 7 insns; ... user var; ... pointer.
```

Then try variants on the real file with `diff_func.py <file.cpp> <symbol> --variants <json>` from the
work directory. It only replaces text in the `.cpp`, so to try different inline helpers, put them in the
replaced text instead of the header.

## Patterns

- **`do { } while (0)` around a body.** Refs inside a loop count double, which reorders priorities. In
  `DD_Event_Listener::event_object_revived` the flags value goes from 3 refs over 4 insns (priority 0.75)
  to 6 refs over 4 insns (3.0). That beats the actor pointer's 7 refs over 7 insns (2.0), so the flags get
  `$v1` and the actor gets `$a0`, as in the game. The loop also emits a lone `nop` before `jr $ra`. That
  `sw; nop; jr $ra; nop` sequence occurs once among the binary's 7,069 returns, so it identifies this pattern
  (probably a macro in the original). `while (p) { ...; break; }` gives the same code. See `DD_ActorInfo` in
  `src/game/CollisionListeners.h`.
- **Splitting `p->x |= k` into `u32 f = p->x; ... f |= k; p->x = f;`** raises the priority of `f`, but the
  `ori` then writes back into the same register as `f`. Use this only when the game's code does the same.
- **IVP `IVP_U_Float_Point` inlines are element-wise.** For example, `k[0] = -p->k[0]; k[1] = -p->k[1]; ...`,
  with no temporaries. Called on itself (`v.set_negative(&v)`), this gives the game's load/neg/store order
  for `k[0]`, then loads `k[1]`/`k[2]` together, because GCC cannot prove that the two base registers do not
  alias. The member address (`this + off`) is folded into the `k[0]` access only. `k[1]` and `k[2]` go through
  a register that holds the address. See `ScootCL::event_collision_object_deleted`.
- **Loads that the game does early.** If the game loads a value before some stores, and our code loads it
  after them, read it into a local at the point where the game loads it. GCC will not move a load above a
  store it cannot prove is independent. See `mine`/`other` in `ScootCL::event_collision_object_deleted`.
- **`asm("");` as a scheduling barrier.** It stops GCC from mixing a flag update into a block of float
  copies (`MBCL::event_pre_collision`, `ScootCL::event_pre_collision`). It emits no instruction.
- **Data members declared before the first virtual function** go before `_vptr`. `IVP_Listener_Collision`
  has `int` at `+0x00`, so its `_vptr` is at `+0x04` (`sw $v0, 0x4($a0)` in the constructor).
