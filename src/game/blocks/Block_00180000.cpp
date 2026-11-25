#include "common/types.h"

// Functions of 0x00180000..0x00183FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00141148(int, int); // 0x00141148
void func_0019A370();         // 0x0019A370

int func_00180ED8(int arg0)
{
    return arg0 + 0x30;
}

int func_00180EE0(int arg0)
{
    return arg0 + 0x50;
}

void func_00180EE8()
{
}

int func_00183A68()
{
    return 1;
}

int func_00183B80()
{
    func_0019A370();
    return 1;
}

int func_00183C40(int arg0, int arg1)
{
    func_00141148(arg1, arg0);
    return 1;
}

int func_00183C88()
{
    return 1;
}

int func_00183D58()
{
    return 1;
}

int func_00183E88()
{
    return 1;
}
