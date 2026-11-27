#include "common/types.h"

// Functions of 0x001F4000..0x001F7FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

int func_001F73F8(int *arg0)
{
    return *arg0;
}

extern "C" void func_001F7B18(void *, void *); // 0x001F7B18
extern "C" void func_001D9AD8(void *);         // 0x001D9AD8

struct UnkIVPObj1F48A0
{
    char pad00[0x14];
    void *mEnv14;         // 0x14
    char pad18[0x60];
    u8 mType78;           // 0x78
    char pad79[0x23];
    void *mCore9C;        // 0x9C
    void *mFieldA0;       // 0xA0
};

void func_001F48A0(int objInt)
{
    UnkIVPObj1F48A0 *obj = (UnkIVPObj1F48A0 *)objInt;
    if (obj->mType78 != 8)
    {
        func_001D9AD8(obj->mCore9C);
    }
    else
    {
        func_001F7B18(obj->mEnv14, obj->mFieldA0);
    }
}
