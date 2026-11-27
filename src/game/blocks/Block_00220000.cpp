#include "common/types.h"

// Functions of 0x00220000..0x00223FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

int func_002221C0(int arg0)
{
    return arg0 + 0x40;
}

int func_002221C8(int arg0)
{
    return arg0 + 0x30;
}

int func_002221F0(int arg0)
{
    return arg0 + 0x10;
}

int func_002221F8(int arg0)
{
    return arg0 + 0x20;
}

