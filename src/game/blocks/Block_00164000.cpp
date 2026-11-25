#include "common/types.h"

// Functions of 0x00164000..0x00167FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00164B40(); // 0x00164B40
void func_00164CC8(); // 0x00164CC8
void func_00165430(); // 0x00165430

int func_00164F88(int arg0)
{
    return arg0 + 0xB0;
}

void func_001650C0()
{
    func_00164CC8();
}

void func_001650E0()
{
    func_00164B40();
}

void func_00165E58()
{
    func_00165430();
}

void func_00167638()
{
}
