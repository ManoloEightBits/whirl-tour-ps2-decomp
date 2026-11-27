#include "common/types.h"

// Functions of 0x00208000..0x0020BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

extern "C" f32 sqrtf(f32);

struct IVP_U_Float_Point
{
    f32 x;
    f32 y;
    f32 z;

    f32 Length208178(); // 0x00208178
};

f32 IVP_U_Float_Point::Length208178()
{
    return sqrtf(x * x + y * y + z * z);
}

