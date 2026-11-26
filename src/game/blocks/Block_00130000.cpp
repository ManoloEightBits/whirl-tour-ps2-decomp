#include "common/types.h"
#include "game/FEScreen.h"

// Functions of 0x00130000..0x00133FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void MemFree1BD978(void *); // 0x001BD978

void CleanupDialog1309E0(void *arg0)
{
    MemFree1BD978(arg0);
}

// UnkObj130608 (0x00130608): no RTTI; its layout is the fields these methods use.
struct UnkObj130608
{
    char field_0x0[0x4];
    int mField4;          // 0x4
    char field_0x8[0x80];
    int mField88;         // 0x88

    int Method130608();   // 0x00130608
};

int UnkObj130608::Method130608()
{
    int var_a1;
    int var_v1;

    var_v1 = mField4;
    var_a1 = 1;
    if (var_v1 > 0)
    {
        do
        {
            var_v1 -= 1;
            var_a1 = ((mField88 ^ 1) & 1) ? 0 : var_a1;
        } while (var_v1 != 0);
    }
    return var_a1;
}

// UnkObj130750 (0x00130750): no RTTI; its layout is the fields these methods use.
struct UnkObj130750
{
    char field_0x0[0x88];
    int mField88;         // 0x88

    int Method130750();   // 0x00130750
};

int UnkObj130750::Method130750()
{
    return mField88 & 1;
}

// UnkObj130AC0 (0x00130AC0..0x00130AC8): no RTTI; its layout is the fields these methods use.
struct UnkObj130AC0
{
    char field_0x0[0x18];
    int mField18;              // 0x18
    int mField1C;              // 0x1C

    void SetField18(int v); // 0x00130AC0
    void SetField1C(int v); // 0x00130AC8
};

void UnkObj130AC0::SetField18(int v)
{
    mField18 = v;
}

void UnkObj130AC0::SetField1C(int v)
{
    mField1C = v;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

extern int data_0025E1A0;
extern int data_0025E1A4;

void func_00130008()
{
    data_0025E1A4 = 0;
}

void func_00130018()
{
    data_0025E1A4 = 0;
    data_0025E1A0 = 0;
}

FESub08::~FESub08()
{
}
