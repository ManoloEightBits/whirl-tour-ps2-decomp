#include "common/types.h"

// Functions of 0x00210000..0x00213FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

int func_00212060(int *arg0)
{
    return *arg0 & 0xFFF;
}

int func_00212070(u32 *arg0)
{
    return ((u32) *arg0 >> 0xC) & 0xFFF;
}

u32 func_00212090(u32 *arg0)
{
    return (u32) *arg0 >> 0x1F;
}

int func_002120A0(int arg0)
{
    return arg0 + 4;
}

int func_002120A8(int arg0)
{
    return arg0 + 4;
}

int func_002120C0(int arg0)
{
    return arg0 + 0x10;
}

int func_002120C8(int arg0)
{
    return arg0 + 0x10;
}

void func_002120D0(int *arg0, int arg1)
{
    *arg0 = arg1;
}

int func_00212130(int arg0)
{
    return arg0 + 0x10;
}

int func_00212138(int arg0)
{
    return arg0 + 0x10;
}

int func_002121B8(int arg0)
{
    return arg0 + 0x1C;
}

int func_002121D0(int *arg0)
{
    return *arg0 == 0;
}

int func_00212200(int arg0)
{
    return arg0 & 0xFFFFFFF0;
}

int func_00212270(int arg0)
{
    return ((int) (arg0 & 0xC) >> 2) - 1;
}

struct UnkObj211F48
{
    void SetFieldC(int v);              // 0x00211F48
    int GetFieldC();                    // 0x00211F50
    void SetField0(u16 v);              // 0x00211F58
    u16 GetField0();                    // 0x00211FA8
    s16 GetFieldCb();                   // 0x00212160
    int GetField4();                    // 0x00212188

    u16 mField0;              // 0x0
    char field_0x2[0x2];
    int mField4;              // 0x4
    char field_0x8[0x4];
    int mFieldC;              // 0xC
};

void UnkObj211F48::SetFieldC(int v) { mFieldC = v; }
int UnkObj211F48::GetFieldC() { return mFieldC; }
void UnkObj211F48::SetField0(u16 v) { mField0 = v; }
u16 UnkObj211F48::GetField0() { return mField0; }
s16 UnkObj211F48::GetFieldCb() { return mFieldC; }
int UnkObj211F48::GetField4() { return mField4; }

