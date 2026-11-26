#include "common/types.h"
#include "game/GL.h"
#include "game/FEScreen.h"

// Functions of 0x00198000..0x0019BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00197BC8(int);                               // 0x00197BC8
void func_001982D0(int, int);                          // 0x001982D0
void func_00198628(int, int, int, int);                // 0x00198628
void func_00198E08(int, int, int, int, int, int, int); // 0x00198E08
void func_00199738();                                  // 0x00199738
void func_001BD240(int);                               // 0x001BD240
int MemAlloc1BD958(int);                                // 0x001BD958
void MemFree1BD978(void *);                            // 0x001BD978

int func_00198090(int arg0)
{
    int result;

    result = MemAlloc1BD958(0x318);
    if (result != 0)
    {
        func_00197BC8(result);
        func_001982D0(result, arg0);
    }
    return result;
}

void func_00198330(int arg0, int arg1)
{
    if (arg1 != 0)
    {
        func_001BD240(arg0 + 0xC);
    }
}

void func_001983A0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    func_00198E08(arg0 + 0x2C, arg1, arg2, arg3, arg4, arg5, arg6);
}

int func_00198578(int arg0, int arg1, int arg2)
{
    int result;

    result = MemAlloc1BD958(0x14);
    if (result != 0)
    {
        func_00198628(result, arg0, arg1, arg2);
    }
    return result;
}

int func_00198D00(int arg0)
{
    return arg0;
}

int func_00198D08(int arg0)
{
    return arg0 + 0x40;
}

int func_00198D10(int arg0)
{
    return arg0 + 0x80;
}

int func_00198D18(int arg0)
{
    return arg0 + 0xC0;
}

int func_00198D50(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    int result;

    result = MemAlloc1BD958(0x34);
    if (result != 0)
    {
        func_00198E08(result, arg0, arg1, arg2, arg3, arg4, arg5);
    }
    return result;
}

void func_00198DE8(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001990C8()
{
    func_00199738();
}

void func_00199738()
{
}

void func_0019A610()
{
}

void DrawEnd19A6B0()
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void func_00197D98();                                       // 0x00197D98
void func_001A3188(int, int, int, int, int, int, int, int); // 0x001A3188
void func_001A3410(int);                                    // 0x001A3410
void func_001A42F8(int);                                    // 0x001A42F8

// UnkObj1982D0 (0x001982D0): no RTTI; its layout is the fields these methods use.
struct UnkObj1982D0
{
    char field_0x0[0x74];
    int mField74;                // 0x74

    void Method1982D0(int arg1); // 0x001982D0
};

void UnkObj1982D0::Method1982D0(int arg1)
{
    mField74 = arg1;
    func_00197D98();
}

// UnkObj198C78 (0x00198C78): no RTTI; its layout is the fields these methods use.
struct UnkObj198C78
{
    char field_0x0[0x14C];
    int mField14C;         // 0x14C

    void Method198C78();   // 0x00198C78
};

void UnkObj198C78::Method198C78()
{
    glDisable(GL_POLYGON_OFFSET_FILL);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, mField14C);
    func_001A3188(0xDE1, 0, 0, 0, 0, 0, 0x80, 0x80);
    func_001A42F8(0x100);
    func_001A3410(0);
}

// UnkObj198D20 (0x00198D20): no RTTI; its layout is the fields these methods use.
struct UnkObj198D20
{
    char field_0x0[0x14C];
    int mField14C;         // 0x14C

    int GetField14C();     // 0x00198D20
};

int UnkObj198D20::GetField14C()
{
    return mField14C;
}

// UnkObj199C88 (0x00199C88..0x00199D60): no RTTI; its layout is the fields these methods use.
struct UnkObj199C88
{
    u32 mField0;         // 0x0
    char field_0x4[0x4];
    u32 mField8;         // 0x8
    u32 mFieldC;         // 0xC

    void Method199C88(); // 0x00199C88
    void Method199D60(); // 0x00199D60
};

void UnkObj199C88::Method199C88()
{
    u32 tmp;

    tmp = mField8;
    if ((u32) mFieldC < tmp)
    {
        mFieldC = tmp;
    }
    mField8 = (u32) mField0;
}

void UnkObj199C88::Method199D60()
{
    u32 tmp;

    tmp = mField8;
    if ((u32) mFieldC < tmp)
    {
        mFieldC = tmp;
    }
    mField8 = (u32) mField0;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_001A24D0(int, int *); // 0x001A24D0
extern f32 data_002659E0;
extern f32 data_002659E4;
extern int data_002659D0;
extern int data_002B2528;

int func_00198D28()
{
    return data_002659D0;
}

void func_00199458(f32 fparg0, f32 fparg1)
{
    data_002659E0 = fparg0;
    data_002659E4 = fparg1;
}

void func_00199490(f32 fparg0)
{
    data_002659E0 = fparg0;
}

void func_001994A0(f32 fparg0)
{
    data_002659E4 = fparg0;
}

f32 func_001994B0()
{
    return data_002659E0;
}

f32 func_001994C0()
{
    return data_002659E4;
}

void func_001994D0(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3)
{
    u32 temp_v0;

    temp_v0 = ((int) (fparg3 * 128.0f) << 0x18) | ((int) (fparg2 * 128.0f) << 0x10) | ((int) (fparg1 * 128.0f) << 8) | (int) (fparg0 * 128.0f);
    data_002B2528 = (((temp_v0 >> 0x18) - 1) << 0x19) | (((((temp_v0 >> 0x10) - 1) * 2) & 0xFF) << 0x10) | ((((temp_v0 >> 8) - 1) << 9) & 0xFE00) | (((temp_v0 - 1) * 2) & 0xFF);
}

void func_0019A618(int arg0)
{
    int sp0;

    sp0 = arg0;
    func_001A24D0(1, &sp0);
}

// The front end's start-up and shut-down: a memory pool of the given size (func_001996F8 prepares it),
// the four pads (func_001BC2B8(1, n)), their copies at 0x002659B0, a pad of type 2 over all four and
// a 0x101-byte buffer (func_001BC448).
FEPad *func_001BC2B8(int type, int index); // 0x001BC2B8
void func_001BC318(void *pad);             // 0x001BC318
s8 *func_001BC448();                       // 0x001BC448
void func_001BC490(void *buffer);          // 0x001BC490
void func_001996F8(int pool, int size);    // 0x001996F8
extern FEPad *gFEPads2659A0[4];
extern FEPad *data_002659B8;
extern FEPad *data_002659BC;
extern FEPad *data_002659C0;
extern s8 *data_002659C4;
extern int data_002659D8;
extern int data_002659DC;

void func_00198F58(int size)
{
    data_002659DC = size;
    data_002659D8 = MemAlloc1BD958(size);
    func_001996F8(data_002659D8, data_002659DC);
    for (int i = 0; i < 4; i++)
        gFEPads2659A0[i] = func_001BC2B8(1, i);
    gFEPad2659B0 = gFEPads2659A0[0];
    gFEPad2659B4 = gFEPads2659A0[1];
    data_002659B8 = gFEPads2659A0[2];
    data_002659BC = gFEPads2659A0[3];
    data_002659C0 = func_001BC2B8(2, 4);
    data_002659C4 = func_001BC448();
}

void func_00199030()
{
    for (int i = 0; i < 4; i++)
    {
        if (gFEPads2659A0[i] != 0)
            func_001BC318(gFEPads2659A0[i]);
    }
    if (data_002659C0 != 0)
        func_001BC318(data_002659C0);
    func_001BC490(data_002659C4);
    MemFree1BD978((void *)data_002659D8);
    data_002659D8 = 0;
    data_002659DC = 0;
}

void func_001BD260(int);     // 0x001BD260
extern f32 data_002659E8;

void func_001982F0(int arg0, int enable)
{
    if (enable != 0)
    {
        func_001BD240(arg0);
    }
}

void func_00198310(int arg0, int enable)
{
    if (enable != 0)
    {
        func_001BD260(arg0);
    }
}

struct UnkEntry1983C0
{
    int mFlags00;       // 0x00
    char pad04[0x40];
};

struct UnkObj1983C0
{
    char pad00[0xD0];
    UnkEntry1983C0 mEntries[8]; // 0xD0
};

// Clears bit 0 of the flags of eight entries of 0x44 bytes.
void func_001983C0(UnkObj1983C0 *obj)
{
    for (int i = 0; i < 8; i++)
        obj->mEntries[i].mFlags00 &= ~1;
}

void func_00199470(f32 fparg0, f32 fparg1, f32 fparg2)
{
    data_002659E0 = fparg0;
    data_002659E4 = fparg1;
    data_002659E8 = fparg2;
}
