#include "common/libc.h"
#include "game/Tricks.h"

extern UnkKeyword data_0025DC28[]; // "trickscores", "scoring", "trick", "/trickscores", "tricklist", "/tricklist"
int func_00124280(const char *sequence);  // 0x00124280: parses a "sequence" string
extern "C" void func_00124A28(void *);
void DrawModel196110(void *model); // 0x00196110
extern "C" void *func_00182258();
extern "C" void func_00183480(void *);

extern UnkTrickScores data_0025A398;
extern UnkTrickDef data_0025ABC0[NUM_TRICKS];
extern UnkTrickSeq data_0025C510[];
extern int data_0025D9C8[];
extern int data_0025D9F0[];
extern int data_0025DBD8[];
extern int data_0025DC00[];
extern void *data_0025DC60;

// 0x001255C8
f32 func_001255C8()
{
    return data_0025A398.mField00;
}

// 0x001255D8
f32 func_001255D8()
{
    return data_0025A398.mField04;
}

// 0x001255E8
f32 func_001255E8()
{
    return data_0025A398.mField08;
}

// 0x001255F8
f32 func_001255F8()
{
    return data_0025A398.mField0C;
}

// 0x00125608
f32 func_00125608(u32 idx)
{
    u32 maxIdx = data_0025A398.mCount10 - 1;
    if (idx < maxIdx)
        maxIdx = idx;
    return data_0025A398.mArr14[maxIdx];
}

// 0x001256F0
f32 func_001256F0(u32 idx)
{
    u32 maxIdx = data_0025A398.mCount200 - 1;
    if (idx < maxIdx)
        maxIdx = idx;
    return data_0025A398.mArr204[maxIdx];
}

// 0x00125880
int func_00125880(const char *name)
{
    int found = -1;
    int i = 0;
    do
    {
        if (strcmp(func_00125940(i), name) == 0)
            found = i;
        i++;
    } while (found == -1 && i < NUM_TRICKS);
    return found;
}

// 0x001258F8
UnkTrickSeq *func_001258F8(int idx)
{
    return &data_0025C510[idx];
}

// 0x00125910
int func_00125910(int idx)
{
    return data_0025C510[idx].mSteps00[data_0025C510[idx].mSteps00[1] + 1];
}

// 0x00125940
const char *func_00125940(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mName00;
    return 0;
}

// 0x00125968
int func_00125968(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField20;
    return -1;
}

// 0x00125998
int func_00125998(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField24;
    return 0;
}

// 0x001259C8
int func_001259C8(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField28;
    return 0;
}

// 0x001259F8
int func_001259F8(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField44;
    return 0;
}

// 0x00125A28
f32 func_00125A28(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField2C;
    return 0.0f;
}

// 0x00125A58
f32 func_00125A58(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField30;
    return 0.0f;
}

// 0x00125A88
int func_00125A88(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField38;
    return -1;
}

// 0x00125AB8
int func_00125AB8(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField34;
    return -1;
}

// 0x00125AE8
int func_00125AE8(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField48;
    return 0;
}

// 0x00125B58
int func_00125B58(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField3C;
    return 0;
}

// 0x00125B88
int func_00125B88(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mField40;
    return 0;
}

// 0x00125BB8
int func_00125BB8(int idx)
{
    return data_0025D9C8[idx];
}

// 0x00125BD0
int func_00125BD0(int idx)
{
    return data_0025D9F0[idx];
}

// 0x00125BE8
int func_00125BE8(int idx)
{
    return data_0025DBD8[idx];
}

// 0x00125C00
int func_00125C00(int idx)
{
    return data_0025DC00[idx];
}

// 0x00125DC0
void UnkTrickState::Action124A28()
{
    func_00124A28(this);
}

// 0x00125DE0
void *UnkTrickState::GetPtr00()
{
    return mSub00;
}

// 0x00125DE8
void *UnkTrickState::GetPtr4E()
{
    return mSub4E;
}

// 0x00125DF0
void *UnkTrickState::GetPtr9C()
{
    return mSub9C;
}

// 0x00125DF8
void *UnkTrickState::GetPtrEA()
{
    return mSubEA;
}

// 0x00125F08
void UnkObj125F::Method125F08()
{
}

// 0x00125F10
void UnkObj125F::Method125F10()
{
}

// 0x00125F18
void UnkObj125F::Action196110()
{
    DrawModel196110(this);
}

// 0x00125F38
void func_00125F38()
{
    if (data_0025DC60 == 0)
        data_0025DC60 = func_00182258();
}

// 0x00125F70
void func_00125F70()
{
    if (data_0025DC60 != 0)
    {
        func_00183480(data_0025DC60);
        data_0025DC60 = 0;
    }
}


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
                int r = strcmp(lock, "yes");
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
