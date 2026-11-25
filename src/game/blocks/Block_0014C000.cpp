#include "common/types.h"

// Functions of 0x0014C000..0x0014FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00126138(int);    // 0x00126138
void func_0014C4E8(int);    // 0x0014C4E8
void func_001974D8();       // 0x001974D8
int func_001BD958(int);     // 0x001BD958
void func_001BD978(void *); // 0x001BD978

void func_0014C198()
{
    func_001974D8();
}

void func_0014C200()
{
}

void func_0014C208(void *arg0)
{
    func_001BD978(arg0);
    func_00126138(0);
}

void func_0014C2B8()
{
    func_001974D8();
}

void func_0014C3B8()
{
}

void func_0014C4D8()
{
}

void func_0014C4E0()
{
}

int func_0014C908(int arg0)
{
    return arg0 + 4;
}

int func_0014C920()
{
    return 0xA;
}

int func_0014C9C0()
{
    int result;

    result = func_001BD958(0x98);
    if (result != 0)
    {
        func_0014C4E8(result);
    }
    return result;
}

void func_0014CAC8(void *arg0)
{
    func_001BD978(arg0);
}

int func_0014CAE8(int arg0)
{
    return arg0 + 0xC;
}

void func_0014E990(void *arg0)
{
    func_001BD978(arg0);
}

void func_0014E9B0()
{
    func_001974D8();
}

void func_0014EC80()
{
    func_001974D8();
}
