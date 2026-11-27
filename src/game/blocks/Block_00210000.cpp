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

