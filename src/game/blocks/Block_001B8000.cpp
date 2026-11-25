#include "common/types.h"

// Functions of 0x001B8000..0x001BBFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

int func_001B9D98();        // 0x001B9D98
void func_001BD978(void *); // 0x001BD978
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
    func_001BD978(arg0);
}

void func_001B9D78(void *arg0)
{
    func_001BD978(arg0);
}

void func_001BA638(void *arg0)
{
    func_001BD978(arg0);
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

// UnkObj1BB0D0 (0x001BB0D0..0x001BB168): no RTTI; its layout is the fields these methods use.
struct UnkObj1BB0D0
{
    char field_0x0[0x4];
    int mField4;         // 0x4
    int mField8;         // 0x8
    void *mFieldC;       // 0xC

    int GetField8();     // 0x001BB0D0
    void Method1BB120(); // 0x001BB120
    void Method1BB168(); // 0x001BB168
};

int UnkObj1BB0D0::GetField8()
{
    return mField8;
}

void UnkObj1BB0D0::Method1BB120()
{
    mField8 = 0;
}

void UnkObj1BB0D0::Method1BB168()
{
    void *tmp;

    tmp = mFieldC;
    if (tmp != NULL)
    {
        func_001BD978(tmp);
        mFieldC = NULL;
    }
    mField4 = 0;
    mField8 = 0;
    func_001BD978(this);
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
