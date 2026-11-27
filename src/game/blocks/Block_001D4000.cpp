#include "common/types.h"

// Functions of 0x001D4000..0x001D7FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

int func_001D64F8(int *arg0)
{
    return *arg0;
}

struct UnkObj1D5238
{
    void SetFieldEC(f32 v);             // 0x001D5238
    void SetField4(int v);              // 0x001D5240
    void SetField94(int v);             // 0x001D5248
    f32 GetField98();                   // 0x001D5568
    int GetField4();                    // 0x001D5698
    int func_001D5830();                // 0x001D5830

    char field_0x0[0x4];
    int mField4;              // 0x4
    char field_0x8[0x8C];
    int mField94;             // 0x94
    f32 mField98;             // 0x98
    char field_0x9C[0x50];
    f32 mFieldEC;             // 0xEC
};

void UnkObj1D5238::SetFieldEC(f32 v) { mFieldEC = v; }
void UnkObj1D5238::SetField4(int v) { mField4 = v; }
void UnkObj1D5238::SetField94(int v) { mField94 = v; }
f32 UnkObj1D5238::GetField98() { return mField98; }
int UnkObj1D5238::GetField4() { return mField4; }
int UnkObj1D5238::func_001D5830() { return 1; }

