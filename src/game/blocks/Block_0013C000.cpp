#include "common/types.h"
#include "common/libc.h"
#include "game/GL.h"

// Functions of 0x0013C000..0x0013FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// UnkObj13F690 (0x0013F690..0x0013F6D8): no RTTI; its layout is the fields these methods use.
struct UnkObj13F690
{
    int mField0;                 // 0x0
    int mField4;                 // 0x4
    char field_0x8[0x1A8];
    int mField1B0;               // 0x1B0
    char field_0x1B4[0x18];
    int mField1CC;               // 0x1CC

    void Method13F690(int arg1); // 0x0013F690
    void SetField4(int v);    // 0x0013F6A0
    void Method13F6A8();         // 0x0013F6A8
    void Method13F6B0();         // 0x0013F6B0
    int GetField1B0();           // 0x0013F6D0
    void Method13F6D8();         // 0x0013F6D8
};

void UnkObj13F690::Method13F690(int arg1)
{
    mField0 = arg1;
    mField4 = 0;
}

void UnkObj13F690::SetField4(int v)
{
    mField4 = v;
}

void UnkObj13F690::Method13F6A8()
{
    mField4 = 0;
}

void UnkObj13F690::Method13F6B0()
{
    mField4 += 1;
}

int UnkObj13F690::GetField1B0()
{
    return mField1B0;
}

void UnkObj13F690::Method13F6D8()
{
    glBindTexture(GL_TEXTURE_2D, mField1CC);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, 0x100, 0x100);
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_0013F6C0(int *arg0)
{
    return *arg0 == 0;
}

void func_001BB250(int, int *); // 0x001BB250
extern int data_0025E5C4;

struct UnkNamed13FA30
{
    char pad00[0x10];
    char mName10[0x20]; // 0x10
};

// A qsort comparison: by the name at +0x10 of the objects two entries point to.
int func_0013FA30(UnkNamed13FA30 **a, UnkNamed13FA30 **b)
{
    return strcmp((*a)->mName10, (*b)->mName10);
}

void func_0013FA58(int arg0, int arg1)
{
    int value;

    value = arg1;
    func_001BB250(data_0025E5C4, &value);
}
