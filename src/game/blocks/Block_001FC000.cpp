#include "common/types.h"

// Functions of 0x001FC000..0x001FFFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

void func_001FD2A8(int *arg0)
{
    *arg0 = 1;
}

void func_001FD2B8(int *arg0)
{
    *arg0 = 0;
}

int func_001FD2C0(int *arg0)
{
    return *arg0;
}

void func_001FD748(int *arg0)
{
    *arg0 = 1;
}

void func_001FD758(int *arg0)
{
    *arg0 = 0;
}

int func_001FD760(int *arg0)
{
    return *arg0;
}

int func_001FDD18(int arg0)
{
    return arg0;
}

struct UnkObj1FE830
{
    void func_001FE978();               // 0x001FE978
    void func_001FE980();               // 0x001FE980
    int GetField4();                    // 0x001FE9D0

    char field_0x0[0x4];
    int mField4;              // 0x4
};

void UnkObj1FE830::func_001FE978() {}
void UnkObj1FE830::func_001FE980() {}
int UnkObj1FE830::GetField4() { return mField4; }

