#include "common/types.h"

// Functions of 0x00190000..0x00193FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

int func_00190D88();        // 0x00190D88
void func_001BD978(void *); // 0x001BD978

int func_00190BB8(int arg0)
{
    return arg0 + 0x1900;
}

int func_00190D90()
{
    return func_00190D88() == 0;
}

int func_00190DB8(int arg0)
{
    return arg0 + 0xC;
}

int func_00190DC0(int arg0)
{
    return arg0 + 4;
}

void func_00191768(void *arg0)
{
    func_001BD978(arg0);
}

void func_00191E40(void *arg0)
{
    func_001BD978(arg0);
}
