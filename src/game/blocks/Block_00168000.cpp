#include "common/types.h"
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
