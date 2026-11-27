#include "common/types.h"
#include "game/GL.h"
#include "game/UnkArray.h"

// Functions of 0x00170000..0x00173FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void MemFree1BD978(void *); // 0x001BD978

// UnkObj170958 (0x00170958): no RTTI; its layout is the fields these methods use.
struct UnkObj170958
{
    char field_0x0[0x8];
    void *mField8;       // 0x8
    void *mFieldC;       // 0xC
    void *mField10;      // 0x10

    void Method170958(); // 0x00170958
};

void UnkObj170958::Method170958()
{
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;

    temp_a0 = mField8;
    if (temp_a0 != NULL)
    {
        MemFree1BD978(temp_a0);
    }
    temp_a0_2 = mFieldC;
    if (temp_a0_2 != NULL)
    {
        MemFree1BD978(temp_a0_2);
    }
    temp_a0_3 = mField10;
    if (temp_a0_3 != NULL)
    {
        MemFree1BD978(temp_a0_3);
    }
    MemFree1BD978(this);
}

// UnkObj170B00 (0x00170B00): no RTTI; its layout is the fields these methods use.
struct UnkObj170B00
{
    char field_0x0[0xC];
    int mFieldC;                   // 0xC
    f32 mField10;                  // 0x10
    char field_0x14[0x4];
    f32 mField18;                  // 0x18

    void Method170B00(f32 fparg0); // 0x00170B00
};

void UnkObj170B00::Method170B00(f32 fparg0)
{
    int tmp;

    tmp = mFieldC & 1;
    switch (tmp)                                /* irregular */
    {
    case 0:
        mField18 = fparg0;
        return;
    case 1:
        mField10 = fparg0;
        return;
    }
}

// UnkObj171050 (0x00171050): no RTTI; its layout is the fields these methods use.
struct UnkObj171050
{
    UnkArray1BB0D0 *mArray0; // 0x0: stride 0x1C
    UnkArray1BB0D0 *mArray4; // 0x4: stride 0x80

    void *Method171050(); // 0x00171050
};

void *UnkObj171050::Method171050()
{
    mArray0 = ArrayCreate1BB0E0(0x1C);
    mArray4 = ArrayCreate1BB0E0(0x80);
    return this;
}

void *MemAlloc1BD958(int);     // 0x001BD958
void *func_001BD558(int, int); // 0x001BD558

struct UnkObj170898
{
    int mField00;   // 0x00
    int mField04;   // 0x04
    void *mField08; // 0x08
    void *mField0C; // 0x0C
    void *mField10; // 0x10
};

UnkObj170898 *func_00170898(int arg0, int arg1, int arg2, int arg3)
{
    UnkObj170898 *obj = (UnkObj170898 *)MemAlloc1BD958(0x14);
    if (obj != 0)
    {
        obj->mField00 = arg0;
        obj->mField04 = arg1;
        obj->mField08 = func_001BD558(arg1 * 0xC, 4);
        obj->mField0C = (arg2 != 0) ? func_001BD558(arg1 * 8, 4) : 0;
        obj->mField10 = (arg3 != 0) ? func_001BD558(arg1 * 4, 4) : 0;
    }
    return obj;
}

struct UnkObj170A78
{
    char pad00[0x90];
    UnkObj170958 *mField90; // 0x90
};

void func_00170A78(UnkObj170A78 *arg0)
{
    UnkObj170958 *sub = arg0->mField90;
    if (sub != 0)
    {
        if (sub->mField8 != 0)
            MemFree1BD978(sub->mField8);
        if (sub->mFieldC != 0)
            MemFree1BD978(sub->mFieldC);
        if (sub->mField10 != 0)
            MemFree1BD978(sub->mField10);
        MemFree1BD978(sub);
    }
}

extern "C" void func_00150FD0(int, void *, void *, void *); // 0x00150FD0
extern "C" void func_001713B0();                           // 0x001713B0
extern void *data_00262CB8;

void func_001713C0()
{
    int sp0;
    func_00150FD0(8, (void *)func_001713B0, data_00262CB8, &sp0);
}

struct UnkObj170AE8
{
    char pad00[0x1C];
    Vec3f mVec1C; // 0x1C
};

void func_00170AE8(UnkObj170AE8 *arg0, f32 x, f32 y, f32 z)
{
    Vec3f *v = &arg0->mVec1C;
    arg0->mVec1C.x = x;
    v->y = y;
    v->z = z;
}

struct UnkObj1709C0
{
    unsigned int mMode00; // 0x00
    int mCount04;         // 0x04
    const void *mVerts08; // 0x08
    const void *mTex0C;   // 0x0C
    const void *mColor10; // 0x10
};

void func_001709C0(UnkObj1709C0 *arg0)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, arg0->mVerts08);
    if (arg0->mTex0C != 0)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, arg0->mTex0C);
    }
    if (arg0->mColor10 != 0)
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, arg0->mColor10);
    }
    glDrawArrays(arg0->mMode00, 0, arg0->mCount04);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
