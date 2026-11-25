#include "common/types.h"

// Functions of 0x00128000..0x0012BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00154C58();         // 0x00154C58
void func_002318F8(int, int); // 0x002318F8
int func_00231A0C(int);       // 0x00231A0C

void func_001285A8()
{
}

void func_00128CC0(int arg0, int arg1)
{
    func_002318F8(arg0 + 0x24, arg1);
}

void func_00128D38(int arg0, int arg1)
{
    func_002318F8(arg0 + 0xA4, arg1);
}

void func_00128ED8(int arg0, int arg1, int arg2)
{
    if (func_00231A0C(arg2) != 0)
    {
        func_002318F8((arg1 * 0x58) + arg0 + 0xD94, arg2);
    }
}

void func_00129138()
{
}

void func_00129CB8()
{
    func_00154C58();
}
