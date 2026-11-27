#include "common/libc.h"
#include "game/Tricks.h"

extern UnkKeyword data_0025DC28[]; // "trickscores", "scoring", "trick", "/trickscores", "tricklist", "/tricklist"
int func_00124280(const char *sequence);  // 0x00124280: parses a "sequence" string
extern "C" void func_00124A28(void *, ...);
void *FindPickupDef(const char *);
void DrawModel196110(void *model); // 0x00196110
extern "C" void *func_00182258();
extern "C" void func_00183480(void *);
extern "C" void func_001834A0(void *, int, const char *, int, int);
void func_001B92F8(char *dst, const char *a, const char *b, const char *c);
extern "C" int func_002320C8(const char *, const char *);

extern UnkTrickScores data_0025A398;
extern f32 data_0025A624; // "health_bonus"
extern f32 data_0025A628; // "attack" -> "score"
extern f32 data_0025A62C; // "attack" -> "kill"
extern f32 data_0025A630; // "combo" -> "score"
extern f32 data_0025A634; // "combo" -> "kill"
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
    return data_0025A398.mSickMax00;
}

// 0x001255D8
f32 func_001255D8()
{
    return data_0025A398.mSickDec04;
}

// 0x001255E8
f32 func_001255E8()
{
    return data_0025A398.mAdrenalineMax08;
}

// 0x001255F8
f32 func_001255F8()
{
    return data_0025A398.mAdrenalineDec0C;
}

// 0x00125608
f32 func_00125608(u32 idx)
{
    u32 maxIdx = data_0025A398.mSpinMultCount10 - 1;
    if (idx < maxIdx)
        maxIdx = idx;
    return data_0025A398.mSpinMultipliers14[maxIdx];
}

#ifdef NON_MATCHING
// Return-value sign extension (dsll32; dsra32 after mfc1) is emitted in the game for these
// float-to-int getters/loop, whereas int return omits it and s64 changes caller Scooter.cpp.
// 0x00125630
int func_00125630(int idx)
{
    u32 maxIdx = data_0025A398.mSpinSwitchCount8C - 1;
    if ((u32)idx < maxIdx)
        maxIdx = idx;
    return (int)data_0025A398.mSpinSwitchBonus90[maxIdx];
}

// 0x00125670
int func_00125670(int idx)
{
    u32 maxIdx = data_0025A398.mTrickVarCount108 - 1;
    if ((u32)idx < maxIdx)
        maxIdx = idx;
    return (int)data_0025A398.mTrickVarBonus10C[maxIdx];
}

// 0x001256B0
int func_001256B0(int idx)
{
    u32 maxIdx = data_0025A398.mSickVarCount184 - 1;
    if ((u32)idx < maxIdx)
        maxIdx = idx;
    return (int)data_0025A398.mSickVarBonus188[maxIdx];
}
#endif

// 0x001256F0
f32 func_001256F0(u32 idx)
{
    u32 maxIdx = data_0025A398.mTrickDegradCount200 - 1;
    if (idx < maxIdx)
        maxIdx = idx;
    return data_0025A398.mTrickDegradMult204[maxIdx];
}

#ifdef NON_MATCHING
// 0x00125718
int func_00125718(int arg0, f32 arg1)
{
    f32 total = 0.0f;
    f32 mult = data_0025A398.mHoldMultiplier280;
    if (arg1 > 0.0f)
    {
        f32 timer = 1.0f;
        do
        {
            arg1 -= data_0025A398.mHoldInterval27C;
            total += (f32)arg0 * mult;
            if (timer >= data_0025A398.mHoldIncreaseInterval284)
            {
                timer = 0.0f;
                mult += data_0025A398.mHoldIncreaseMultiplier288;
            }
            timer += 1.0f;
        } while (arg1 > 0.0f);
    }
    return (int)total;
}

// 0x001257B8
int func_001257B8()
{
    return (int)data_0025A624;
}

// 0x001257E0
int func_001257E0()
{
    return (int)data_0025A628;
}

// 0x00125808
int func_00125808()
{
    return (int)data_0025A62C;
}

// 0x00125830
int func_00125830()
{
    return (int)data_0025A630;
}

// 0x00125858
int func_00125858()
{
    return (int)data_0025A634;
}
#endif

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
        return data_0025ABC0[idx].mScore28;
    return 0;
}

// 0x001259F8
int func_001259F8(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mPrev44;
    return 0;
}

// 0x00125A28
f32 func_00125A28(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mAngleFs2C;
    return 0.0f;
}

// 0x00125A58
f32 func_00125A58(int idx)
{
    if (idx >= 0 && idx < NUM_TRICKS)
        return data_0025ABC0[idx].mAngleBs30;
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
        return data_0025ABC0[idx].mReverseFs48;
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
        return data_0025ABC0[idx].mNext40;
    return 0;
}

// 0x00125B18
int func_00125B18(int idx)
{
    if ((u32)idx < NUM_TRICKS)
    {
        if (data_0025ABC0[idx].mReverseBs4C != 0)
            return data_0025ABC0[idx].mReverseBs4C;
        return data_0025ABC0[idx].mReverseFs48;
    }
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

struct UnkObj125CD8
{
    s8 mSub00[0x4E];            // 0x000
    s8 mSub4E[0x4E];            // 0x04E
    s8 mSub9C[0x4E];            // 0x09C
    s8 mSubEA[0x4E];            // 0x0EA
    int mField138;              // 0x138
    int mField13C;              // 0x13C
    int mField140;              // 0x140
    int mField144;              // 0x144
    int mField148;              // 0x148
    u8 mUnlocked14C[NUM_TRICKS]; // 0x14C
    char pad19D[3];             // 0x19D
    UnkTrickList *mList1A0;     // 0x1A0

    ~UnkObj125CD8();            // 0x00125CD8
};

void func_00125D00(UnkObj125CD8 *obj);

#ifdef NON_MATCHING
// 14 of 47 instructions differ: scheduling of mField138..148 stores and loop address setup.
// 0x00125C18
UnkObj125CD8 *func_00125C18(UnkObj125CD8 *obj, const char *name)
{
    if (name == 0)
        name = "tricklist_default";
    obj->mList1A0 = (UnkTrickList *)FindPickupDef(name);
    obj->mField138 = 0;
    obj->mField13C = 0;
    obj->mField140 = 0;
    obj->mField144 = 0;
    obj->mField148 = 0;
    for (int i = 0; i < 0x4E; i++)
    {
        obj->mSub00[i] = -1;
        obj->mSub4E[i] = -1;
        obj->mSub9C[i] = -1;
        obj->mSubEA[i] = -1;
    }
    int i = NUM_TRICKS - 1;
    u8 *p = &obj->mUnlocked14C[i];
    do
    {
        *p-- = 0;
        i--;
    } while (i >= 0);
    func_00125D00(obj);
    return obj;
}
#endif

// 0x00125CD8
UnkObj125CD8::~UnkObj125CD8()
{
}

// 0x00125D00
void func_00125D00(UnkObj125CD8 *obj)
{
{
    obj->mField138 = 0;
    obj->mField13C = 0;
    obj->mField140 = 0;
    obj->mField144 = 0;
    obj->mField148 = 0;
    for (int i = 0; i < 0x4E; i++)
    {
        obj->mSub00[i] = -1;
        obj->mSub4E[i] = -1;
        obj->mSub9C[i] = -1;
        obj->mSubEA[i] = -1;
    }
    int i = NUM_TRICKS - 1;
    u8 *p = &obj->mUnlocked14C[i];
    do
    {
        *p-- = 0;
        i--;
    } while (i >= 0);
    if (obj->mList1A0 != 0)
    {
        for (i = 0; i < NUM_TRICKS; i++)
        {
            if (obj->mList1A0->mUnlocked000[i] != 0)
                func_00124A28(obj, i);
        }
    }
}
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

// 0x00125E00
void func_00125E00(u8 *arg0, int arg1, u32 arg2, int arg3)
{
    u8 *base;
    switch (arg2)
    {
    case 0:
    case 1:
    case 2:
    default:
        base = arg0;
        break;
    case 3:
    case 4:
        base = arg0 + 0x4E;
        break;
    case 5:
        base = arg0 + 0x9C;
        break;
    case 6:
        base = arg0 + 0xEA;
        break;
    }
    base[arg1] = arg3;
}

// 0x00125E50
int func_00125E50(s8 *arg0, u32 arg1)
{
{
    s8 *base = 0;
    int cat = (arg1 < NUM_TRICKS) ? data_0025ABC0[arg1].mField20 : -1;
    switch (cat)
    {
    case 0:
    case 1:
    case 2:
        base = arg0;
        break;
    case 3:
    case 4:
        base = arg0 + 0x4E;
        break;
    case 5:
        base = arg0 + 0x9C;
        break;
    case 6:
        base = arg0 + 0xEA;
        break;
    case 7:
    default:
        break;
    }
    if (base != 0)
    {
        s8 *ptr = base;
        for (int i = 0; i < 0x4E; i++, ptr++)
        {
            if (*ptr == (int)arg1)
                return i;
        }
        return -1;
    }
    return -1;
}
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

// 0x00125FA8
#ifdef NON_MATCHING
// Stack frame is 0x170 vs 0x160 because GCC CSEs ".ddf" and ".ps2" into $s registers.
// 0x00125FA8
void func_00125FA8(int arg0, const char *arg1, int arg2, int arg3)
{
    if (data_0025DC60 == 0)
        return;
    char buf[256];
    if (func_002320C8(arg1, ".ddf") != 0)
        func_001B92F8(buf, arg1, ".ps2", ".ps2");
    else
        func_001B92F8(buf, arg1, ".ps2", ".ddf");
    func_001834A0(data_0025DC60, arg0, buf, arg2, arg3);
}
#endif


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
