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
