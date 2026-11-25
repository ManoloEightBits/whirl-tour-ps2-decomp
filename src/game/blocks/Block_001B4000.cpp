#include "common/types.h"
#include "common/libc.h"

// Functions of 0x001B4000..0x001B7FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void MemFree1BD978(void *); // 0x001BD978
void func_002306F0(int);    // 0x002306F0

void func_001B4F08()
{
}

void func_001B4F10()
{
    func_002306F0(0);
}

void func_001B4F30()
{
}

void func_001B6590(void *arg0)
{
    MemFree1BD978(arg0);
}


// UnkObj1B61B0 (0x001B61B0..0x001B61B8): no RTTI; its layout is the fields these methods use.
struct UnkObj1B61B0
{
    char field_0x0[0x4];
    int mField4;         // 0x4
    int mField8;         // 0x8

    int GetField4();     // 0x001B61B0
    int GetField8();     // 0x001B61B8
};

int UnkObj1B61B0::GetField4()
{
    return mField4;
}

int UnkObj1B61B0::GetField8()
{
    return mField8;
}

// UnkObj1B6530 (0x001B6530): no RTTI; its layout is the fields these methods use.
struct UnkObj1B6530
{
    char field_0x0[0x4];
    int mField4;         // 0x4
    s8 *mField8;         // 0x8

    void Method1B6530(); // 0x001B6530
};

void UnkObj1B6530::Method1B6530()
{
    mField4 = 0;
    *mField8 = 0;
}

// UnkObj1B6540 (0x001B6540): no RTTI; its layout is the fields these methods use.
struct UnkObj1B6540
{
    char field_0x0[0x8];
    int mField8;         // 0x8

    int GetField8();     // 0x001B6540
};

int UnkObj1B6540::GetField8()
{
    return mField8;
}

// UnkObj1B6F00 (0x001B6F00): no RTTI; its layout is the fields these methods use.
struct UnkObj1B6F00
{
    char field_0x0[0x6];
    u16 mField6;         // 0x6
    u8 *mField8;         // 0x8

    void Method1B6F00(); // 0x001B6F00
};

void UnkObj1B6F00::Method1B6F00()
{
    u8 *buf;

    buf = mField8;
    if (buf != NULL)
    {
        memset(buf + 2, 0, mField6 - 2);
    }
}

// UnkObj1B7010 (0x001B7010): no RTTI; its layout is the fields these methods use.
struct UnkObj1B7010
{
    char field_0x0[0x6];
    s16 mField6;         // 0x6
    void *mField8;       // 0x8

    void Method1B7010(); // 0x001B7010
};

void UnkObj1B7010::Method1B7010()
{
    void *tmp;

    mField6 = 0;
    tmp = mField8;
    if (tmp != NULL)
    {
        MemFree1BD978(tmp);
        mField8 = NULL;
    }
    MemFree1BD978(this);
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_001B6410(int *arg0)
{
    return *arg0 & 0x80000000;
}

void func_001B6420(int *arg0)
{
    *arg0 |= 0x80000000;
}

void func_001B6438(int *arg0)
{
    *arg0 &= 0x7FFFFFFF;
}

int func_001B66F8(int *arg0)
{
    return *arg0;
}

void func_001B6700(int *arg0, int arg1)
{
    *arg0 |= arg1;
}

void func_001B6710(int *arg0, int arg1)
{
    *arg0 &= ~arg1;
}
