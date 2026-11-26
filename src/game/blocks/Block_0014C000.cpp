#include "common/types.h"
#include "game/GL.h"

// Functions of 0x0014C000..0x0014FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00126138(int);    // 0x00126138
void func_0014C4E8(int);    // 0x0014C4E8
void func_001974D8();       // 0x001974D8
int MemAlloc1BD958(int);     // 0x001BD958
void MemFree1BD978(void *); // 0x001BD978

void func_0014C198()
{
    func_001974D8();
}

void func_0014C200()
{
}

void func_0014C208(void *arg0)
{
    MemFree1BD978(arg0);
    func_00126138(0);
}

void func_0014C2B8()
{
    func_001974D8();
}

void func_0014C3B8()
{
}

void func_0014C4D8()
{
}

void func_0014C4E0()
{
}

int func_0014C908(int arg0)
{
    return arg0 + 4;
}

int func_0014C920()
{
    return 0xA;
}

int func_0014C9C0()
{
    int result;

    result = MemAlloc1BD958(0x98);
    if (result != 0)
    {
        func_0014C4E8(result);
    }
    return result;
}

void func_0014CAC8(void *arg0)
{
    MemFree1BD978(arg0);
}

int func_0014CAE8(int arg0)
{
    return arg0 + 0xC;
}

void func_0014E990(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_0014E9B0()
{
    func_001974D8();
}

void func_0014EC80()
{
    func_001974D8();
}

void func_0014C2B8();    // 0x0014C2B8
void func_0016F630(int); // 0x0016F630
void func_0018BFA0(int); // 0x0018BFA0
int func_0018C018(int);  // 0x0018C018
void func_001F48A0(int); // 0x001F48A0

// UnkObj14C1B8 (0x0014C1B8): no RTTI; its layout is the fields these methods use.
struct UnkObj14C1B8
{
    char field_0x0[0x94];
    int mField94;         // 0x94

    void Method14C1B8();  // 0x0014C1B8
};

void UnkObj14C1B8::Method14C1B8()
{
    int tmp;

    tmp = mField94;
    switch (tmp)                                /* irregular */
    {
    case 0x100:
        mField94 = 0xF000;
        return;
    case 0xF000:
        func_0014C2B8();
        break;
    }
}

// UnkObj14E748 (0x0014E748): no RTTI; its layout is the fields these methods use.
struct UnkObj14E748
{
    int mField0;                 // 0x0
    int mField4;                 // 0x4

    void Method14E748(int arg1); // 0x0014E748
};

void UnkObj14E748::Method14E748(int arg1)
{
    mField4 = 0;
    mField0 = (int) (1 << arg1);
}

// UnkObj14EF90 (0x0014EF90): no RTTI; its layout is the fields these methods use.
struct UnkObj14EF90
{
    char field_0x0[0x6C];
    int mField6C;         // 0x6C

    int Method14EF90();   // 0x0014EF90
};

int UnkObj14EF90::Method14EF90()
{
    int temp_a0;
    int var_v0;

    temp_a0 = mField6C;
    var_v0 = 0;
    if (temp_a0 != 0)
    {
        var_v0 = func_0018C018(temp_a0);
    }
    return var_v0;
}

// UnkObj14F3A8 (0x0014F3A8): no RTTI; its layout is the fields these methods use.
struct UnkObj14F3A8
{
    char field_0x0[0x6C];
    int mField6C;         // 0x6C

    void Method14F3A8();  // 0x0014F3A8
};

void UnkObj14F3A8::Method14F3A8()
{
    int tmp;

    tmp = mField6C;
    if (tmp != 0)
    {
        func_0018BFA0(tmp);
    }
}

// UnkObj14F5D8 (0x0014F5D8): no RTTI; its layout is the fields these methods use.
struct UnkObj14F5D8
{
    char field_0x0[0x18];
    int mField18;         // 0x18
    int mField1C;         // 0x1C

    void Method14F5D8();  // 0x0014F5D8
};

void UnkObj14F5D8::Method14F5D8()
{
    int tmp;

    tmp = mField1C;
    if (tmp != 0)
    {
        func_0016F630(tmp);
        func_001F48A0(mField18);
    }
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_0014C900(int *arg0)
{
    return *arg0;
}

int func_0014C910(int *arg0, int *arg1)
{
    return *arg1 - *arg0;
}

void func_00126620(int, int, int, int); // 0x00126620
void func_00197AB8(int);           // 0x00197AB8

void func_0014C3C0(int arg0, int arg1)
{
    func_00197AB8(arg1 + 4);
}

void func_0014F158(int arg0, int arg1, int arg2)
{
    func_00126620(arg1, arg0, arg2, 0);
}

struct EnvObj;
void func_001F39D0(void *);      // 0x001F39D0
void DrawModel196110(void *);    // 0x00196110

// Empty in this build (the EnvObj delete helpers call it before freeing).
void EnvObjCleanup14FB70(EnvObj *obj)
{
}

// UnkObj14CAF0 (0x0014CAF0..0x0014CCB0): EnvObj-derived object with matrix at +0x20, physics at +0x70, model at +0x78.
struct UnkObj14CAF0
{
    char field_0x0[0x8];
    int mField8;                 // 0x08
    char field_0xC[0x14];
    f32 mMatrix20[16];           // 0x20
    char field_0x60[0x10];
    void *mPhysics70;            // 0x70
    char field_0x74[0x4];
    void *mModel78;              // 0x78

    int GetField8();             // 0x0014CAF0
    void Destroy14CC78();        // 0x0014CC78
    void Draw14CCB0();           // 0x0014CCB0
};

int UnkObj14CAF0::GetField8()
{
    return mField8;
}

void UnkObj14CAF0::Destroy14CC78()
{
    EnvObjCleanup14FB70((EnvObj *)this);
    func_001F39D0(mPhysics70);
    MemFree1BD978(this);
}

void UnkObj14CAF0::Draw14CCB0()
{
    glPushMatrix();
    glMultMatrixf(mMatrix20);
    DrawModel196110(mModel78);
    glPopMatrix();
}

struct UnkObj14EB68
{
    char pad00[0xA4];
    void *mFieldA4; // 0xA4
    char padA8[0x08];
};

void *func_001BD558(int, int);                  // 0x001BD558
void func_0014EBE0(UnkObj14EB68 *, int, void *); // 0x0014EBE0
void *ArrayCreate1BB0E0(int);                   // 0x001BB0E0
void func_001BB1B0(void *, int);                // 0x001BB1B0

UnkObj14EB68 *func_0014EB68(int arg0)
{
    UnkObj14EB68 *obj = (UnkObj14EB68 *)func_001BD558(0xB0, 4);
    if (obj != 0)
    {
        func_0014EBE0(obj, arg0, func_001BD558(arg0 << 7, 4));
        void *arr = ArrayCreate1BB0E0(0x94);
        obj->mFieldA4 = arr;
        func_001BB1B0(arr, 0x64);
    }
    return obj;
}

struct UnkSub14C128
{
    char pad00[0x1C];
    int mField1C; // 0x1C
};

struct UnkObj14C128
{
    char pad00[0x98];
    UnkSub14C128 *mField98; // 0x98
    void *mField9C;         // 0x9C
    void *mFieldA0;         // 0xA0
    char padA4[0x18];
    int mFieldBC;           // 0xBC
    int mFieldC0;           // 0xC0
    char padC4[0x08];
    void *mFieldCC;         // 0xCC
    char padD0[0x04];
    void *mFieldD4;         // 0xD4
};

void func_001982D0(int, int);      // 0x001982D0
void Release198F38(void *);       // 0x00198F38
void func_00191E40(void *);       // 0x00191E40
void ArrayDestroy1BB168(int);     // 0x001BB168
void CleanupDialog1309E0(void *); // 0x001309E0
void func_0014CAC8(void *);       // 0x0014CAC8

void func_0014C128(UnkObj14C128 *arg0)
{
    func_001982D0(arg0->mField98->mField1C, 0);
    Release198F38(arg0->mFieldA0);
    func_00191E40(arg0->mField9C);
    ArrayDestroy1BB168(arg0->mFieldC0);
    ArrayDestroy1BB168(arg0->mFieldBC);
    CleanupDialog1309E0(arg0->mFieldCC);
    func_0014CAC8(arg0->mFieldD4);
    MemFree1BD978(arg0);
    func_00126138(0);
}

struct UnkVec14FA78
{
    f32 x;
    f32 y;
    f32 z;
};

struct UnkObj14FA78
{
    char pad00[0xC0];
    void *mFieldC0; // 0xC0
};

void *__builtin_new(u32);                        // 0x00100BE8
void *func_00165100(void *, f32, f32, f32);      // 0x00165100

void func_0014FA78(UnkObj14FA78 *arg0, UnkVec14FA78 *arg1)
{
    if (arg0->mFieldC0 == 0)
        arg0->mFieldC0 = func_00165100(__builtin_new(0x138), arg1->x, arg1->y, arg1->z);
}
