#include "common/types.h"

// Functions of 0x001C4000..0x001C7FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001B4390(int, int, int); // 0x001B4390

// A size in bytes for each type 0..13 (8 for any other). The function list splits it after each
// `jr $ra`; 0x001C4084..0x001C40AC are its cases.
int func_001C4058(int type)
{
    switch (type)
    {
    case 0:
    case 6:
    case 7:
    default:
        return 8;
    case 1:
    case 4:
    case 12:
        return 16;
    case 2:
        return 20;
    case 3:
    case 10:
        return 32;
    case 5:
    case 8:
    case 13:
        return 40;
    case 9:
        return 52;
    case 11:
        return 12;
    }
}

void func_001C4788(int arg0, int arg1, int arg2)
{
    func_001B4390(arg2, arg0 + 4, arg1 + 4);
}

void func_001C4CE8(int arg0, int arg1, int arg2)
{
    func_001B4390(arg2, arg0 + 0x18, arg1 + 0x18);
}

void func_001C4D18()
{
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_001C5070(int (*arg0)(int, int *, int), int arg1)
{
    int sp0;

    arg0(arg1, &sp0, 4);
    return sp0;
}

// out[i] = scale * in[i] for nine floats (a 3x3 matrix).
void ScaleMat3x3_1C5EF8(f32 *out, f32 *in, f32 scale)
{
    for (int i = 0; i < 9; i++)
        out[i] = scale * in[i];
}

void MulMat3x3Vec3f1C5D50(f32 *m, f32 *v, f32 *out)
{
    out[0] = v[0] * m[0] + v[1] * m[3] + v[2] * m[6];
    out[1] = v[0] * m[1] + v[1] * m[4] + v[2] * m[7];
    out[2] = v[0] * m[2] + v[1] * m[5] + v[2] * m[8];
}

int Vec3NearEqual1C4540(f32 *a, f32 *b)
{
    int ret = 0;
    if (fabsf(a[3] - b[3]) < 0.0001f && fabsf(a[1] - b[1]) < 0.0001f && fabsf(a[2] - b[2]) < 0.0001f)
        ret = 1;
    return ret;
}

struct UnkObj1C43B0
{
    int mField00;
    int mField04;
};

void func_001C43B0(UnkObj1C43B0 *arg0, u32 arg1, int arg2)
{
    switch (arg1)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 11:
    case 12:
    case 13:
        break;
    case 10:
        arg0->mField04 &= ~arg2;
        break;
    }
}

struct UnkObj1C4C38
{
    char pad00[0x4];
    f32 mField04; // 0x04
};

void func_001C4C38(UnkObj1C4C38 *arg0, UnkObj1C4C38 *arg1, f32 *out, f32 t)
{
    f32 a = arg0->mField04;
    *out = a + t * (arg1->mField04 - a);
}
