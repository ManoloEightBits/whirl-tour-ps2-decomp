# Full rebuild

`rebuild.py` relinks the game from a splat split of your own `SLUS_204.89`, swapping in every C++
function from `src/` that can be linked, and checks that the result has the SHA-1 in `pkg/target.sha1`.

```bash
# once: split the executable in a folder OUTSIDE the repo (it holds the game's code as text)
mkdir -p $WORK/split && cp SLUS_204.89 $WORK/split/ && cp config/splat/whirl_tour.yaml $WORK/split/
(cd $WORK/split && splat split whirl_tour.yaml)

export WHIRL_COMPILERS=... WHIRL_SLUS=... WHIRL_SPLIT=$WORK/split
python3 rebuild/rebuild.py --asm-only   # the split alone must reproduce the game
python3 rebuild/rebuild.py              # with the C++
```
Needs `binutils-mips-linux-gnu`, splat 0.50 and the compilers (see README.md).

Notes
- splat writes registers 8-15 with o32 names; the build uses `-mabi=eabi`, so `rebuild.py` renames them.
- After linking, each C++ function is compared with the game. Every matched function in `src/` links
  cleanly (0 kept as assembly).
- Functions the compiler adds for the generated probes (`config/probes.txt`) are ignored.
