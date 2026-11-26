#include "common/types.h"

// Functions of 0x00104000..0x00107FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00105F18(); // 0x00105F18
void func_00106C38(); // 0x00106C38

void func_00106C18()
{
    func_00106C38();
}

void func_00106C38()
{
}

void func_00106C40()
{
    func_00105F18();
}

void func_00106C60()
{
}

// UnkObj106E68 (0x00106E68): no RTTI; its layout is the fields these methods use.
struct UnkObj106E68
{
    char field_0x0[0x20];
    int mField20;         // 0x20

    void Method106E68();  // 0x00106E68
};

void UnkObj106E68::Method106E68()
{
    mField20 &= 0xFFBFFFFF;
}

struct UnkSub106C68
{
    int mField00;
    f32 mField04;
};

struct UnkObj106C68
{
    char pad00[0x20];
    int mField20;         // 0x20
    char pad24[0x10C];
    f32 mField130;        // 0x130
    char pad134[0x48];
    UnkSub106C68 *mSub17C; // 0x17C
};

f32 func_00106C68(UnkObj106C68 *arg0, f32 arg1)
{
    int flags = arg0->mField20 & 0xFFFEFFFF;
    UnkSub106C68 *sub = arg0->mSub17C;
    arg0->mField20 = flags;
    f32 val = arg0->mField130 + arg1;
    if (val < sub->mField04)
    {
        arg0->mField130 = val;
        return val;
    }
    arg0->mField20 = flags & 0xFFFBFFFF;
    f32 limit = sub->mField04;
    arg0->mField130 = limit;
    return limit;
}
