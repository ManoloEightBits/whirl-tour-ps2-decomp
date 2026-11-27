#include "common/types.h"

// Functions of 0x0015C000..0x0015FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_0015F318(); // 0x0015F318
void func_0015F3C8(); // 0x0015F3C8
void func_0015F458(); // 0x0015F458

void func_0015E958()
{
}

void func_0015E960()
{
}

void func_0015F2F8()
{
    func_0015F318();
}

void func_0015F3A8()
{
    func_0015F3C8();
}

void func_0015F438()
{
    func_0015F458();
}

int func_0015F578()
{
    return 0;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

struct UnkObj15EFF8
{
    char field_0x0[0x20];
    int mField20; // 0x20

    void SetFlag15EFF8(); // 0x0015EFF8
};

void UnkObj15EFF8::SetFlag15EFF8()
{
    mField20 |= 0x20000000;
}
