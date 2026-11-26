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

extern const f32 data_002670C0[16];
extern int data_002B3608;

void glLoadIdentity(void)
{
    glLoadMatrixf(data_002670C0);
    data_002B3608 = 1;
}

void func_001B3EC8(Mat4x4f *dst, const Mat4x4f *a, const Mat4x4f *b); // 0x001B3EC8

struct UnkGLState1A0
{
    char field_0x0[0x5C0];
    int mField5C0;      // 0x5C0: matrix mode (GL_MODELVIEW / GL_PROJECTION)
    Mat4x4f *mField5C4; // 0x5C4: projection stack top
    Mat4x4f *mField5C8; // 0x5C8: modelview stack top
    int mField5CC;      // 0x5CC
    int mField5D0;      // 0x5D0
    char field_0x5D4[0x8];
    void *mField5DC;    // 0x5DC
    int mField5E0;      // 0x5E0
    int mField5E4;      // 0x5E4: vertex count
    f32 mField5E8;      // 0x5E8: texcoord s
    f32 mField5EC;      // 0x5EC: texcoord t
    f32 mField5F0;      // 0x5F0: texcoord r
    int mField5F4;      // 0x5F4: color r
    int mField5F8;      // 0x5F8: color g
    int mField5FC;      // 0x5FC: color b
    int mField600;      // 0x600: color a
    int mField604;      // 0x604
    unsigned int mField608; // 0x608: primitive mode
    char field_0x60C[0x11964];
    int mField11F70;    // 0x11F70: GL_FOG
    int mField11F74;    // 0x11F74: GL_TEXTURE_2D
    int mField11F78;    // 0x11F78: GL_ALPHA_TEST
    int mField11F7C;    // 0x11F7C: GL_DEPTH_TEST
    int mField11F80;    // 0x11F80: GL_BLEND
    int mField11F84;    // 0x11F84: GL_SCISSOR_TEST
    int mField11F88;    // 0x11F88: GL_POLYGON_OFFSET_FILL
    int mField11F8C;    // 0x11F8C: GL_LIGHTING
    int mField11F90;    // 0x11F90: GL_LIGHT0
    int mField11F94;    // 0x11F94: GL_LIGHT1
    int mField11F98;    // 0x11F98: GL_LIGHT2
    char field_0x11F9C[0x24];
    int mField11FC0;    // 0x11FC0: viewport x
    int mField11FC4;    // 0x11FC4: viewport y
    int mField11FC8;    // 0x11FC8: viewport w
    int mField11FCC;    // 0x11FCC: viewport h
    int mField11FD0;    // 0x11FD0: scissor x
    int mField11FD4;    // 0x11FD4: scissor y
    int mField11FD8;    // 0x11FD8: scissor w
    int mField11FDC;    // 0x11FDC: scissor h
};
extern UnkGLState1A0 data_00267140;

struct GLVertex
{
    f32 x, y, z;   // 0x00
    int mField0C;  // 0x0C
    f32 s, t, r;   // 0x10
    int mField1C;  // 0x1C
    int mField20;  // 0x20
    int mField24;  // 0x24
    int mField28;  // 0x28
    int mField2C;  // 0x2C
};

struct UnkGLVertBuf
{
    char field_0x0[0x8];
    GLVertex *mPtr08; // 0x08
};
extern UnkGLVertBuf data_002670A0;

void glScalef(f32 x, f32 y, f32 z)
{
    Mat4x4f m;
    do { m.row[0].x = x; m.row[0].y = 0.0f; m.row[0].z = 0.0f; m.row[0].w = 0.0f; } while (0);
    do { m.row[1].x = 0.0f; m.row[1].y = y; m.row[1].z = 0.0f; m.row[1].w = 0.0f; } while (0);
    do { m.row[2].x = 0.0f; m.row[2].y = 0.0f; m.row[2].z = z; m.row[2].w = 0.0f; } while (0);
    do { m.row[3].x = 0.0f; m.row[3].y = 0.0f; m.row[3].z = 0.0f; m.row[3].w = 1.0f; } while (0);
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
            func_001B3EC8(data_00267140.mField5C4, &m, data_00267140.mField5C4);
    }
    else
    {
        func_001B3EC8(data_00267140.mField5C8, &m, data_00267140.mField5C8);
    }
    data_002B3608 = 1;
}

void glVertex3fv(const f32 *v)
{
    GLVertex *dst = data_002670A0.mPtr08;
    data_002670A0.mPtr08 = dst + 1;
    dst->x = v[0];
    dst->y = v[1];
    dst->z = v[2];
    dst->s = data_00267140.mField5E8;
    dst->t = data_00267140.mField5EC;
    dst->r = 1.0f;
    dst->mField20 = data_00267140.mField5F4;
    dst->mField24 = data_00267140.mField5F8;
    dst->mField28 = data_00267140.mField5FC;
    dst->mField2C = data_00267140.mField600;
    dst->mField0C = 0;
    data_00267140.mField5E4++;
}

void glPopMatrix(void)
{
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
            data_00267140.mField5C4--;
    }
    else
    {
        data_00267140.mField5C8--;
    }
    data_002B3608 = 1;
}

void glBegin(unsigned int mode)
{
    data_00267140.mField5D0 = 1;
    GLVertex *p = (GLVertex *)((char *)data_002670A0.mPtr08 + 0x10);
    data_00267140.mField608 = mode;
    data_002670A0.mPtr08 = p;
    data_00267140.mField5DC = p;
    data_00267140.mField5E4 = 0;
}

void glVertex3f(f32 x, f32 y, f32 z)
{
    GLVertex *dst = data_002670A0.mPtr08;
    data_002670A0.mPtr08 = dst + 1;
    dst->x = x;
    dst->y = y;
    dst->z = z;
    dst->s = data_00267140.mField5E8;
    dst->t = data_00267140.mField5EC;
    dst->r = 1.0f;
    dst->mField20 = data_00267140.mField5F4;
    dst->mField24 = data_00267140.mField5F8;
    dst->mField28 = data_00267140.mField5FC;
    dst->mField2C = data_00267140.mField600;
    dst->mField0C = 0;
    data_00267140.mField5E4++;
}

void glMultMatrixf(const f32 *m)
{
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
            func_001B3EC8(data_00267140.mField5C4, (const Mat4x4f *)m, data_00267140.mField5C4);
    }
    else
    {
        func_001B3EC8(data_00267140.mField5C8, (const Mat4x4f *)m, data_00267140.mField5C8);
    }
    data_002B3608 = 1;
}

void func_001A1070(); // 0x001A1070
void func_001A4AF0(int, int, int, int); // 0x001A4AF0
f32 Sin1B1910(f32);  // 0x001B1910
f32 Cos1B19E8(f32);  // 0x001B19E8
void func_001B3B48(Mat4x4f *dst, const f32 *q); // 0x001B3B48

void glLoadMatrixf(const f32 *m)
{
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
            *data_00267140.mField5C4 = *(const Mat4x4f *)m;
    }
    else
    {
        *data_00267140.mField5C8 = *(const Mat4x4f *)m;
    }
    data_002B3608 = 1;
}

void glPushMatrix(void)
{
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
        {
            Mat4x4f *top = data_00267140.mField5C4;
            data_00267140.mField5C4 = top + 1;
            top[1] = top[0];
        }
    }
    else
    {
        Mat4x4f *top = data_00267140.mField5C8;
        data_00267140.mField5C8 = top + 1;
        top[1] = top[0];
    }
    data_002B3608 = 1;
}

void glTranslatef(f32 x, f32 y, f32 z)
{
    Mat4x4f m;
    do { m.row[0].x = 1.0f; m.row[0].y = 0.0f; m.row[0].z = 0.0f; m.row[0].w = 0.0f; } while (0);
    do { m.row[1].x = 0.0f; m.row[1].y = 1.0f; m.row[1].z = 0.0f; m.row[1].w = 0.0f; } while (0);
    do { m.row[2].x = 0.0f; m.row[2].y = 0.0f; m.row[2].z = 1.0f; m.row[2].w = 0.0f; } while (0);
    do { m.row[3].x = x; m.row[3].y = y; m.row[3].z = z; m.row[3].w = 1.0f; } while (0);
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
            func_001B3EC8(data_00267140.mField5C4, &m, data_00267140.mField5C4);
    }
    else
    {
        func_001B3EC8(data_00267140.mField5C8, &m, data_00267140.mField5C8);
    }
    data_002B3608 = 1;
}

#ifdef NON_MATCHING
// 2 of 17 instructions differ: mField11F84 gets $t0 instead of $v1.
void glScissor(int x, int y, int width, int height)
{
    data_00267140.mField11FD0 = x;
    data_00267140.mField11FD4 = y;
    data_00267140.mField11FD8 = width;
    data_00267140.mField11FDC = height;
    if (data_00267140.mField11F84 != 0)
        func_001A4AF0(x, y, width, height);
}
#endif

void glViewport(int x, int y, int width, int height)
{
    data_00267140.mField11FC0 = x;
    data_00267140.mField11FC4 = y;
    data_00267140.mField11FC8 = width;
    data_00267140.mField11FCC = height;
    func_001A1070();
    data_002B3608 = 1;
}

void glEnable(unsigned int cap)
{
    switch (cap)
    {
    case GL_TEXTURE_2D:
        data_00267140.mField11F74 = 1;
        return;
    case GL_DEPTH_TEST:
        data_00267140.mField11F7C = 1;
        break;
    case GL_BLEND:
        data_00267140.mField11F80 = 1;
        break;
    case GL_ALPHA_TEST:
        data_00267140.mField11F78 = 1;
        break;
    case GL_SCISSOR_TEST:
        data_00267140.mField11F84 = 1;
        func_001A4AF0(data_00267140.mField11FD0, data_00267140.mField11FD4,
                      data_00267140.mField11FD8, data_00267140.mField11FDC);
        break;
    case GL_POLYGON_OFFSET_FILL:
        data_00267140.mField11F88 = 1;
        break;
    case GL_FOG:
        data_00267140.mField11F70 = 1;
        break;
    case GL_LIGHTING:
        data_00267140.mField11F8C = 1;
        break;
    case GL_LIGHT0:
        data_00267140.mField11F90 = 1;
        break;
    case GL_LIGHT1:
        data_00267140.mField11F94 = 1;
        break;
    case GL_LIGHT2:
        data_00267140.mField11F98 = 1;
        break;
    }
}

void glDisable(unsigned int cap)
{
    switch (cap)
    {
    case GL_TEXTURE_2D:
        data_00267140.mField11F74 = 0;
        return;
    case GL_DEPTH_TEST:
        data_00267140.mField11F7C = 0;
        break;
    case GL_BLEND:
        data_00267140.mField11F80 = 0;
        break;
    case GL_ALPHA_TEST:
        data_00267140.mField11F78 = 0;
        break;
    case GL_SCISSOR_TEST:
        data_00267140.mField11F84 = 0;
        func_001A4AF0(data_00267140.mField11FC0, data_00267140.mField11FC4,
                      data_00267140.mField11FC8, data_00267140.mField11FCC);
        break;
    case GL_POLYGON_OFFSET_FILL:
        data_00267140.mField11F88 = 0;
        break;
    case GL_FOG:
        data_00267140.mField11F70 = 0;
        break;
    case GL_LIGHTING:
        data_00267140.mField11F8C = 0;
        break;
    case GL_LIGHT0:
        data_00267140.mField11F90 = 0;
        break;
    case GL_LIGHT1:
        data_00267140.mField11F94 = 0;
        break;
    case GL_LIGHT2:
        data_00267140.mField11F98 = 0;
        break;
    }
}

#ifdef NON_MATCHING
// 57 of 59 instructions differ: scheduling/register order of angle, x, y, z and quaternion stores.
void glRotatef(f32 angle, f32 x, f32 y, f32 z)
{
    f32 q[4];
    Mat4x4f m;
    f32 half = -angle * 0.008726647f;
    f32 s = Sin1B1910(half);
    q[0] = x * s;
    q[1] = y * s;
    q[2] = z * s;
    q[3] = Cos1B19E8(half);
    func_001B3B48(&m, q);
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
            func_001B3EC8(data_00267140.mField5C4, &m, data_00267140.mField5C4);
    }
    else
    {
        func_001B3EC8(data_00267140.mField5C8, &m, data_00267140.mField5C8);
    }
    data_002B3608 = 1;
}
#endif

void glOrtho(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar)
{
    Mat4x4f m;
    do { m.row[0].x = 2.0f / (right - left); m.row[0].y = 0.0f; m.row[0].z = 0.0f; m.row[0].w = 0.0f; } while (0);
    do { m.row[1].x = 0.0f; m.row[1].y = 2.0f / (top - bottom); m.row[1].z = 0.0f; m.row[1].w = 0.0f; } while (0);
    do { m.row[2].x = 0.0f; m.row[2].y = 0.0f; m.row[2].z = -2.0f / (zFar - zNear); m.row[2].w = 0.0f; } while (0);
    do {
        m.row[3].x = -(right + left) / (right - left);
        m.row[3].y = -(top + bottom) / (top - bottom);
        m.row[3].z = (zFar + zNear) / (zFar - zNear);
        m.row[3].w = 1.0f;
    } while (0);
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
            func_001B3EC8(data_00267140.mField5C4, &m, data_00267140.mField5C4);
    }
    else
    {
        func_001B3EC8(data_00267140.mField5C8, &m, data_00267140.mField5C8);
    }
    data_002B3608 = 1;
}

#ifdef NON_MATCHING
// 52 of 64 instructions differ: subexpression scheduling for invDz/invDx/invDy.
void glFrustum(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar)
{
    Mat4x4f m;
    f32 invDz = 1.0f / (zFar - zNear);
    f32 invDx = 1.0f / (right - left);
    f32 invDy = 1.0f / (top - bottom);
    f32 twoNear = 2.0f * zNear;
    m.row[0].x = twoNear * invDx;
    m.row[0].y = 0.0f;
    m.row[0].z = (right + left) * invDx;
    m.row[0].w = 0.0f;
    m.row[1].x = 0.0f;
    m.row[1].y = twoNear * invDy;
    m.row[1].z = (top + bottom) * invDy;
    m.row[1].w = 0.0f;
    m.row[2].x = 0.0f;
    m.row[2].y = 0.0f;
    m.row[2].z = -(zFar + zNear) * invDz;
    m.row[2].w = twoNear * -(zFar + zNear) * invDz;
    m.row[3].x = 0.0f;
    m.row[3].y = 0.0f;
    m.row[3].z = -1.0f;
    m.row[3].w = 0.0f;
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
            func_001B3EC8(data_00267140.mField5C4, &m, data_00267140.mField5C4);
    }
    else
    {
        func_001B3EC8(data_00267140.mField5C8, &m, data_00267140.mField5C8);
    }
    data_002B3608 = 1;
}
#endif

void gluPerspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar)
{
    Mat4x4f m;
    f32 half = fovy * 0.008726647f;
    f32 cot = Cos1B19E8(half) / Sin1B1910(half);
    f32 invDz = 1.0f / (zNear - zFar);
    m.row[0].x = cot / aspect;
    m.row[0].y = 0.0f;
    m.row[0].z = 0.0f;
    m.row[0].w = 0.0f;
    m.row[1].x = 0.0f;
    m.row[1].y = -cot;
    m.row[1].z = 0.0f;
    m.row[1].w = 0.0f;
    m.row[2].x = 0.0f;
    m.row[2].y = 0.0f;
    m.row[2].z = -(zNear + zFar) * invDz;
    m.row[2].w = 1.0f;
    m.row[3].x = 0.0f;
    m.row[3].y = 0.0f;
    m.row[3].z = 2.0f * zNear * zFar * invDz;
    m.row[3].w = 0.0f;
    if (data_00267140.mField5C0 != GL_MODELVIEW)
    {
        if (data_00267140.mField5C0 == GL_PROJECTION)
            func_001B3EC8(data_00267140.mField5C4, &m, data_00267140.mField5C4);
    }
    else
    {
        func_001B3EC8(data_00267140.mField5C8, &m, data_00267140.mField5C8);
    }
    data_002B3608 = 1;
}

extern f32 data_00266000[];
void func_0019CBC8(int, int); // 0x0019CBC8

void func_001A02E8(int arg0, const f32 *arg1, int arg2)
{
    glLoadMatrixf(data_00266000);
    glMultMatrixf(arg1);
    func_0019CBC8(arg0, arg2);
}
