#include "common/types.h"
#include "game/GL.h"

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

union GLVal5F4
{
    int i;
    f32 f;
};

struct UnkGLState
{
    char field_0x0[0x70];
    f32 mField70;     // 0x70: GL_LIGHT_MODEL_AMBIENT r
    f32 mField74;     // 0x74: GL_LIGHT_MODEL_AMBIENT g
    f32 mField78;     // 0x78: GL_LIGHT_MODEL_AMBIENT b
    f32 mField7C;     // 0x7C: GL_LIGHT_MODEL_AMBIENT a
    char field_0x80[0x568];
    f32 mField5E8;    // 0x5E8
    f32 mField5EC;    // 0x5EC
    f32 mField5F0;    // 0x5F0
    GLVal5F4 mField5F4; // 0x5F4
    GLVal5F4 mField5F8; // 0x5F8
    GLVal5F4 mField5FC; // 0x5FC
    GLVal5F4 mField600; // 0x600
    s8 mField604;     // 0x604: clear color r
    s8 mField605;     // 0x605: clear color g
    s8 mField606;     // 0x606: clear color b
    s8 mField607;     // 0x607: clear color a
    char field_0x608[0x4];
    const void *mField60C; // 0x60C: vertex pointer
    const void *mField610; // 0x610: texcoord pointer
    const void *mField614; // 0x614: color pointer
    int mField618;         // 0x618: vertex size
    int mField61C;         // 0x61C: texcoord size
    int mField620;         // 0x620: color size
    char field_0x624[0x11978];
    int mField11F9C;  // 0x11F9C
    unsigned int mField11FA0; // 0x11FA0
    int mField11FA4;  // 0x11FA4
    int mField11FA8;  // 0x11FA8
    char field_0x11FAC[0x8];
    int mField11FB4;  // 0x11FB4: GL_TEXTURE_COORD_ARRAY
    int mField11FB8;  // 0x11FB8: GL_COLOR_ARRAY
    int mField11FBC;  // 0x11FBC: GL_VERTEX_ARRAY
    int mField11FC0;  // 0x11FC0: viewport x
    int mField11FC4;  // 0x11FC4: viewport y
    int mField11FC8;  // 0x11FC8: viewport w
    int mField11FCC;  // 0x11FCC: viewport h
};
extern UnkGLState data_00267140;

void func_001A4930(int arg0)
{
    data_00267140.mField11F9C = arg0 & 0xFF;
}

void glTexCoord3f(f32 s, f32 t, f32 r)
{
    data_00267140.mField5E8 = s;
    data_00267140.mField5F0 = r;
    data_00267140.mField5EC = t;
    *(u32 *)&data_00267140.mField5E8 &= 0xFFFFFFFEU;
}

void glTexCoord2fv(const f32 *v)
{
    f32 s = v[0];
    f32 t = v[1];
    data_00267140.mField5E8 = s;
    data_00267140.mField5F0 = 1.0f;
    data_00267140.mField5EC = t;
    *(u32 *)&data_00267140.mField5E8 &= 0xFFFFFFFEU;
}

void glTexCoord2f(f32 s, f32 t)
{
    data_00267140.mField5E8 = s;
    *(u32 *)&data_00267140.mField5E8 &= 0xFFFFFFFEU;
    data_00267140.mField5EC = t;
    data_00267140.mField5F0 = 1.0f;
}

void glColor3f(f32 r, f32 g, f32 b)
{
    data_00267140.mField5F4.i = (int)(r * 128.0f);
    data_00267140.mField5F8.i = (int)(g * 128.0f);
    data_00267140.mField5FC.i = (int)(b * 128.0f);
    data_00267140.mField600.i = 0x80;
}

void glColor4f(f32 r, f32 g, f32 b, f32 a)
{
    data_00267140.mField5F4.i = (int)(r * 128.0f);
    data_00267140.mField5F8.i = (int)(g * 128.0f);
    data_00267140.mField5FC.i = (int)(b * 128.0f);
    data_00267140.mField600.i = (int)(a * 128.0f);
}

void glTexCoordPointer(int size, unsigned int type, int stride, const void *ptr)
{
    data_00267140.mField61C = size;
    data_00267140.mField610 = ptr;
}

void glVertexPointer(int size, unsigned int type, int stride, const void *ptr)
{
    data_00267140.mField618 = size;
    data_00267140.mField60C = ptr;
}

void glColorPointer(int size, unsigned int type, int stride, const void *ptr)
{
    data_00267140.mField620 = size;
    data_00267140.mField614 = ptr;
}

void glEnableClientState(unsigned int array)
{
    switch (array)
    {
    case GL_TEXTURE_COORD_ARRAY:
        data_00267140.mField11FB4 = 1;
        return;
    case GL_COLOR_ARRAY:
        data_00267140.mField11FB8 = 1;
        return;
    case GL_VERTEX_ARRAY:
        data_00267140.mField11FBC = 1;
        return;
    }
}

void glDisableClientState(unsigned int array)
{
    switch (array)
    {
    case GL_TEXTURE_COORD_ARRAY:
        data_00267140.mField11FB4 = 0;
        return;
    case GL_COLOR_ARRAY:
        data_00267140.mField11FB8 = 0;
        return;
    case GL_VERTEX_ARRAY:
        data_00267140.mField11FBC = 0;
        return;
    }
}

void glBlendFunc(unsigned int sfactor, unsigned int dfactor)
{
    data_00267140.mField11FA0 = dfactor;
    if (sfactor == GL_SRC_ALPHA && dfactor == GL_ONE_MINUS_SRC_ALPHA)
    {
        data_00267140.mField11FA8 = 0;
    }
    else if (sfactor == 1 && dfactor == 1)
    {
        data_00267140.mField11FA8 = dfactor;
    }
    else if (sfactor <= 1 && dfactor == 0x301)
    {
        data_00267140.mField11FA8 = 2;
    }
    else
    {
        data_00267140.mField11FA8 = 0;
    }
}

void glColor3fv(const f32 *v)
{
    f32 r = v[0], g = v[1], b = v[2];
    data_00267140.mField5F4.i = (int)(r * 128.0f);
    data_00267140.mField5F8.i = (int)(g * 128.0f);
    data_00267140.mField5FC.i = (int)(b * 128.0f);
    data_00267140.mField600.i = 0x80;
}

void glColor4fv(const f32 *v)
{
    f32 r = v[0], g = v[1], b = v[2], a = v[3];
    data_00267140.mField5F4.i = (int)(r * 128.0f);
    data_00267140.mField5F8.i = (int)(g * 128.0f);
    data_00267140.mField5FC.i = (int)(b * 128.0f);
    data_00267140.mField600.i = (int)(a * 128.0f);
}

void glColor3i(int r, int g, int b)
{
    data_00267140.mField5F4.i = r;
    data_00267140.mField5F8.i = g;
    data_00267140.mField5FC.i = b;
    data_00267140.mField600.i = 0x80;
}

void glColor4i(int r, int g, int b, int a)
{
    data_00267140.mField5F4.i = r;
    data_00267140.mField5F8.i = g;
    data_00267140.mField5FC.i = b;
    data_00267140.mField600.i = a;
}

void glColor4ub(u8 r, u8 g, u8 b, u8 a)
{
    data_00267140.mField5F4.i = r;
    data_00267140.mField5F8.i = g;
    data_00267140.mField5FC.i = b;
    data_00267140.mField600.i = a;
}

void glColor4ubv(const u8 *v)
{
    u8 r = v[0], g = v[1], b = v[2], a = v[3];
    data_00267140.mField5F4.i = r;
    data_00267140.mField5F8.i = g;
    data_00267140.mField5FC.i = b;
    data_00267140.mField600.i = a;
}

void glColor4iv(const int *v)
{
    int r = v[0], g = v[1], b = v[2], a = v[3];
    data_00267140.mField5F4.i = r;
    data_00267140.mField5F8.i = g;
    data_00267140.mField5FC.i = b;
    data_00267140.mField600.i = a;
}

void glLightModelfv(unsigned int pname, const f32 *params)
{
    if (pname == GL_LIGHT_MODEL_AMBIENT)
    {
        data_00267140.mField70 = params[0] * 128.0f;
        data_00267140.mField74 = params[1] * 128.0f;
        data_00267140.mField78 = params[2] * 128.0f;
        data_00267140.mField7C = params[3] * 128.0f;
    }
}

void glClearColor(f32 r, f32 g, f32 b, f32 a)
{
    data_00267140.mField604 = (s8)(int)(r * 128.0f);
    data_00267140.mField605 = (s8)(int)(g * 128.0f);
    data_00267140.mField606 = (s8)(int)(b * 128.0f);
    data_00267140.mField607 = (s8)(int)(a * 128.0f);
}

void func_001A4690(f32 x, f32 y, f32 z)
{
    data_00267140.mField5F4.f = x;
    data_00267140.mField5F8.f = y;
    data_00267140.mField5FC.f = z;
    data_00267140.mField600.f = 1.0f;
}

void func_001A46B8(const f32 *v)
{
    f32 x = v[0], y = v[1], z = v[2];
    data_00267140.mField5F4.f = x;
    data_00267140.mField5F8.f = y;
    data_00267140.mField5FC.f = z;
    data_00267140.mField600.f = 1.0f;
}

void glGetIntegerv(unsigned int pname, int *params)
{
    if (pname == GL_VIEWPORT)
    {
        *params++ = data_00267140.mField11FC0;
        *params++ = data_00267140.mField11FC4;
        *params++ = data_00267140.mField11FC8;
        *params = data_00267140.mField11FCC;
    }
}
