#include "common/types.h"

// Functions of 0x001A8000..0x001ABFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001A6780(); // 0x001A6780
void func_001AB8C8(); // 0x001AB8C8

u32 func_001A9370(int arg0)
{
    return (u32) (arg0 << 0xC) / 48000U;
}

int func_001AB370()
{
    func_001AB8C8();
    return 0;
}

void func_001ABD60()
{
    func_001A6780();
}

int func_001ABE88()
{
    return 0;
}
