#include "common/types.h"

// Functions of 0x00150000..0x00153FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8();       // 0x001974D8
void func_001BD978(void *); // 0x001BD978

void func_00151608(void *arg0)
{
    func_001BD978(arg0);
}

void func_00151760()
{
}

void func_001519E0()
{
}

void func_001519E8()
{
}

void func_001519F0()
{
}

void func_001519F8()
{
}

void func_00151A00()
{
}

void func_00151A08()
{
}

void func_00151A10()
{
}

void func_00151C28()
{
}

void func_00151CB8()
{
    func_001974D8();
}
