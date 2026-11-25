#include "common/types.h"

// Functions of 0x00124000..0x00127FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// UnkObj1272A0 (0x001272A0..0x00127328): no RTTI; its layout is the fields these methods use.
struct UnkObj1272A0
{
    char field_0x0[0x28];
    int mField28;                  // 0x28
    f32 mField2C;                  // 0x2C
    char field_0x30[0xC];
    f32 mField3C;                  // 0x3C

    void Method1272A0(int arg1);   // 0x001272A0
    void Method1272B0(int arg1);   // 0x001272B0
    void SetField2C(f32 fparg0);   // 0x00127320
    void Method127328(f32 fparg0); // 0x00127328
};

void UnkObj1272A0::Method1272A0(int arg1)
{
    mField28 |= arg1;
}

void UnkObj1272A0::Method1272B0(int arg1)
{
    mField28 &= ~arg1;
}

void UnkObj1272A0::SetField2C(f32 fparg0)
{
    mField2C = fparg0;
}

void UnkObj1272A0::Method127328(f32 fparg0)
{
    f32 tmp;

    tmp = fparg0;
    if (tmp < 0.05f)
    {
        tmp = 0.05f;
    }
    mField3C = tmp;
}

// UnkObj127458 (0x00127458): no RTTI; its layout is the fields these methods use.
struct UnkObj127458
{
    char field_0x0[0x6F];
    s8 mField6F;              // 0x6F

    void SetField6F(s8 v); // 0x00127458
};

void UnkObj127458::SetField6F(s8 v)
{
    mField6F = v;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_0012D120();                         // 0x0012D120
void func_0012D248(int, int, int, int, int); // 0x0012D248
int func_00182CF0(int, int, int);            // 0x00182CF0
void func_00182D98(int, int, int, int);      // 0x00182D98
int func_00182E20(int, int, int);            // 0x00182E20
int func_00182E98(int, int, int, int, int);  // 0x00182E98
void func_001832A8(int, int);                // 0x001832A8
int func_00183580(int);                      // 0x00183580
extern int data_0025DC60;
extern int data_0025DC64;

int func_001260A0()
{
    int var_v1;

    var_v1 = 0;
    if (data_0025DC60 != 0)
    {
        var_v1 = func_00183580(data_0025DC60);
    }
    return var_v1;
}

void func_00126138(int arg0)
{
    if (data_0025DC60 != 0)
    {
        func_001832A8(data_0025DC60, arg0);
    }
}

int func_00126168(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182CF0(data_0025DC60, arg0, 0x2710);
    }
    return var_v0;
}

void func_00126198(int arg0, int arg1, int arg2)
{
    if (data_0025DC60 != 0)
    {
        func_00182D98(data_0025DC60, arg0, arg1, arg2);
    }
}

int func_001261D0(int arg0, int arg1)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, arg0, arg1);
    }
    return var_v0;
}

int func_00126250(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xD, arg0);
    }
    return var_v0;
}

int func_00126280(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0, arg0);
    }
    return var_v0;
}

int func_001262B0(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 5, arg0);
    }
    return var_v0;
}

int func_001262E0(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 3, arg0);
    }
    return var_v0;
}

int func_00126310(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xA, arg0);
    }
    return var_v0;
}

int func_00126340(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0x10, arg0);
    }
    return var_v0;
}

int func_00126370(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xC, arg0);
    }
    return var_v0;
}

int func_001263A0(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xB, arg0);
    }
    return var_v0;
}

int func_001263D0(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 8, arg0);
    }
    return var_v0;
}

int func_00126400(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xF, arg0);
    }
    return var_v0;
}

int func_00126430(int arg0, int arg1, int arg2)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E98(data_0025DC60, 8, arg0, arg1, arg2);
    }
    return var_v0;
}

void func_00126620(int arg0, int arg1, int arg2, int arg3)
{
    if (data_0025DC64 == 0)
    {
        data_0025DC64 = func_0012D120();
    }
    func_0012D248(data_0025DC64, arg0, arg1, arg2, arg3);
}

void func_0012D278(int, int);             // 0x0012D278

void func_001266A0(int arg0)
{
    if (data_0025DC64 != 0)
    {
        func_0012D278(data_0025DC64, arg0);
    }
}

