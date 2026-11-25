#include "game/Tricks.h"

extern "C" int func_002317B4(const char *a, const char *b); // 0x002317B4 (runtime library; probably strcmp)
extern UnkKeyword data_0025DC28[]; // "trickscores", "scoring", "trick", "/trickscores", "tricklist", "/tricklist"
int func_00124280(const char *sequence);  // 0x00124280: parses a "sequence" string
int func_00125880(const char *name);      // 0x00125880: index of the trick with this name, or -1

#ifdef NON_MATCHING
// 93 of 97 instructions match. In the game both branches of the lock test compute
// &mUnlocked000[idx] into $v0, so reorg merges them into the bnez delay slot, and the 1 goes in
// $v1. Computing the pointer once after strcmp (below) gives that shape and fixes `list` ($s5)
// and the sequence buffer ($s4), but GCC ties the pointer to $s0 (idx * 4 dies there) instead of
// $v0. A plain if/else gets the pointer into $v1 and swaps $s4/$s5 (39 differences); a ternary or
// a value variable compiles to sltu without branches (94 instructions). Case 2 must come first.
void func_001240F8(UnkParser *p, UnkTrickList *list, char *name)
{
    for (int i = 0; i < NUM_TRICKS; i++)
    {
        list->mSequence144[i] = -1;
        list->mUnlocked000[i] = 0;
    }
    p->func_001C2C78("name", name);
    int done = 0;
    while (p->mEof102C == 0 && !done)
    {
        p->func_001C1D28(data_0025DC28);
        switch (p->mToken14)
        {
        case 2: // trick
        {
            char trick[64];
            char sequence[16];
            char lock[16];
            p->func_001C2C78("name", trick);
            p->func_001C2C78("sequence", sequence);
            p->func_001C2C78("lock", lock);
            int seq = func_00124280(sequence);
            int idx = func_00125880(trick);
            if (idx >= 0)
            {
                list->mSequence144[idx] = seq;
                int r = func_002317B4(lock, "yes");
                int *unlocked = &list->mUnlocked000[idx];
                if (r == 0)
                    *unlocked = 0;
                else
                    *unlocked = 1;
            }
            break;
        }
        case 5: // /tricklist
            done = 1;
            break;
        default:
            p->func_001C2C10();
            break;
        }
    }
}
#endif
