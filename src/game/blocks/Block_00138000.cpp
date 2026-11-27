#include "common/types.h"

// Functions of 0x00138000..0x0013BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_0013B300(); // 0x0013B300

void func_00138918()
{
}

void func_00138920()
{
}

void func_00138928()
{
}

void func_0013B2E0()
{
    func_0013B300();
}

// UnkObj13B240 (0x0013B240): no RTTI; its layout is the fields these methods use.
struct UnkObj13B240
{
    char field_0x0[0x18];
    f32 mField18;          // 0x18
    char field_0x1C[0x30];
    u8 *mField4C;          // 0x4C

    void Method13B240();   // 0x0013B240
};

void UnkObj13B240::Method13B240()
{
    u8 *tmp;

    tmp = mField4C;
    *tmp &= 0xFE;
    mField18 = (f32) (mField18 - 0.2f);
}

struct UnkObj1397E0A
{
    char pad00[0x03];
    s8 mField03; // 0x03
};

struct UnkObj1397E0B
{
    char pad00[0x4A];
    u16 mField4A; // 0x4A
};

void func_001397E0(UnkObj1397E0A *arg0, UnkObj1397E0B *arg1)
{
    arg1->mField4A |= 0x20;
    arg0->mField03 = 0;
}

struct UnkData1397F8
{
    char pad00[0x20A];
    u16 mField20A; // 0x20A
};

extern UnkData1397F8 *data_0025E5DC;
void func_00119140(UnkObj1397E0B *); // 0x00119140

void func_001397F8(u8 *arg0, UnkObj1397E0B *arg1)
{
    func_00119140(arg1);
    arg1->mField4A |= 0x20;
    *arg0 |= 0x80;
    if (data_0025E5DC != 0)
        data_0025E5DC->mField20A = 0;
}

struct UnkInner1398E0
{
    char pad00[0x18];
    int mField18; // 0x18
};

struct UnkEntry1398E0
{
    int mField00;
    UnkInner1398E0 *mInner04;
};

struct UnkObj1398E0
{
    char pad00[0x01];
    s8 mIdx01;               // 0x01
    char pad02[0x1A];
    UnkEntry1398E0 *mArr1C;  // 0x1C
};

int func_001398E0(UnkObj1398E0 *arg0)
{
    s8 idx = arg0->mIdx01;
    if (idx != -1)
        return arg0->mArr1C[idx].mInner04->mField18;
    return 0;
}

// Synthesized from m2c (0x00139720)
struct UnkObj139720
{
    int mField00; // 0x00
    int mField04; // 0x04
    int mField08; // 0x08
    void Method139720();
};

void UnkObj139720::Method139720()
{
    mField00 = 0;
    mField04 = 0;
    mField08 = 0;
}
