#include "common/types.h"
#include "game/GL.h"

// Functions of 0x00180000..0x00183FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00141148(int, int); // 0x00141148
void func_0019A370();         // 0x0019A370
f32 Sin1B1910(f32);           // 0x001B1910
f32 Cos1B19E8(f32);           // 0x001B19E8

int func_00180ED8(int arg0)
{
    return arg0 + 0x30;
}

int func_00180EE0(int arg0)
{
    return arg0 + 0x50;
}

void func_00180EE8()
{
}

int func_00183A68()
{
    return 1;
}

int func_00183B80()
{
    func_0019A370();
    return 1;
}

int func_00183C40(int arg0, int arg1)
{
    func_00141148(arg1, arg0);
    return 1;
}

int func_00183C88()
{
    return 1;
}

int func_00183D58()
{
    return 1;
}

int func_00183E88()
{
    return 1;
}

void func_001BCAC0(int);    // 0x001BCAC0
void MemFree1BD978(void *); // 0x001BD978
void func_001BFAC0(int);    // 0x001BFAC0

void PhysicsRelease1F3A70(void *); // 0x001F3A70

// UnkObj1804E8 (0x001804E8..0x00180558, just before ScootCtrl): no RTTI; a float and two physics
// objects that Destroy releases.
struct UnkObj1804E8
{
    f32 mField00;    // 0x0
    void *mPhys04;   // 0x4
    void *mPhys08;   // 0x8

    void Destroy();          // 0x001804E8
    void SubField00(f32 v);  // 0x00180548
    f32 GetField00();        // 0x00180558
};

void UnkObj1804E8::Destroy()
{
    PhysicsRelease1F3A70(mPhys08);
    PhysicsRelease1F3A70(mPhys04);
    MemFree1BD978(this);
}

void UnkObj1804E8::SubField00(f32 v)
{
    mField00 -= v;
}

f32 UnkObj1804E8::GetField00()
{
    return mField00;
}

// UnkObj180EA8 (0x00180EA8): no RTTI; its layout is the fields these methods use.
struct UnkObj180EA8
{
    char field_0x0[0x4C];
    void *mField4C;       // 0x4C

    void Method180EA8();  // 0x00180EA8
};

void UnkObj180EA8::Method180EA8()
{
    MemFree1BD978(mField4C);
    MemFree1BD978(this);
}

// UnkObj182AC8 (0x00182AC8): no RTTI; its layout is the fields these methods use.
struct UnkObj182AC8
{
    char field_0x0[0x10];
    int mField10;                // 0x10
    char field_0x14[0x80];
    int *mField94;               // 0x94

    int *Method182AC8(int arg1); // 0x00182AC8
};

int *UnkObj182AC8::Method182AC8(int arg1)
{
    int *temp_v1;
    int *var_a1;

    var_a1 = NULL;
    if (mField10 == 1)
    {
        temp_v1 = mField94;
        var_a1 = ((arg1 ^ *temp_v1) == 0) ? temp_v1 : NULL;
    }
    return var_a1;
}

// UnkObj182CD0 (0x00182CD0): no RTTI; its layout is the fields these methods use.
struct UnkObj182CD0
{
    char field_0x0[0x8];
    int mField8;         // 0x8

    void Method182CD0(); // 0x00182CD0
};

void UnkObj182CD0::Method182CD0()
{
    func_001BFAC0(mField8);
}

// UnkObj1832A0 (0x001832A0): no RTTI; its layout is the fields these methods use.
struct UnkObj1832A0
{
    char field_0x0[0x444];
    int mField444;         // 0x444

    int GetField444();     // 0x001832A0
};

int UnkObj1832A0::GetField444()
{
    return mField444;
}

// UnkObj183480 (0x00183480..0x00183578): no RTTI; its layout is the fields these methods use.
struct UnkObj183480
{
    char field_0x0[0x4];
    int mField4;         // 0x4
    int mField8;         // 0x8

    void Method183480(); // 0x00183480
    int GetField8();     // 0x00183578
};

void UnkObj183480::Method183480()
{
    func_001BCAC0(mField4);
}

int UnkObj183480::GetField8()
{
    return mField8;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_001821A0(int *arg0, int arg1)
{
    *arg0 = arg1;
}

int func_001835D0(int *arg0)
{
    return *arg0;
}

struct UnkObj1835A8
{
    int mType00;        // 0x00
    char pad04[0x30];
    int mSub34;         // 0x34: a sub-object (size unknown)
};

// The sub-object at +0x34 when the type at +0x00 is 2 or 3, else null.
void *func_001835A8(UnkObj1835A8 *obj)
{
    if ((u32)(obj->mType00 - 2) < 2U)
    {
        return &obj->mSub34;
    }
    return 0;
}

struct UnkBox1810C8
{
    Vec3f mMin; // 0x00
    Vec3f mMax; // 0x0C
};

void func_001810C8(UnkBox1810C8 *box)
{
{
    glBegin(3);
    Vec3f *max = &box->mMax;
    glVertex3f(box->mMin.x, box->mMin.y, box->mMin.z);
    glVertex3f(box->mMax.x, box->mMin.y, box->mMin.z);
    glVertex3f(box->mMax.x, box->mMin.y, max->z);
    glVertex3f(box->mMin.x, box->mMin.y, max->z);
    glVertex3f(box->mMin.x, box->mMin.y, box->mMin.z);
    glEnd();
    glBegin(3);
    glVertex3f(box->mMin.x, max->y, box->mMin.z);
    glVertex3f(box->mMax.x, max->y, box->mMin.z);
    glVertex3f(box->mMax.x, max->y, max->z);
    glVertex3f(box->mMin.x, max->y, max->z);
    glVertex3f(box->mMin.x, max->y, box->mMin.z);
    glEnd();
    glBegin(1);
    glVertex3f(box->mMin.x, box->mMin.y, box->mMin.z);
    glVertex3f(box->mMin.x, max->y, box->mMin.z);
    glVertex3f(box->mMax.x, box->mMin.y, box->mMin.z);
    glVertex3f(box->mMax.x, max->y, box->mMin.z);
    glVertex3f(box->mMax.x, box->mMin.y, max->z);
    glVertex3f(box->mMax.x, max->y, max->z);
    glVertex3f(box->mMin.x, box->mMin.y, max->z);
    glVertex3f(box->mMin.x, max->y, max->z);
    glEnd();
}
}

void func_00181800(f32 x, f32 y, f32 z, f32 r, f32 segs)
{
    if (segs <= 0.1f)
        segs = 0.1f;
    glBegin(3);
    f32 a = 0.0f;
    do
    {
        glVertex3f(x + r * Cos1B19E8(a), y, z + r * Sin1B1910(a));
        a += 6.2831855f / segs;
    } while (a <= 6.2831855f);
    a = 0.0f;
    do
    {
        glVertex3f(x + r * Cos1B19E8(a), y + r * Sin1B1910(a), z);
        a += 6.2831855f / segs;
    } while (a <= 6.2831855f);
    a = 0.0f;
    do
    {
        glVertex3f(x, y + r * Sin1B1910(a), z + r * Cos1B19E8(a));
        a += 6.2831855f / segs;
    } while (a <= 6.2831855f);
    glEnd();
}
