#include "common/types.h"

// Functions of 0x00154000..0x00157FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00126138(int); // 0x00126138
int func_00151D40(int);  // 0x00151D40
void func_00153AD8();    // 0x00153AD8
void func_00155238();    // 0x00155238
void func_00155250();    // 0x00155250
void func_00155280();    // 0x00155280
void func_00156158();    // 0x00156158
int func_00231A0C(int);  // 0x00231A0C

int func_00154F80()
{
    return 0xB;
}

void func_00155030()
{
    func_00155238();
    func_00155250();
    func_00155280();
    func_00153AD8();
    func_00156158();
}

void func_00155A28()
{
    func_00231A0C(func_00151D40(0x82));
}

int func_00156300()
{
    return 0x134C;
}

int func_00156308()
{
    return 0x2490;
}

void func_001566B8(int arg0)
{
    func_00126138(arg0 + 0x65);
}

void func_001566D8(int arg0)
{
    func_00126138(arg0 + 0x3E9);
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_001557C8(u32 arg0)
{
    int var_v1;

    var_v1 = 0;
    switch (arg0)
    {
    case 0:
    case 2:
        var_v1 = 0;
        break;
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        var_v1 = 1;
        break;
    }
    return var_v1;
}

int func_00155B20(int *arg0, int *arg1)
{
    int temp_a0;
    int temp_v1;

    temp_a0 = *arg0;
    temp_v1 = *arg1;
    if (temp_a0 >= temp_v1)
    {
        return (temp_v1 >= temp_a0) ? 0 : -1;
    }
    return 1;
}

extern int * gGameCtx262250;

int func_001552B0()
{
    int temp_v1;
    int var_a1;

    temp_v1 = *gGameCtx262250;
    var_a1 = 0;
    if ((temp_v1 == 2) || (temp_v1 == 0))
    {
        var_a1 = 1;
    }
    return var_a1;
}

int func_001552E0(int arg0)
{
    int temp_v0;
    int var_a1;

    var_a1 = 0;
    if (arg0 != 7)
    {
        temp_v0 = *gGameCtx262250;
        if (temp_v0 != 5)
        {
            var_a1 = temp_v0 != 1;
        }
    }
    return var_a1;
}

int func_00155808()
{
    return (u32) (*gGameCtx262250 - 4) >= 2U;
}

int func_001559D0()
{
    return (u32) (*gGameCtx262250 - 1) >= 2U;
}

int func_001559F0()
{
    int temp_v1;
    int var_a0;

    temp_v1 = *gGameCtx262250;
    var_a0 = 0;
    if ((temp_v1 == 0) || (temp_v1 == 3) || (temp_v1 == 2))
    {
        var_a0 = 1;
    }
    return var_a0;
}

int func_001560C0()
{
    int temp_v1;
    int var_a0;

    temp_v1 = *gGameCtx262250;
    var_a0 = 0;
    if ((temp_v1 == 0) || (temp_v1 == 3))
    {
        var_a0 = 1;
    }
    return var_a0;
}
