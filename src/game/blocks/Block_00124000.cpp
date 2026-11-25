#include "common/types.h"

// Functions of 0x00124000..0x00127FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// UnkObj1272A0 (0x001272A0..0x00127328): no RTTI; its layout is the fields these methods use.
struct UnkObj1272A0
{
    char field_0x0[0x28];
    int mField28;                  // 0x28
    f32 mField2C;                  // 0x2C
    char field_0x30[0xC];
    f32 mField3C;                  // 0x3C

    void Method1272A0(int arg1);   // 0x001272A0
    void Method1272B0(int arg1);   // 0x001272B0
    void SetField2C(f32 fparg0);   // 0x00127320
    void Method127328(f32 fparg0); // 0x00127328
};

void UnkObj1272A0::Method1272A0(int arg1)
{
    mField28 |= arg1;
}

void UnkObj1272A0::Method1272B0(int arg1)
{
    mField28 &= ~arg1;
}

void UnkObj1272A0::SetField2C(f32 fparg0)
{
    mField2C = fparg0;
}

void UnkObj1272A0::Method127328(f32 fparg0)
{
    f32 tmp;

    tmp = fparg0;
    if (tmp < 0.05f)
    {
        tmp = 0.05f;
    }
    mField3C = tmp;
}

// UnkObj127458 (0x00127458): no RTTI; its layout is the fields these methods use.
struct UnkObj127458
{
    char field_0x0[0x6F];
    s8 mField6F;              // 0x6F

    void SetField6F(s8 v); // 0x00127458
};

void UnkObj127458::SetField6F(s8 v)
{
    mField6F = v;
}
