#include "common/types.h"
#include "game/GL.h"

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

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_0019DD98(int, int, int, int, int); // 0x0019DD98

void func_001A0640(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    func_0019DD98(arg0, arg1, arg4, arg2, arg3);
}

void func_001A0670(int arg0, int arg1, int arg2, int arg3, int arg4)
{
    func_0019DD98(arg0, arg1, arg4, arg2, arg3);
}

extern unsigned int gMatrixMode267700; // the stack glPushMatrix/glPopMatrix work on

void glMatrixMode(unsigned int mode)
{
    gMatrixMode267700 = mode;
}
