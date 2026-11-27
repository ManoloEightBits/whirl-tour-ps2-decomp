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

struct UnkObj2221B8
{
    int func_002221B8();                // 0x002221B8
    f32 GetField50();                   // 0x002221D0
    f32 GetField54();                   // 0x002221D8
    f32 GetField58();                   // 0x002221E0
    f32 GetField5C();                   // 0x002221E8
    void SetField50(f32 v);             // 0x00222200
    void SetField54(f32 v);             // 0x00222208
    void SetField58(f32 v);             // 0x00222210
    void SetField5C(f32 v);             // 0x00222218

    char field_0x0[0x50];
    f32 mField50;             // 0x50
    f32 mField54;             // 0x54
    f32 mField58;             // 0x58
    f32 mField5C;             // 0x5C
};

int UnkObj2221B8::func_002221B8() { return 500; }
f32 UnkObj2221B8::GetField50() { return mField50; }
f32 UnkObj2221B8::GetField54() { return mField54; }
f32 UnkObj2221B8::GetField58() { return mField58; }
f32 UnkObj2221B8::GetField5C() { return mField5C; }
void UnkObj2221B8::SetField50(f32 v) { mField50 = v; }
void UnkObj2221B8::SetField54(f32 v) { mField54 = v; }
void UnkObj2221B8::SetField58(f32 v) { mField58 = v; }
void UnkObj2221B8::SetField5C(f32 v) { mField5C = v; }

