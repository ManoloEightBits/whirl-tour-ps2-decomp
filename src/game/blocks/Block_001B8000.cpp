#include "common/types.h"
#include "common/libc.h"
#include "game/UnkArray.h"

// Functions of 0x001B8000..0x001BBFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

int func_001B9D98();        // 0x001B9D98
void MemFree1BD978(void *); // 0x001BD978
void func_001C11D8();       // 0x001C11D8
void func_001C1450(int);    // 0x001C1450

void func_001B81C8(int arg0)
{
    func_001C11D8();
    func_001C1450(arg0 + 0x10);
}

void func_001B9160(int arg0)
{
    func_001C11D8();
    func_001C1450(arg0 + 0x10);
}

void func_001B9240(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001B9D78(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001BA638(void *arg0)
{
    MemFree1BD978(arg0);
}

int func_001BA658(int arg0)
{
    int result;

    result = 0;
    if (arg0 != 0)
    {
        result = func_001B9D98();
    }
    return result;
}

// UnkObj1B8D20 (0x001B8D20): no RTTI; its layout is the fields these methods use.
struct UnkObj1B8D20
{
    char field_0x0[0x20];
    f32 mField20;         // 0x20
    f32 mField24;         // 0x24

    f32 Method1B8D20();   // 0x001B8D20
};

f32 UnkObj1B8D20::Method1B8D20()
{
    f32 temp_f0;
    f32 temp_f1;

    temp_f0 = mField20;
    temp_f1 = mField24;
    mField24 = temp_f0;
    return temp_f0 - temp_f1;
}

// UnkObj1B91D8 (0x001B91D8): no RTTI; its layout is the fields these methods use.
struct UnkObj1B91D8
{
    char field_0x0[0x2];
    u16 mField2;         // 0x2

    u16 GetField2();     // 0x001B91D8
};

u16 UnkObj1B91D8::GetField2()
{
    return mField2;
}

int UnkArray1BB0D0::GetCount()
{
    return mCount08;
}

void UnkArray1BB0D0::Clear()
{
    mCount08 = 0;
}

void UnkArray1BB0D0::Destroy()
{
    void *tmp;

    tmp = mData0C;
    if (tmp != NULL)
    {
        MemFree1BD978(tmp);
        mData0C = NULL;
    }
    mField4 = 0;
    mCount08 = 0;
    MemFree1BD978(this);
}

// UnkObj1BB3E0 (0x001BB3E0): no RTTI; its layout is the fields these methods use.
struct UnkObj1BB3E0
{
    int mField0;                 // 0x0
    char field_0x4[0x4];
    int mField8;                 // 0x8
    int mFieldC;                 // 0xC

    void Method1BB3E0(int arg1); // 0x001BB3E0
};

void UnkObj1BB3E0::Method1BB3E0(int arg1)
{
    int tmp;

    tmp = mField8;
    if (tmp != 0)
    {
        qsort((void *)mFieldC, tmp, mField0, (int (*)(const void *, const void *))arg1);
    }
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_001B8E40(int *arg0)
{
    return *arg0 & 2;
}

int func_001B91E0(u16 *arg0)
{
    return ((*arg0 - 1) * 0x50) + 0x60;
}

int func_001BB0D8(int *arg0)
{
    return *arg0;
}

char *func_00151D70(char *dst, const char *src); // 0x00151D70: appends src (a strcat)
void *MemAlloc1BD958(int);     // 0x001BD958
extern int data_0027B528;
extern int data_0027B52C;
extern void *data_0027B530;   // an array of 8-byte entries: data_0027B528 used of data_0027B52C
extern char data_0027B538[0x80];
extern char data_0027B5B8[0x80];
extern char data_0027B638[0x80];

// Writes a, b and c one after another into dst.
void func_001B92F8(char *dst, const char *a, const char *b, const char *c)
{
    strcpy(dst, a);
    func_00151D70(dst, b);
    func_00151D70(dst, c);
}

void func_001BBB58(const char *s)
{
    data_0027B538[0] = 0;
    if (s != 0)
    {
        strcpy(data_0027B538, s);
    }
}

void func_001BBB88(const char *s)
{
    data_0027B5B8[0] = 0;
    if (s != 0)
    {
        strcpy(data_0027B5B8, s);
    }
}

void func_001BBBB8(const char *s)
{
    data_0027B638[0] = 0;
    if (s != 0)
    {
        strcpy(data_0027B638, s);
    }
}

// Doubles the capacity of the data_0027B530 array; returns 1 when the allocation worked.
int func_001BBE20()
{
    int ok = 0;
    void *grown = MemAlloc1BD958(data_0027B52C * 0x10);
    if (grown != 0)
    {
        ok = 1;
        memcpy(grown, data_0027B530, data_0027B528 * 8);
        MemFree1BD978(data_0027B530);
        data_0027B530 = grown;
        data_0027B52C *= 2;
    }
    return ok;
}

int func_001C1428(u32); // 0x001C1428

struct UnkObj1B8108
{
    u32 mField00; // 0x00
    u32 mField04; // 0x04

    void ByteSwap1B8108(); // 0x001B8108
};

void UnkObj1B8108::ByteSwap1B8108()
{
    mField00 = func_001C1428(mField00);
    mField04 = func_001C1428(mField04);
}

void func_001BDCA0(void *); // 0x001BDCA0
struct UnkObj1B7010 { void Method1B7010(); };
struct UnkObj1B6F00 { void Method1B6F00(); };

struct UnkObj1B8B30
{
    char field_0x0[0xC];
    UnkObj1B7010 *mField0C; // 0x0C
    char field_0x10[0x24];
    void *mField34;         // 0x34
    UnkObj1B7010 *mField38; // 0x38
    UnkObj1B7010 *mField3C; // 0x3C
    void *mField40;         // 0x40
    void *mField44;         // 0x44
    void *mField48;         // 0x48

    void Destroy1B8B30();   // 0x001B8B30
};

void UnkObj1B8B30::Destroy1B8B30()
{
    func_001BDCA0(mField34);
    mField0C->Method1B7010();
    mField38->Method1B7010();
    mField3C->Method1B7010();
    MemFree1BD978(mField40);
    MemFree1BD978(mField44);
    if (mField48 != 0)
        MemFree1BD978(mField48);
    MemFree1BD978(this);
}

struct UnkObj1B8BA0
{
    UnkObj1B6F00 *mField00; // 0x00
    int mField04;           // 0x04
    int mField08;           // 0x08
    f32 mField0C;           // 0x0C
    f32 mField10;           // 0x10
    f32 mField14;           // 0x14
    int mField18;           // 0x18
    int mField1C;           // 0x1C
    f32 mField20;           // 0x20
    int mField24;           // 0x24

    void Method1B8BA0(int a, int b, int c, f32 x, f32 y, f32 z); // 0x001B8BA0
};

void UnkObj1B8BA0::Method1B8BA0(int a, int b, int c, f32 x, f32 y, f32 z)
{
    mField04 = a;
    mField08 = b;
    mField0C = x;
    mField10 = y;
    mField14 = z;
    mField18 = c;
    mField20 = 1e-5f;
    mField1C = 0;
    mField24 = 0;
    mField00->Method1B6F00();
}

struct UnkObj1B9B30
{
    int mField00;  // 0x00
    void *mField04; // 0x04

    void Method1B9B30(int count, void *buf); // 0x001B9B30
};

void UnkObj1B9B30::Method1B9B30(int count, void *buf)
{
    mField00 = count;
    mField04 = buf;
    memset(buf, 0, count * 4);
}

int func_001C13A8(u32);          // 0x001C13A8
extern "C" f32 func_001C13E8(f32); // 0x001C13E8
int func_001C1428(u32);          // 0x001C1428

struct UnkPair1B8040
{
    u32 mField00; // 0x00
    u32 mField04; // 0x04
};

struct UnkObj1B8040
{
    char pad00[0x40];
    f32 mField40;           // 0x40
    f32 mField44;           // 0x44
    int mCount48;           // 0x48
    int mField4C;           // 0x4C
    u32 mField50;           // 0x50
    UnkPair1B8040 mPairs54[1]; // 0x54
};

void func_001B8040(UnkObj1B8040 *arg0)
{
{
    int i = 0;
    if (arg0->mCount48 > 0)
    {
        UnkPair1B8040 *p = arg0->mPairs54;
        do
        {
            i++;
            p->mField00 = func_001C1428(p->mField00);
            p->mField04 = func_001C1428(p->mField04);
            p++;
        } while (i < arg0->mCount48);
    }
    arg0->mField40 = func_001C13E8(arg0->mField40);
    arg0->mField44 = func_001C13E8(arg0->mField44);
    arg0->mField50 = func_001C1428(arg0->mField50);
    arg0->mCount48 = func_001C13A8(arg0->mCount48);
    arg0->mField4C = func_001C13A8(arg0->mField4C);
}
}

struct UnkNode1B9CA0
{
    UnkNode1B9CA0 *mNext00;
    int mField04;
    int mField08;
};

struct UnkTable1B9CA0
{
    int mCount00;
    UnkNode1B9CA0 **mBuckets04;
};

void HashTableForEach1B9CA0(UnkTable1B9CA0 *arg0, void (*cb)(int, int))
{
    for (int i = 0; i < arg0->mCount00; i++)
    {
        UnkNode1B9CA0 *node = arg0->mBuckets04[i];
        while (node != 0)
        {
            int a1 = node->mField08;
            int a0 = node->mField04;
            node = node->mNext00;
            cb(a0, a1);
        }
    }
}

void *MemAlloc1BD958(int); // 0x001BD958

UnkTable1B9CA0 *HashTableCreate1B9B60(int arg0)
{
    int bytes = arg0 * 4;
    UnkTable1B9CA0 *t = (UnkTable1B9CA0 *)MemAlloc1BD958(bytes + 8);
    UnkNode1B9CA0 **buckets = (UnkNode1B9CA0 **)(t + 1);
    if (t != 0)
    {
        t->mCount00 = arg0;
        t->mBuckets04 = buckets;
        memset(buckets, 0, bytes);
    }
    return t;
}

void HashNodeAlloc1B9D30(int arg0, int arg1)
{
    UnkNode1B9CA0 *node = (UnkNode1B9CA0 *)MemAlloc1BD958(0xC);
    if (node != 0)
    {
        node->mField04 = arg0;
        node->mField08 = arg1;
        node->mNext00 = 0;
    }
}

struct UnkClip1B7
{
    f32 GetField40(); // 0x001B7D20
};

struct UnkObj1B8CC0
{
    int mField00;          // 0x00
    UnkClip1B7 *mClip04;   // 0x04
    char pad08[0x18];
    f32 mField20;          // 0x20
    f32 mField24;          // 0x24
};

f32 func_001B8CC0(UnkObj1B8CC0 *arg0)
{
    return arg0->mField20 + arg0->mClip04->GetField40();
}

f32 func_001B8CF0(UnkObj1B8CC0 *arg0)
{
    return arg0->mField24 + arg0->mClip04->GetField40();
}
