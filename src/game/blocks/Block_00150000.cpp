#include "common/types.h"

// Functions of 0x00150000..0x00153FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8();       // 0x001974D8
void MemFree1BD978(void *); // 0x001BD978

void func_00151608(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_00151760()
{
}

void func_001519E0()
{
}

void func_001519E8()
{
}

void func_001519F0()
{
}

void func_001519F8()
{
}

void func_00151A00()
{
}

void func_00151A08()
{
}

void func_00151A10()
{
}

void func_00151C28()
{
}

void func_00151CB8()
{
    func_001974D8();
}

void func_0016F630(int); // 0x0016F630
void func_001F48A0(int); // 0x001F48A0

// UnkObj151900 (0x00151900..0x00151938): no RTTI; its layout is the fields these methods use.
struct UnkObj151900
{
    char field_0x0[0x6];
    s16 mField6;         // 0x6
    void *mField8;       // 0x8
    void *mFieldC;       // 0xC

    void Method151900(); // 0x00151900
    void Method151938(); // 0x00151938
};

void UnkObj151900::Method151900()
{
    MemFree1BD978(mFieldC);
    MemFree1BD978(mField8);
    MemFree1BD978(this);
}

void UnkObj151900::Method151938()
{
    mField6 = 0;
}

// UnkObj152498 (0x00152498): no RTTI; its layout is the fields these methods use.
struct UnkObj152498
{
    char field_0x0[0x68];
    int mField68;         // 0x68
    int mField6C;         // 0x6C

    void Method152498();  // 0x00152498
};

void UnkObj152498::Method152498()
{
    int tmp;

    tmp = mField6C;
    if (tmp != 0)
    {
        func_0016F630(tmp);
        func_001F48A0(mField68);
    }
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

f32 *MemAlloc1BD958(int); // 0x001BD958
extern f32 data_002B24F8;
extern f32 data_002B24FC;
extern int data_0025E720;
extern int data_0025E738;
// The object at data_0025E73C; only the fields read by func_001519B0..func_001519D0 are known.
struct UnkObj25E73C
{
    char pad00[0xC8];
    int mFieldC8; // 0xC8
    int mFieldCC; // 0xCC
    int mFieldD0; // 0xD0
    int padD4;
    int mFieldD8; // 0xD8
};
extern UnkObj25E73C *data_0025E73C;
extern int data_00261C4C;

void func_00150928(int arg0)
{
    data_0025E720 = arg0;
}

int func_00150938()
{
    return data_0025E720;
}

void func_001515B8(int arg0, f32 fparg0, f32 fparg1)
{
    data_0025E738 = arg0;
    data_002B24F8 = fparg0;
    data_002B24FC = fparg1;
}

void func_001515D8()
{
    f32 *temp_v0;

    temp_v0 = MemAlloc1BD958(4);
    if (temp_v0 != NULL)
    {
        *temp_v0 = 1.0f;
    }
}

f32 func_00151758(f32 *arg0)
{
    return *arg0;
}

int func_001519B0()
{
    return data_0025E73C->mFieldCC;
}

int func_001519C0()
{
    return data_0025E73C->mFieldD0;
}

int func_001519D0()
{
    return data_0025E73C->mFieldD8;
}

UnkObj25E73C *func_00151D10()
{
    return data_0025E73C;
}

void func_00151D20(int arg0)
{
    data_00261C4C = arg0;
}

int func_00151D30()
{
    return data_00261C4C;
}

void func_00151CD8()
{
    data_0025E73C->mFieldC8 |= 1;
}

void func_00151CF0()
{
    data_0025E73C->mFieldC8 &= ~1;
}

struct EnvObj;
struct UnkObjDef;

void *func_00116560(UnkObjDef *, const Vec3f *, const Vec4f *, int); // 0x00116560
void func_0014FB08(EnvObj *, UnkObjDef *, int);          // 0x0014FB08
extern "C" int func_001B07C8(void *, int);               // 0x001B07C8
extern "C" int func_001B08A0(void *);                    // 0x001B08A0
extern "C" void func_001B3BE8(void *, void *, void *);   // 0x001B3BE8
void *func_001BD558(int, int);                // 0x001BD558

struct UnkObj1520D8
{
    int mField00;     // 0x00
    int mField04;     // 0x04
    char pad08[0x18];
    char mField20[0x40]; // 0x20
    int mField60;     // 0x60
    f32 mField64;     // 0x64
    void *mField68;   // 0x68
    int mField6C;     // 0x6C
    int mField70;     // 0x70
    int mField74;     // 0x74
    int mField78;     // 0x78
    int mField7C;     // 0x7C
};

struct UnkSrc1520D8
{
    int mField00;     // 0x00
    char pad04[0x14];
    Vec3f mField18;   // 0x18
    Vec4f mField24;   // 0x24
    char pad34[0x0C];
    f32 mField40;     // 0x40
};

struct UnkSub1520D8
{
    char pad00[0xA8];
    void *mFieldA8;   // 0xA8
};

void func_001520D8(UnkObj1520D8 *arg0, UnkSrc1520D8 *arg1, UnkObjDef *arg2)
{
    Vec4f *v24 = &arg1->mField24;
    Vec3f *v18 = &arg1->mField18;
    int s3 = func_001B07C8(arg1, 0);
    int s4 = func_001B08A0(arg1);
    f32 f20 = arg1->mField40;
    func_0014FB08((EnvObj *)arg0, arg2, 0);
    func_001B3BE8(arg0->mField20, v24, v18);
    arg0->mField64 = f20;
    arg0->mField70 = s3;
    arg0->mField60 = 0;
    arg0->mField68 = 0;
    arg0->mField6C = 0;
    arg0->mField74 = 0;
    arg0->mField78 = 0;
    arg0->mField7C = 0;
    UnkSub1520D8 *sub = (UnkSub1520D8 *)func_00116560(arg2, v18, v24, s4);
    arg0->mField68 = sub;
    if (sub != 0)
        sub->mFieldA8 = arg0;
    arg0->mField00 = arg1->mField00;
}

UnkObj1520D8 *func_00152330(Vec4f *arg0, Vec3f *arg1, int arg2, int arg3, UnkObjDef *arg4, f32 fparg0)
{
    UnkObj1520D8 *obj = (UnkObj1520D8 *)func_001BD558(0x80, 4);
    if (obj != 0)
    {
        func_0014FB08((EnvObj *)obj, arg4, 0);
        func_001B3BE8(obj->mField20, arg0, arg1);
        obj->mField64 = fparg0;
        obj->mField70 = arg2;
        obj->mField60 = 0;
        obj->mField68 = 0;
        obj->mField6C = 0;
        obj->mField74 = 0;
        obj->mField78 = 0;
        obj->mField7C = 0;
        UnkSub1520D8 *sub = (UnkSub1520D8 *)func_00116560(arg4, arg1, arg0, arg3);
        obj->mField68 = sub;
        if (sub != 0)
            sub->mFieldA8 = obj;
        obj->mField04 |= 0x80000000;
    }
    return obj;
}
