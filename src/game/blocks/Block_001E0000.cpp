#include "common/types.h"

// Functions of 0x001E0000..0x001E3FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

void func_001E0888()
{

}

void func_001E0F78()
{

}

f32 func_001E1740()
{
    return 1.0f;
}

void func_001E19D0()
{

}

void func_001E2440()
{

}

void func_001E2648()
{

}

struct UnkObj1E1700
{
    int func_001E1708();                // 0x001E1708
    f32 GetField48();                   // 0x001E1A78
    f32 GetField54();                   // 0x001E1A88
    u16 GetField2();                    // 0x001E1B90
    u16 GetField2b();                   // 0x001E1C38

    char field_0x0[0x2];
    u16 mField2;              // 0x2
    char field_0x4[0x44];
    f32 mField48;             // 0x48
    char field_0x4C[0x8];
    f32 mField54;             // 0x54
};

int UnkObj1E1700::func_001E1708() { return 2000; }
f32 UnkObj1E1700::GetField48() { return mField48; }
f32 UnkObj1E1700::GetField54() { return mField54; }
u16 UnkObj1E1700::GetField2() { return mField2; }
u16 UnkObj1E1700::GetField2b() { return mField2; }

