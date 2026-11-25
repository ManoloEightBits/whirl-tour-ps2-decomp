#ifndef GAME_TRICKS_H
#define GAME_TRICKS_H

#include "common/types.h"
#include "game/Parser.h"

// Translation unit 0x00123CD0..: the "trickscores" and "tricklist" blocks of the tricks script
// (keywords in data_0025DC28). Names come from those keywords; the struct names are ours.

#define NUM_TRICKS 81 // the trick table at 0x0025ABC0 has 81 entries of 0x50 bytes

// Filled by a "tricklist" block (func_001240F8).
struct UnkTrickList
{
    int mUnlocked000[NUM_TRICKS];  // 0x000: 0 when the entry has lock "yes", else 1
    int mSequence144[NUM_TRICKS];  // 0x144: func_00124280 of the "sequence" string, -1 if not listed
};

// Score settings table at 0x0025A398 (filled by func_00123CD0).
struct UnkTrickScores
{
    f32 mField00;          // 0x000
    f32 mField04;          // 0x004
    f32 mField08;          // 0x008
    f32 mField0C;          // 0x00C
    int mCount10;          // 0x010
    f32 mArr14[30];        // 0x014
    int mCount8C;          // 0x08C
    f32 mArr90[30];        // 0x090
    int mCount108;         // 0x108
    f32 mArr10C[30];       // 0x10C
    int mCount184;         // 0x184
    f32 mArr188[30];       // 0x188
    int mCount200;         // 0x200
    f32 mArr204[30];       // 0x204
};

// Trick entry (0x50 bytes) in the 81-entry table at 0x0025ABC0 (filled by func_00124750).
struct UnkTrickDef
{
    char mName00[32];      // 0x00
    int mField20;          // 0x20
    int mField24;          // 0x24
    int mField28;          // 0x28
    f32 mField2C;          // 0x2C
    f32 mField30;          // 0x30
    int mField34;          // 0x34
    int mField38;          // 0x38
    int mField3C;          // 0x3C
    int mField40;          // 0x40
    int mField44;          // 0x44
    int mField48;          // 0x48
    int mField4C;          // 0x4C
};

// 0x40-byte entry in the table at 0x0025C510 (accessed by func_001258F8, func_00125910).
struct UnkTrickSeq
{
    int mSteps00[16];      // 0x00 (mSteps00[1] is the step count)
};

// Trick state struct passed to 0x00125DC0..0x00125DF8.
struct UnkTrickState
{
    u8 mSub00[0x4E];       // 0x00
    u8 mSub4E[0x4E];       // 0x4E
    u8 mSub9C[0x4E];       // 0x9C
    u8 mSubEA[0x4E];       // 0xEA

    void Action124A28();   // 0x00125DC0
    void *GetPtr00();      // 0x00125DE0
    void *GetPtr4E();      // 0x00125DE8
    void *GetPtr9C();      // 0x00125DF0
    void *GetPtrEA();      // 0x00125DF8
};

// Wrapper object at 0x00125F08..0x00125F18.
struct UnkObj125F
{
    void Method125F08();   // 0x00125F08
    void Method125F10();   // 0x00125F10
    void Action196110();   // 0x00125F18
};

void func_001240F8(UnkParser *p, UnkTrickList *list, char *name); // 0x001240F8: a "tricklist" block

f32 func_001255C8();                 // 0x001255C8: the adrenaline cap
f32 func_001255D8();                 // 0x001255D8
f32 func_001255E8();                 // 0x001255E8
f32 func_001255F8();                 // 0x001255F8
f32 func_00125608(u32 idx);          // 0x00125608
f32 func_001256F0(u32 idx);          // 0x001256F0
int func_00125880(const char *name); // 0x00125880: index of the trick with this name, or -1
UnkTrickSeq *func_001258F8(int idx); // 0x001258F8
int func_00125910(int idx);          // 0x00125910
const char *func_00125940(int idx);  // 0x00125940
int func_00125968(int idx);          // 0x00125968
int func_00125998(int idx);          // 0x00125998
int func_001259C8(int idx);          // 0x001259C8
int func_001259F8(int idx);          // 0x001259F8
f32 func_00125A28(int idx);          // 0x00125A28
f32 func_00125A58(int idx);          // 0x00125A58
int func_00125A88(int idx);          // 0x00125A88
int func_00125AB8(int idx);          // 0x00125AB8
int func_00125AE8(int idx);          // 0x00125AE8
int func_00125B58(int idx);          // 0x00125B58
int func_00125B88(int idx);          // 0x00125B88
int func_00125BB8(int idx);          // 0x00125BB8
int func_00125BD0(int idx);          // 0x00125BD0
int func_00125BE8(int idx);          // 0x00125BE8
int func_00125C00(int idx);          // 0x00125C00
void func_00125F38();                // 0x00125F38
void func_00125F70();                // 0x00125F70

#endif
