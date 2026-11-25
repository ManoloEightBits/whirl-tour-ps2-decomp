#include "common/types.h"

// Functions of 0x001C4000..0x001C7FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001B4390(int, int, int); // 0x001B4390

void func_001C4788(int arg0, int arg1, int arg2)
{
    func_001B4390(arg2, arg0 + 4, arg1 + 4);
}

void func_001C4CE8(int arg0, int arg1, int arg2)
{
    func_001B4390(arg2, arg0 + 0x18, arg1 + 0x18);
}

void func_001C4D18()
{
}
