#include "common/types.h"

// Functions of 0x001C8000..0x001CBFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

int func_001CA2A0(int arg0)
{
    return arg0;
}

void func_001CADE0()
{

}

void func_001CB250()
{

}

struct UnkObj1CA2F8
{
    int GetField10();                   // 0x001CA300
    s16 GetField1A();                   // 0x001CA308
    int GetField14();                   // 0x001CA340
    f32 GetField54();                   // 0x001CA3F8
    int func_001CA560();                // 0x001CA560
    int GetField8();                    // 0x001CA6F0
    int GetFieldC();                    // 0x001CA6F8

    char field_0x0[0x8];
    int mField8;              // 0x8
    int mFieldC;              // 0xC
    int mField10;             // 0x10
    int mField14;             // 0x14
    char field_0x18[0x2];
    s16 mField1A;             // 0x1A
    char field_0x1C[0x38];
    f32 mField54;             // 0x54
};

int UnkObj1CA2F8::GetField10() { return mField10; }
s16 UnkObj1CA2F8::GetField1A() { return mField1A; }
int UnkObj1CA2F8::GetField14() { return mField14; }
f32 UnkObj1CA2F8::GetField54() { return mField54; }
int UnkObj1CA2F8::func_001CA560() { return 2; }
int UnkObj1CA2F8::GetField8() { return mField8; }
int UnkObj1CA2F8::GetFieldC() { return mFieldC; }

