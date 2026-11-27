#include "common/types.h"

// Functions of 0x001F0000..0x001F3FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

void func_001F2EE8(int *arg0, int arg1)
{
    *arg0 = arg1;
}

int func_001F2EF0(int *arg0)
{
    return *arg0;
}

int func_001F2F08(int arg0)
{
    return arg0;
}

int func_001F2F10(int arg0)
{
    return arg0;
}

int func_001F2F18(int arg0)
{
    return arg0;
}

int func_001F2F20(int arg0)
{
    return arg0;
}

int func_001F30B8(int arg0)
{
    return arg0 + 0x30;
}

