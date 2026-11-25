#include "common/types.h"

// Functions of 0x001A0000..0x001A3FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_0019F370();         // 0x0019F370
void func_001A0210(int, int); // 0x001A0210

void func_001A0400()
{
}

void func_001A0408()
{
}

void func_001A0410()
{
    func_001A0210(0x1A, 0);
    func_001A0210(0x1B, 0);
}

void func_001A0440()
{
    func_001A0210(0x1A, 1);
}

void func_001A3610()
{
}

void func_001A3618()
{
    func_0019F370();
}
