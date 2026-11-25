#include "common/types.h"
#include "common/libc.h"

// Functions of 0x00190000..0x00193FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

int func_00190D88();        // 0x00190D88
void MemFree1BD978(void *); // 0x001BD978

int func_00190BB8(int arg0)
{
    return arg0 + 0x1900;
}

int func_00190D90()
{
    return func_00190D88() == 0;
}

int func_00190DB8(int arg0)
{
    return arg0 + 0xC;
}

int func_00190DC0(int arg0)
{
    return arg0 + 4;
}

void func_00191768(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_00191E40(void *arg0)
{
    MemFree1BD978(arg0);
}

// UnkObj190B68 (0x00190B68..0x00190BA0): no RTTI; its layout is the fields these methods use.
struct UnkObj190B68
{
    char field_0x0[0x8];
    int mField8;          // 0x8
    int mFieldC;          // 0xC
    char field_0x10[0x4];
    int mField14;         // 0x14

    int GetField8();      // 0x00190B68
    int Method190B70();   // 0x00190B70
    int GetField14();     // 0x00190BA0
};

int UnkObj190B68::GetField8()
{
    return mField8;
}

int UnkObj190B68::Method190B70()
{
    return mFieldC != 0;
}

int UnkObj190B68::GetField14()
{
    return mField14;
}

// UnkObj190D70 (0x00190D70..0x00190D88): no RTTI; its layout is the fields these methods use.
struct UnkObj190D70
{
    char field_0x0[0x30];
    int mField30;         // 0x30
    char field_0x34[0xC];
    int mField40;         // 0x40
    int mField44;         // 0x44
    int mField48;         // 0x48

    int GetField48();     // 0x00190D70
    int GetField44();     // 0x00190D78
    int GetField40();     // 0x00190D80
    int GetField30();     // 0x00190D88
};

int UnkObj190D70::GetField48()
{
    return mField48;
}

int UnkObj190D70::GetField44()
{
    return mField44;
}

int UnkObj190D70::GetField40()
{
    return mField40;
}

int UnkObj190D70::GetField30()
{
    return mField30;
}

// UnkObj190DB0 (0x00190DB0): no RTTI; its layout is the fields these methods use.
struct UnkObj190DB0
{
    char field_0x0[0x2C];
    int mField2C;         // 0x2C

    int GetField2C();     // 0x00190DB0
};

int UnkObj190DB0::GetField2C()
{
    return mField2C;
}

// UnkObj191320 (0x00191320): no RTTI; its layout is the fields these methods use.
struct UnkObj191320
{
    char field_0x0[0x3480];
    int mField3480;         // 0x3480

    int Method191320();     // 0x00191320
};

int UnkObj191320::Method191320()
{
    if (func_00190D88() == 0)
    {
        mField3480 = 0;
    }
    return 1;
}

// UnkObj1914A0 (0x001914A0..0x00191568): no RTTI; its layout is the fields these methods use.
struct UnkObj1914A0
{
    char field_0x0[0x4];
    int mField4;             // 0x4
    char field_0x8[0x2C];
    int mField34;            // 0x34
    char field_0x38[0x3448];
    int mField3480;          // 0x3480

    int GetField3480();      // 0x001914A0
    int GetField4();         // 0x00191558
    void Method191568();     // 0x00191568
};

int UnkObj1914A0::GetField3480()
{
    return mField3480;
}

int UnkObj1914A0::GetField4()
{
    return mField4;
}

void UnkObj1914A0::Method191568()
{
    mField34 += 1;
}

// UnkObj192470 (0x00192470): no RTTI; its layout is the fields these methods use.
struct UnkObj192470
{
    char field_0x0[0x20];
    int mField20;         // 0x20

    int GetField20();     // 0x00192470
};

int UnkObj192470::GetField20()
{
    return mField20;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_00191E60(int, f32, f32, f32); // 0x00191E60
int MemAlloc1BD958(int);                // 0x001BD958

int func_00190B80(int *arg0)
{
    return *arg0;
}

int func_00191560(int *arg0)
{
    return *arg0;
}

int func_00191DD8(f32 fparg0, f32 fparg1, f32 fparg2)
{
    int temp_v0;

    temp_v0 = MemAlloc1BD958(0x3C);
    if (temp_v0 != 0)
    {
        func_00191E60(temp_v0, fparg0, fparg1, fparg2);
    }
    return temp_v0;
}


