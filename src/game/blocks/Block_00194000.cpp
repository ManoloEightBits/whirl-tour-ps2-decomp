#include "common/types.h"

// Functions of 0x00194000..0x00197FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8();       // 0x001974D8
void MemFree1BD978(void *); // 0x001BD978

void func_001957F0()
{
    func_001974D8();
}

void func_00195A10(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_00196160()
{
}

void func_001961B0()
{
}

void func_001962C8()
{
}

void func_001962D0()
{
}

void func_00196410(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001965B0()
{
}

void func_001965F8(void *arg0)
{
    MemFree1BD978(arg0);
}

int func_00196648(int arg0)
{
    return ((arg0 - 1) * 0xC) + 0x10;
}

int func_00196D80()
{
    return 0;
}

void func_001975D0();    // 0x001975D0
void func_001AC198(int); // 0x001AC198
void func_001AC398(int); // 0x001AC398
void func_001AC3F0(int); // 0x001AC3F0

// UnkObj194EC0 (0x00194EC0): no RTTI; its layout is the fields these methods use.
struct UnkObj194EC0
{
    char field_0x0[0x2C];
    void *mField2C;        // 0x2C
    char field_0x30[0x48];
    void *mField78;        // 0x78
    void *mField7C;        // 0x7C
    void *mField80;        // 0x80
    void *mField84;        // 0x84

    void Method194EC0();   // 0x00194EC0
};

void UnkObj194EC0::Method194EC0()
{
    MemFree1BD978(mField78);
    MemFree1BD978(mField80);
    MemFree1BD978(mField7C);
    MemFree1BD978(mField84);
    MemFree1BD978(mField2C);
    MemFree1BD978(this);
}

// UnkObj196000 (0x00196000..0x00196030): no RTTI; its layout is the fields these methods use.
struct UnkObj196000
{
    char field_0x0[0x4];
    int mField4;          // 0x4
    int mField8;          // 0x8
    int mFieldC;          // 0xC
    int mField10;         // 0x10
    int mField14;         // 0x14
    char field_0x18[0x4];
    int mField1C;         // 0x1C
    char field_0x20[0x4];
    int mField24;         // 0x24

    int GetField8();      // 0x00196000
    int GetFieldC();      // 0x00196008
    int GetField10();     // 0x00196010
    int GetField14();     // 0x00196018
    int GetField24();     // 0x00196020
    int GetField4();      // 0x00196028
    int GetField1C();     // 0x00196030
};

int UnkObj196000::GetField8()
{
    return mField8;
}

int UnkObj196000::GetFieldC()
{
    return mFieldC;
}

int UnkObj196000::GetField10()
{
    return mField10;
}

int UnkObj196000::GetField14()
{
    return mField14;
}

int UnkObj196000::GetField24()
{
    return mField24;
}

int UnkObj196000::GetField4()
{
    return mField4;
}

int UnkObj196000::GetField1C()
{
    return mField1C;
}

// UnkObj196630 (0x00196630): no RTTI; its layout is the fields these methods use.
struct UnkObj196630
{
    char field_0x0[0x2];
    u16 mField2;         // 0x2

    int Method196630();  // 0x00196630
};

int UnkObj196630::Method196630()
{
    return ((mField2 - 1) * 0xC) + 0x10;
}

// UnkObj1972B0 (0x001972B0..0x001972F8): no RTTI; its layout is the fields these methods use.
struct UnkObj1972B0
{
    char field_0x0[0x8];
    int mField8;         // 0x8

    void Method1972B0(); // 0x001972B0
    void Method1972D8(); // 0x001972D8
    void Method1972F8(); // 0x001972F8
};

void UnkObj1972B0::Method1972B0()
{
    int tmp;

    tmp = mField8;
    if (tmp != 0)
    {
        func_001AC198(tmp);
    }
}

void UnkObj1972B0::Method1972D8()
{
    func_001AC3F0(mField8);
}

void UnkObj1972B0::Method1972F8()
{
    func_001AC398(mField8);
}

// UnkObj1974D8 (0x001974D8): no RTTI; its layout is the fields these methods use.
struct UnkObj1974D8
{
    char field_0x0[0x14];
    u16 mField14;         // 0x14

    void Method1974D8();  // 0x001974D8
};

void UnkObj1974D8::Method1974D8()
{
    u16 tmp;

    tmp = mField14;
    if (tmp & 0x10)
    {
        mField14 = (u16) (tmp | 0x20);
        return;
    }
    func_001975D0();
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_001959B8(int, f32, f32, f32, f32); // 0x001959B8
void func_001973A0(int, f32, f32, f32);      // 0x001973A0
void func_00197468(int, int);                // 0x00197468
int func_001BD558(int, int);                 // 0x001BD558
int MemAlloc1BD958(int);                     // 0x001BD958

int func_00195940(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3)
{
    int temp_v0;

    temp_v0 = MemAlloc1BD958(0x44);
    if (temp_v0 != 0)
    {
        func_001959B8(temp_v0, fparg0, fparg1, fparg2, fparg3);
    }
    return temp_v0;
}

int func_00197318(int arg0, f32 fparg0, f32 fparg1, f32 fparg2)
{
    int temp_v0;

    temp_v0 = func_001BD558(0xA0, 4);
    if (temp_v0 != 0)
    {
        func_001973A0(temp_v0, fparg0, fparg1, fparg2);
        func_00197468(temp_v0, arg0);
    }
    return temp_v0;
}
