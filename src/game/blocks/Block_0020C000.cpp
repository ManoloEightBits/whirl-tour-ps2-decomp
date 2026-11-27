#include "common/types.h"

// Functions of 0x0020C000..0x0020FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

void func_0020CDE8()
{

}

int func_0020D6B8(int *arg0)
{
    return *arg0 + 1;
}

int func_0020F060(int arg0)
{
    return arg0;
}

int func_0020D768(int arg0)
{
    return (((int) (arg0 * 0x3E9) >> 0x10) + (arg0 * 0x4B)) | 0x80000000;
}
