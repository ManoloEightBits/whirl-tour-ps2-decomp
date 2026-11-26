#include "common/types.h"

// Functions of 0x00134000..0x00137FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001562E8();    // 0x001562E8
void func_00136FB8();    // 0x00136FB8
void func_001BDCF8(int); // 0x001BDCF8
void func_001BDE60(int); // 0x001BDE60

void func_00135B58()
{
    func_001562E8();
}

void func_00136C50(int arg0)
{
    func_001BDCF8(arg0 + 0xC);
}

void func_00136C70(int arg0)
{
    func_001BDE60(arg0 + 0xC);
}

void func_00136FB8()
{
}

void func_00136FD0()
{
}

void func_001BCAC0(int); // 0x001BCAC0

// UnkObj135A50 (0x00135A50..0x00135B48): no RTTI; its layout is the fields these methods use.
struct UnkObj135A50
{
    char field_0x0[0xC4];
    int mFieldC4;          // 0xC4
    int mFieldC8;          // 0xC8
    int mFieldCC;          // 0xCC
    char field_0xD0[0x44];
    int mField114;         // 0x114

    void Method135A50();   // 0x00135A50
    void Method135A60();   // 0x00135A60
    void Method135AD8();   // 0x00135AD8
    void Method135B48();   // 0x00135B48
};

void UnkObj135A50::Method135A50()
{
    mFieldC4 = 1;
}

void UnkObj135A50::Method135A60()
{
    mFieldC8 = 1;
}

void UnkObj135A50::Method135AD8()
{
    mFieldCC = 1;
}

void UnkObj135A50::Method135B48()
{
    mField114 = 1;
}

// UnkObj136B90 (0x00136B90): no RTTI; its layout is the fields these methods use.
struct UnkObj136B90
{
    f32 mField0;                                           // 0x0
    f32 mField4;                                           // 0x4
    f32 mField8;                                           // 0x8
    f32 mFieldC;                                           // 0xC
    f32 mField10;                                          // 0x10
    f32 mField14;                                          // 0x14

    void Method136B90(f32 fparg0, f32 fparg1, f32 fparg2); // 0x00136B90
};

void UnkObj136B90::Method136B90(f32 fparg0, f32 fparg1, f32 fparg2)
{
    mField10 = 0.0f;
    mField0 = fparg0;
    mField4 = fparg1;
    mField8 = fparg2;
    mField14 = fparg0;
    if (fparg2 != mField10)
    {
        mFieldC = (f32) ((fparg1 - fparg0) / fparg2);
        return;
    }
    mField14 = fparg1;
    mFieldC = (f32) (fparg1 - fparg0);
}

// UnkObj136D78 (0x00136D78): no RTTI; its layout is the fields these methods use.
struct UnkObj136D78
{
    char field_0x0[0x6C];
    int mField6C;         // 0x6C

    void Method136D78();  // 0x00136D78
};

void UnkObj136D78::Method136D78()
{
    func_001BCAC0(mField6C);
}

struct UnkObj136FC0
{
    char pad00[0x08];
    void *mField08; // 0x08
};

void func_00136FC0(UnkObj136FC0 *arg0)
{
    arg0->mField08 = (void *)func_00136FB8;
}

struct UnkSub137818
{
    char pad00[0x28];
    u32 mField28; // 0x28
};

struct UnkObj137818
{
    char pad00[0x1C];
    UnkSub137818 *mField1C; // 0x1C
};

void func_00137818(UnkObj137818 *arg0)
{
    arg0->mField1C->mField28 &= 0xFFFFFFFE;
}
