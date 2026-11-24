# Matching notes

Source patterns that ee-gcc 2.95.3 (`-O2 -G0 -fno-exceptions`) needs before the output matches the game.
Each one is used by a function that matches in `src/`.

## Assembler

The retail assembler is not among the available packages. All three `ps2eeas.exe` builds (2.95.2-273a,
2.95.3-114, 2.95.3-136) give the same results; the three `as.exe` builds break three functions. The
retail one differs from them in one known way: the `nop` it inserts after `mtc1` (and after the
`li.s` macro, which ends in `mtc1`). It checks the even/odd FP register *pair*, like classic GNU as
does, and not only the register itself. After `mtc1 $at,$f3`, a `mul.s $f0,$f0,$f2` gets a `nop`
because `$f2` is `$f3`'s partner. In game and IVP code this rule explains 246 of the 247 such nops
before an instruction that does not read the written register.

`verify.assemble()` reproduces it with `mtc1_pair_nops()`: it writes `<file>.as.s` with an explicit
`nop` for the partner case (the exact-register case stays with ps2eeas), skipping `.set noreorder`
regions, and assembles that. This is what moved `KeyPickup::Update` out of `NON_MATCHING`. If a
function differs from the game only by a `nop` right after an `mtc1`, look here first.

## Register allocation

When the instructions are right but the register numbers differ, the cause is usually the order in
which the global allocator picks pseudo-registers. It sorts them by

    priority = floor_log2(refs) * refs / live_length

with the highest priority first. Temporaries that live inside one basic block are handled earlier by
local-alloc and usually take `$v0`. Ties go to the lower pseudo number. A pseudo used more often in a
shorter range wins, so a pointer that is null-checked, loaded through and stored through (4 refs) usually
beats a value that is loaded, tested and used once (3 refs).

To see the real numbers, use `tools/analysis/scratch_cc.py --regs` (see [TOOLS.md](TOOLS.md)). It compiles with
`-dl -dg` and prints, for each pseudo-register, the weighted refs, live length, priority, allocation
order and final hard register, from GCC's own dumps:

```
$ python3 tools/analysis/scratch_cc.py t.cpp --func looped --regs
  pseudo  refs  live  alloc   priority  order hard    notes
  118        6     7  global     1.714  2     $a0     user var, pointer
  120        6     4  global     3.000  1     $v1
```

Compare the result with the game using `scratch_cc.py --vs <addr>`. Then try variants in the real
file with `diff_func.py <file.cpp> <symbol> --variants <json>`. That command only replaces text in the
`.cpp`, so to try different inline helpers, put them in the replaced text instead of the header.

## Patterns

- **`do { } while (0)` around a body.** Refs inside a loop count double, which reorders priorities. In
  `DD_Event_Listener::event_object_revived` the flags value goes from 3 refs over 4 insns (priority 0.75)
  to 6 refs over 4 insns (3.0). The actor pointer goes from 4 refs over 7 insns (1.143) to 6 refs over
  7 insns (1.714). The flags now win, so they get `$v1` and the actor gets `$a0`, as in the game. The loop
  also emits a lone `nop` before `jr $ra`. This is probably a macro in the original.
  `while (p) { ...; break; }` gives the same code. See `DD_ActorInfo` in `src/game/CollisionListeners.h`.
  Outside function boundaries, `find_pattern.py '(?!jr)\S+.*; sw; nop; jr \$ra; nop'` finds this
  `sw; nop; jr $ra; nop` sequence 4 times: `0x00117360` (this function), `0x001AFD28`, `0x001BD2F8` and
  `0x001C43A0`. The last one ends a jump-table `switch`. The other three are candidates for the same kind
  of construct. Without the `(?!jr)` element there are 11 hits; the extra 7 are a `sw` in the previous
  function's delay slot, followed by an alignment `nop`.
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
- **An inline function that also exists out of line.** Game code inlines `IVP_Listener_Collision(int)`
  (`MBCL` passes 3, `ScootCL` 7, `MarActCL` 1), but the IVP library also has an out-of-line copy at
  `0x001F6F10`. The header defines the constructor inline, except when `IVP_LISTENER_COLLISION_OUT_OF_LINE`
  is defined. `IVP_Listener_Collision.cpp` defines that macro and emits the copy.
- **`min.s` / `max.s` come from the GNU g++ operators `<?` and `>?`.** GCC 2.95 never turns
  `a < b ? a : b` on floats into MIN (IEEE rules forbid it), so a clamp that compiles to `min.s`/`max.s`
  was written as `(x + t <? 1.0f) >? 0.0f`. A `?:` macro around a function call instead compiles to a
  branch that calls the function twice: `LunActCL` has `MIN(len(), 1.0f)` as `((a) <= (b) ? (a) : (b))`
  (`c.le.s`; with `<` it would be `c.lt.s`). See `LunActCL::event_pre_collision`.
- **Inline members are emitted in the key-function TU.** The TU that defines a class's first non-inline
  virtual function (and so emits its vtable) also emits out-of-line copies of the class's inline member
  functions. If the game has no such copy, the original did not have the inline member: for example,
  `DD_Collision_Listener` uses its implicit constructor, which needs the base's `int enable_bits = 1` default.
  If two classes' key functions share our file but not the game's TU, GCC may also inline one class's
  `__tf` into the other's: keep separate game TUs in separate files (`IVP_Listener_Collision.cpp`).
- **A function that is both inlined and present out of line is an inline member.** `Pickup::func_0011B7B8`
  contains the whole body of `Pickup::func_0011CD80(1)`, which also exists on its own at `0x0011CD80`:
  defining it inline in the class gives both (the out-of-line copy comes from the key-function TU).
- **An inline helper can change the schedule of a call's arguments.** In `Pickup::func_0011B7B8`,
  `new UnkEffect(mDef70->field_0x9C, &mPos44, ...)` written in place lets GCC move the `mDef70` reload
  after the copy of the new object into `$a0`, so it gets `$v0` instead of the game's `$v1`. The same
  code in a `static inline` function taking the pickup matches (`SpawnCollectEffect`). A `static inline`
  free function leaves no out-of-line copy, unlike an inline member.
- **A value that the game reloads, but ours keeps in a register, means GCC knew less.** In
  `AI_PedestrianCL::event_pre_collision` the game reloads `n->k[1]` after the stores to a local `up`
  vector, because CSE could not rule out that they alias. Written in place, CSE keeps the value; moved
  into a `static inline` helper that receives `n` as a parameter (`FixNormal`), the reload appears.
- **Which FP register a temporary gets depends on what is live at the time.** In the same function,
  `up.k[0]` lands in `$f1` only if it is read *before* the `if` that uses it, so that its life overlaps
  the compared value in `$f0`. The delay-slot filler then moves the load to the same place either way.
- **`base ... with only non-default constructor in class without a constructor`.** GCC 2.95 gives this
  error when a derived class declares no constructor at all. Declare the real one, even if its body is
  not decompiled yet (see `MBCL` and `ScootCL`).
- **Data members declared before the first virtual function** go before `_vptr`. `IVP_Listener_Collision`
  has `int` at `+0x00`, so its `_vptr` is at `+0x04` (`sw $v0, 0x4($a0)` in the constructor).
