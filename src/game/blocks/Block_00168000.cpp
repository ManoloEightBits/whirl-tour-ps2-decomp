#include "common/types.h"
#include "common/libc.h"
#include "game/GL.h"

// Functions of 0x00168000..0x0016BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00168338(); // 0x00168338

void func_00168318()
{
    func_00168338();
}

void func_00168B38();                   // 0x00168B38
void func_001A4930(int);                // 0x001A4930

// UnkObj168A20 (0x00168A20..0x00168A40): no RTTI; its layout is the fields these methods use.
struct UnkObj168A20
{
    char field_0x0[0x4];
    f32 mField4;                   // 0x4
    char field_0x8[0x4];
    int mFieldC;                   // 0xC
    f32 mField10;                  // 0x10
    char field_0x14[0xC];
    f32 *mField20;                 // 0x20
    u8 *mField24;                  // 0x24
    f32 *mField28;                 // 0x28

    void Method168A20(f32 fparg0); // 0x00168A20
    void Method168A40();           // 0x00168A40
};

void UnkObj168A20::Method168A20(f32 fparg0)
{
    mField4 = (f32) (mField4 + fparg0);
    mField10 = (f32) (mField10 + fparg0);
}

void UnkObj168A20::Method168A40()
{
    if (mFieldC >= 2)
    {
        func_00168B38();
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0xCDEE3B39);
        func_001A4930(0);
        glVertexPointer(3, GL_FLOAT, 0, mField20);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, mField24);
        glTexCoordPointer(2, GL_FLOAT, 0, mField28);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, mFieldC * 2);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        func_001A4930(1);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    }
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int ArrayCreate1BB0E0(int); // 0x001BB0E0

int *func_00168BE0(int *arg0)
{
    *arg0 = ArrayCreate1BB0E0(4);
    return arg0;
}

void func_001BB250(int, int *); // 0x001BB250
extern int * data_002624B0;

void func_00168DF0(int arg0)
{
    int sp0;

    sp0 = arg0;
    func_001BB250(*data_002624B0, &sp0);
}

void *func_001BD558(int, int); // 0x001BD558

struct UnkObj168900
{
    f32 mField00;  // 0x00
    int mField04;  // 0x04
    int mField08;  // 0x08
    int mField0C;  // 0x0C
    int mField10;  // 0x10
    f32 mField14;  // 0x14
    int mField18;  // 0x18
    void *mField1C; // 0x1C
    void *mField20; // 0x20
    void *mField24; // 0x24
    void *mField28; // 0x28
};

UnkObj168900 *func_00168900(UnkObj168900 *arg0, int arg1, f32 fparg0)
{
    arg0->mField08 = arg1;
    int sz = arg1 * 8;
    arg0->mField18 = arg1;
    arg0->mField04 = 0;
    arg0->mField0C = 0;
    arg0->mField10 = 0;
    arg0->mField00 = fparg0;
    arg0->mField14 = 0.1f;
    arg0->mField20 = func_001BD558(arg1 * 0x18, 4);
    arg0->mField24 = func_001BD558(sz, 4);
    arg0->mField28 = func_001BD558(arg1 * 0x10, 4);
    arg0->mField1C = func_001BD558(sz, 4);
    memset(arg0->mField24, 0, sz);
    func_00168DF0((int)arg0);
    return arg0;
}
