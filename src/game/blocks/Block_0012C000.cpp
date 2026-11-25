#include "common/types.h"

// Functions of 0x0012C000..0x0012FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_0012E5F8()
{
}

int func_0012ECB8(int arg0)
{
    return arg0 + 0x10;
}

void func_001BB128(int);    // 0x001BB128
void func_001BB168(int);    // 0x001BB168
void func_001BCAC0(int);    // 0x001BCAC0
void func_001BD978(void *); // 0x001BD978

// UnkObj12D0F0 (0x0012D0F0..0x0012D178): no RTTI; its layout is the fields these methods use.
struct UnkObj12D0F0
{
    int mField0;         // 0x0
    int mField4;         // 0x4

    void Method12D0F0(); // 0x0012D0F0
    void Method12D178(); // 0x0012D178
};

void UnkObj12D0F0::Method12D0F0()
{
    func_001BB128(mField0);
    func_001BB128(mField4);
}

void UnkObj12D0F0::Method12D178()
{
    func_001BB128(mField0);
    func_001BB128(mField4);
    func_001BB168(mField0);
    func_001BB168(mField4);
    func_001BD978(this);
}

// UnkObj12E408 (0x0012E408..0x0012E428): no RTTI; its layout is the fields these methods use.
struct UnkObj12E408
{
    char field_0x0[0xD0];
    int mFieldD0;         // 0xD0
    char field_0xD4[0x4];
    int mFieldD8;         // 0xD8
    int mFieldDC;         // 0xDC

    int Method12E408();   // 0x0012E408
    int Method12E428();   // 0x0012E428
};

int UnkObj12E408::Method12E408()
{
    if (mFieldD0 & 2)
    {
        return mFieldDC;
    }
    return 0;
}

int UnkObj12E408::Method12E428()
{
    if (mFieldD0 & 1)
    {
        return mFieldD8;
    }
    return 0;
}

// UnkObj12E7D8 (0x0012E7D8): no RTTI; its layout is the fields these methods use.
struct UnkObj12E7D8
{
    char field_0x0[0x14];
    int mField14;         // 0x14

    void Method12E7D8();  // 0x0012E7D8
};

void UnkObj12E7D8::Method12E7D8()
{
    func_001BCAC0(mField14);
}

// UnkObj12F188 (0x0012F188..0x0012F1A0): no RTTI; its layout is the fields these methods use.
struct UnkObj12F188
{
    char field_0x0[0x94];
    int mField94;                // 0x94
    int mField98;                // 0x98

    int GetField98();            // 0x0012F188
    void Method12F190(int arg1); // 0x0012F190
    void Method12F1A0(int arg1); // 0x0012F1A0
};

int UnkObj12F188::GetField98()
{
    return mField98;
}

void UnkObj12F188::Method12F190(int arg1)
{
    mField94 |= arg1;
}

void UnkObj12F188::Method12F1A0(int arg1)
{
    mField94 &= ~arg1;
}
