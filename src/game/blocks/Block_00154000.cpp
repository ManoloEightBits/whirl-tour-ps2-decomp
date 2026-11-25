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
