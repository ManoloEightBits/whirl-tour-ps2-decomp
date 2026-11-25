#include "common/types.h"
#include "common/libc.h"

// Functions of 0x001C0000..0x001C3FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void MemFree1BD978(void *);       // 0x001BD978
void func_00239BE0(int);          // 0x00239BE0
int func_0023CE78(int, int, int); // 0x0023CE78
int func_0023D320(int, int, int); // 0x0023D320

int func_001C00F8(int arg0, int arg1, int arg2)
{
    int result;

    func_00239BE0(0);
    result = func_0023D320(arg0 - 1, arg1, arg2);
    func_00239BE0(0);
    return result;
}

int func_001C02A0(int arg0, int arg1, int arg2)
{
    int result;

    func_00239BE0(0);
    result = func_0023CE78(arg0 - 1, arg1, arg2);
    func_00239BE0(0);
    return result;
}

void func_001C03A0(void *arg0)
{
    MemFree1BD978(arg0);
}

int func_001C13A8(u32 arg0)
{
    return (arg0 >> 0x18) | ((arg0 >> 8) & 0xFF00) | ((arg0 & 0xFF00) << 8) | (arg0 << 0x18);
}

int func_001C1428(u32 arg0)
{
    return (arg0 >> 0x18) | ((arg0 >> 8) & 0xFF00) | ((arg0 & 0xFF00) << 8) | (arg0 << 0x18);
}

void func_001C38D0(char *arg0, char *arg1)
{
    strcpy(arg1, arg0 + 0x3030);
}

void func_001BB128(int);         // 0x001BB128
int func_001C0840(void *);       // 0x001C0840
int func_001C13A8(unsigned int); // 0x001C13A8
void func_001C13D0(int);         // 0x001C13D0

// UnkObj1C0E80 (0x001C0E80..0x001C10D0): no RTTI; its layout is the fields these methods use.
struct UnkObj1C0E80
{
    char field_0x0[0x4];
    int mField4;           // 0x4
    int mField8;           // 0x8
    void *mFieldC;         // 0xC
    char field_0x10[0x10];
    int mField20;          // 0x20
    char field_0x24[0x4C];
    int mField70;          // 0x70

    int GetField4();       // 0x001C0E80
    void Method1C0F58();   // 0x001C0F58
    void Method1C0FF0();   // 0x001C0FF0
    void Method1C1070();   // 0x001C1070
    int Method1C10C0();    // 0x001C10C0
    int GetField8();       // 0x001C10D0
};

int UnkObj1C0E80::GetField4()
{
    return mField4;
}

void UnkObj1C0E80::Method1C0F58()
{
    func_001BB128(mField70);
    mField20 = func_001C0840(this);
}

void UnkObj1C0E80::Method1C0FF0()
{
    mField8 = 0;
}

void UnkObj1C0E80::Method1C1070()
{
    MemFree1BD978(mFieldC);
    MemFree1BD978(this);
}

int UnkObj1C0E80::Method1C10C0()
{
    return mField4 - mField8;
}

int UnkObj1C0E80::GetField8()
{
    return mField8;
}

// UnkObj1C10D8 (0x001C10D8..0x001C10E0): no RTTI; its layout is the fields these methods use.
struct UnkObj1C10D8
{
    char field_0x0[0x4];
    int mField4;         // 0x4
    int mField8;         // 0x8
    int mFieldC;         // 0xC

    int GetFieldC();     // 0x001C10D8
    int Method1C10E0();  // 0x001C10E0
};

int UnkObj1C10D8::GetFieldC()
{
    return mFieldC;
}

int UnkObj1C10D8::Method1C10E0()
{
    int tmp;

    tmp = mField8;
    if (mField4 != tmp)
    {
        return mFieldC + tmp;
    }
    return 0;
}

// UnkObj1C1C78 (0x001C1C78..0x001C1D20): no RTTI; its layout is the fields these methods use.
struct UnkObj1C1C78
{
    char field_0x0[0x104];
    int mField104;                                                 // 0x104
    int mField108;                                                 // 0x108
    char field_0x10C[0x28];
    u16 mField134;                                                 // 0x134
    u16 mField136;                                                 // 0x136
    u16 mField138;                                                 // 0x138
    u16 mField13A;                                                 // 0x13A

    void Method1C1C78(u16 *arg1, u16 *arg2, u16 *arg3, u16 *arg4); // 0x001C1C78
    int GetField108();                                             // 0x001C1D08
    void Method1C1D10();                                           // 0x001C1D10
    int GetField104();                                             // 0x001C1D18
    void Method1C1D20();                                           // 0x001C1D20
};

void UnkObj1C1C78::Method1C1C78(u16 *arg1, u16 *arg2, u16 *arg3, u16 *arg4)
{
    if (arg1 != NULL)
    {
        *arg1 = mField134;
    }
    if (arg2 != NULL)
    {
        *arg2 = mField136;
    }
    if (arg3 != NULL)
    {
        *arg3 = mField138;
    }
    if (arg4 != NULL)
    {
        *arg4 = mField13A;
    }
}

int UnkObj1C1C78::GetField108()
{
    return mField108;
}

void UnkObj1C1C78::Method1C1D10()
{
    mField108 = 0;
}

int UnkObj1C1C78::GetField104()
{
    return mField104;
}

void UnkObj1C1C78::Method1C1D20()
{
    mField104 = 0;
}

// UnkObj1C3BA8 (0x001C3BA8..0x001C3BE8): no RTTI; its layout is the fields these methods use.
struct UnkObj1C3BA8
{
    char field_0x0[0xC];
    int mFieldC;         // 0xC
    int mField10;        // 0x10
    u16 mField14;        // 0x14

    void Method1C3BA8(); // 0x001C3BA8
    void Method1C3BC8(); // 0x001C3BC8
    int Method1C3BE8();  // 0x001C3BE8
};

void UnkObj1C3BA8::Method1C3BA8()
{
    func_001C13D0(mField14);
}

void UnkObj1C3BA8::Method1C3BC8()
{
    func_001C13A8(mField10);
}

int UnkObj1C3BA8::Method1C3BE8()
{
    return func_001C13A8(mFieldC) + 0x30;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_001C0E78(int *arg0)
{
    return *arg0;
}


