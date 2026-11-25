#include "common/types.h"

// Functions of 0x00158000..0x0015BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

f32 func_00158F70()
{
    return 0.0f;
}

void func_00158F80()
{
}

void func_00158F88()
{
}

// UnkObj158860 (0x00158860..0x00158888): no RTTI; its layout is the fields these methods use.
struct UnkObj158860
{
    char field_0x0[0x3C];
    int mField3C;                // 0x3C
    int mField40;                // 0x40
    int mField44;                // 0x44

    int Method158860();          // 0x00158860
    void Method158870(int arg1); // 0x00158870
    void Method158888();         // 0x00158888
};

int UnkObj158860::Method158860()
{
    return mField40 == 0;
}

void UnkObj158860::Method158870(int arg1)
{
    mField40 = arg1;
    mField44 = 1;
    mField3C = 0;
}

void UnkObj158860::Method158888()
{
    mField3C += 1;
}
