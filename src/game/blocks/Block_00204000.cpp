#include "common/types.h"

// Functions of 0x00204000..0x00207FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

int func_00206EB8(int arg0)
{
    return arg0;
}

f32 func_00206EE8(f32 fparg0)
{
    return fabsf(fparg0);
}

