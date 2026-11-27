#include "common/types.h"

// Functions of 0x001D8000..0x001DBFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

int func_001D8270(int arg0)
{
    return arg0 + 0x40;
}

int func_001D8280(int arg0)
{
    return arg0 + 0x20;
}

int func_001D8288(int arg0)
{
    return arg0 + 0x40;
}

int func_001D82F0(int *arg0)
{
    return *arg0 & 3;
}

int func_001D8390(int arg0)
{
    return arg0 + 0x100;
}

int func_001D8398(int arg0)
{
    return arg0 + 0x130;
}

int func_001DBB68(int arg0)
{
    return arg0;
}

int func_001DBCE8(int arg0)
{
    return arg0 + 0x34;
}

int func_001DBD40(int arg0)
{
    return arg0 + 0xC0;
}

int func_001DBD20(int arg0)
{
    return arg0 + 0x88;
}

