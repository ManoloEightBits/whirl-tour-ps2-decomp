#include "common/types.h"

// Functions of 0x00194000..0x00197FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8();       // 0x001974D8
void func_001BD978(void *); // 0x001BD978

void func_001957F0()
{
    func_001974D8();
}

void func_00195A10(void *arg0)
{
    func_001BD978(arg0);
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
    func_001BD978(arg0);
}

void func_001965B0()
{
}

void func_001965F8(void *arg0)
{
    func_001BD978(arg0);
}

int func_00196648(int arg0)
{
    return ((arg0 - 1) * 0xC) + 0x10;
}

int func_00196D80()
{
    return 0;
}
