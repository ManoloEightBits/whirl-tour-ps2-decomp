#include "common/types.h"

// Functions of 0x00114000..0x00117FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00115D70(int, int); // 0x00115D70

int func_00115E38()
{
    return 0;
}

int func_00115E40()
{
    return 0;
}

void func_001161E0()
{
    func_00115D70(1, 0xFFFF);
}

void func_00116200()
{
    func_00115D70(0, 0xFFFF);
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_00115908(f32);  // 0x00115908
void func_00115BB0();     // 0x00115BB0
extern f32 data_00259F40;

void func_00115F58()
{
    func_00115BB0();
    func_00115908(data_00259F40);
}
