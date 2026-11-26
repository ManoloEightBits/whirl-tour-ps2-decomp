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

void func_0022FCC8(int, int, int, int); // 0x0022FCC8

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
        func_0022FCC8(mFieldC, tmp, mField0, arg1);
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
