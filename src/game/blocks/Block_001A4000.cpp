#include "common/types.h"

// Functions of 0x001A4000..0x001A7FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001A4E90()
{
}

void func_001A4E98()
{
}

void func_001A4EA0()
{
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_0019C2E8();     // 0x0019C2E8
void func_001A1070();     // 0x001A1070
extern int data_00265D3C;
extern int data_0026770C;

void func_001A4DA8()
{
    if (data_0026770C != 0)
    {
        func_0019C2E8();
        func_001A1070();
    }
}

void func_001A4E78(int arg0)
{
    data_00265D3C = (arg0 == 0) ? 0 : 3;
}

void func_0019B798(int, int, int, int); // 0x0019B798
void func_001A0C10();    // 0x001A0C10

void func_001A4D78(int arg0, int arg1, int arg2)
{
    func_0019B798(arg0, arg1, arg2, 0x420000);
    func_001A0C10();
    func_001A4DA8();
}

struct UnkGLState
{
    char field_0x0[0x11F9C];
    int mField11F9C; // 0x11F9C
};
extern UnkGLState data_00267140;

void func_001A4930(int arg0)
{
    data_00267140.mField11F9C = arg0 & 0xFF;
}
