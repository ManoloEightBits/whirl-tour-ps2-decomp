#include "common/types.h"

// Functions of 0x00144000..0x00147FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8(); // 0x001974D8
void func_00197510(); // 0x00197510
void func_0019A6F0(); // 0x0019A6F0

void func_00144F18()
{
}

void func_00145010()
{
}

void func_00145018()
{
}

void func_001456E8()
{
    func_001974D8();
}

void func_00145B20()
{
    func_001974D8();
}

void func_00145B40()
{
    func_00197510();
}

void func_00145B60()
{
    func_0019A6F0();
}

void func_001461C0()
{
    func_001974D8();
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_00197AB8(int); // 0x00197AB8

void func_00144F20(int arg0, int arg1)
{
    func_00197AB8(arg1 + 4);
}
