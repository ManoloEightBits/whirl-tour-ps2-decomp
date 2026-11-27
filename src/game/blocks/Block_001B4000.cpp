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

int func_001C13D0(int); // 0x001C13D0

struct UnkObj1B7CA8
{
    u16 mField00; // 0x00
    u16 mField02; // 0x02

    void ByteSwap1B7CA8(); // 0x001B7CA8
};

void UnkObj1B7CA8::ByteSwap1B7CA8()
{
    mField00 = func_001C13D0(mField00);
    mField02 = func_001C13D0(mField02);
}

void QuatAlignHemisphere1B4E18(f32 *a, f32 *b)
{
    f32 x = a[0];
    f32 y = a[1];
    f32 z = a[2];
    f32 w = a[3];
    if (x * b[0] + y * b[1] + z * b[2] + w * b[3] < 0.0f)
    {
        a[0] = -x;
        a[1] = -y;
        a[2] = -z;
        a[3] = -w;
    }
}

f32 Sin1B1910(f32); // 0x001B1910
f32 Cos1B19E8(f32); // 0x001B19E8

void QuatFromAngleX1B4948(f32 *q, f32 angle)
{
    f32 half = angle * 0.5f;
    f32 s = Sin1B1910(half);
    q[1] = 0.0f;
    q[2] = 0.0f;
    q[0] = s;
    q[3] = Cos1B19E8(half);
}

struct UnkBuf1B6548
{
    int mCap00;  // 0x00
    int mLen04;  // 0x04
    char *mStr08; // 0x08
    char mBuf0C[1]; // 0x0C
};

void *MemAlloc1BD958(int); // 0x001BD958

UnkBuf1B6548 *func_001B6548(int arg0)
{
    UnkBuf1B6548 *p = (UnkBuf1B6548 *)MemAlloc1BD958(arg0 + 0xD);
    if (p != 0)
    {
        p->mCap00 = arg0;
        p->mStr08 = p->mBuf0C;
        p->mLen04 = 0;
        p->mBuf0C[0] = 0;
    }
    return p;
}

struct UnkObj1B6F58
{
    char pad00[0x06];
    u16 mField06; // 0x06
    void *mField08; // 0x08
};

void MemFree1BD978(void *); // 0x001BD978

void func_001B6F58(UnkObj1B6F58 *arg0)
{
    arg0->mField06 = 0;
    if (arg0->mField08 != 0)
    {
        MemFree1BD978(arg0->mField08);
        arg0->mField08 = 0;
    }
}
