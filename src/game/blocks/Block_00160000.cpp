#include "common/types.h"

// Functions of 0x00160000..0x00163FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00163698(); // 0x00163698

void func_00163A30()
{
    func_00163698();
}

// UnkObj1618D0 (0x001618D0..0x001618E8): no RTTI; its layout is the fields these methods use.
struct UnkObj1618D0
{
    char field_0x0[0x1C];
    int mField1C;                // 0x1C

    int GetField1C();            // 0x001618D0
    void Method1618D8(int arg1); // 0x001618D8
    void Method1618E8(int arg1); // 0x001618E8
};

int UnkObj1618D0::GetField1C()
{
    return mField1C;
}

void UnkObj1618D0::Method1618D8(int arg1)
{
    mField1C |= arg1;
}

void UnkObj1618D0::Method1618E8(int arg1)
{
    mField1C &= ~arg1;
}
