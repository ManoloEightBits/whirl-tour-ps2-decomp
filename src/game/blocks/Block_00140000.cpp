#include "common/types.h"
#include "common/libc.h"
#include "game/UnkEffect.h"

// Functions of 0x00140000..0x00143FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00142400();         // 0x00142400
void func_001A6368();         // 0x001A6368
void func_001A6458();         // 0x001A6458
int func_001A87E8();          // 0x001A87E8
void func_001A8950();         // 0x001A8950
void func_001A89F0();         // 0x001A89F0
void func_001A8C10(int, int); // 0x001A8C10
void func_001A8D50();         // 0x001A8D50
void MemFree1BD978(void *);   // 0x001BD978

void func_00140A88()
{
}

void func_001416A0(void *arg0)
{
}

void func_001416A8()
{
}

void func_001416B0()
{
}

void func_001416B8()
{
}

void UnkEffect::func_00141A18()
{
    func_00142400();
}

void func_001425E0(int, f32)
{
}

void func_00142D70()
{
    func_001A8C10(1, 5);
}

void func_00142D90()
{
    func_001A8C10(0x18, 0x2F);
}

void func_001430E0(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001436B0()
{
}

void func_001436B8()
{
    func_001A89F0();
}

void func_001436D8()
{
    func_001A8950();
}

int func_001436F8()
{
    return func_001A87E8() == 0;
}

void func_00143718()
{
    func_001A6368();
}

void func_00143738()
{
    func_001A6458();
}

void func_00143758()
{
    func_001A8D50();
}

void func_001AB828(int); // 0x001AB828

// UnkObj140FF8 (0x00140FF8): no RTTI; its layout is the fields these methods use.
struct UnkObj140FF8
{
    char field_0x0[0x10];
    f32 mField10;                  // 0x10

    void Method140FF8(f32 fparg0); // 0x00140FF8
};

void UnkObj140FF8::Method140FF8(f32 fparg0)
{
    mField10 = (f32) (mField10 + fparg0);
}

// UnkObj141140 (0x00141140): no RTTI; its layout is the fields these methods use.
struct UnkObj141140
{
    char field_0x0[0x8];
    int mField8;         // 0x8

    int GetField8();     // 0x00141140
};

int UnkObj141140::GetField8()
{
    return mField8;
}

void UnkEffect::Method141A38(int arg1)
{
    mField24 = arg1;
    mField2C |= 0x20;
}

void UnkEffect::SetField28(int v)
{
    mField28 = v;
}

// UnkObj143538 (0x00143538): no RTTI; its layout is the fields these methods use.
struct UnkObj143538
{
    char field_0x0[0x4];
    u16 mField4;         // 0x4

    void Method143538(); // 0x00143538
};

void UnkObj143538::Method143538()
{
    func_001AB828(mField4);
    MemFree1BD978(this);
}

// UnkObj143870 (0x00143870): no RTTI; its layout is the fields these methods use.
struct UnkObj143870
{
    f32 mField0;         // 0x0
    f32 mField4;         // 0x4

    void Method143870(); // 0x00143870
};

void UnkObj143870::Method143870()
{
    mField0 = 0.5f;
    mField4 = 0.01f;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

struct EnvObj;
void func_001424C8(int);      // 0x001424C8
void func_00142568(int);      // 0x00142568
void func_00142660(int, int); // 0x00142660
extern int data_0025E5DC;

int func_00141738(int **arg0)
{
    return (u32) (**arg0 - 2) < 3U;
}

void func_00142368()
{
    if (data_0025E5DC != 0)
    {
        func_00142660(data_0025E5DC, 3);
        data_0025E5DC = 0;
    }
}

void func_001424A0()
{
    func_001424C8(data_0025E5DC);
}

void func_00142540()
{
    func_00142568(data_0025E5DC);
}

void func_00143778(s8 *arg0)
{
    *arg0 = 0;
}

void EnvObjCleanup14FB70(EnvObj *); // 0x0014FB70
void func_001BCAC0(int);            // 0x001BCAC0
extern int * data_0025E5E0;

void func_00142D10(int *arg0)
{
    int *var_a0;

    var_a0 = arg0;
    if (var_a0 == NULL)
    {
        var_a0 = data_0025E5E0;
    }
    func_001BCAC0(*var_a0);
}

// Cleans an EnvObj up and frees it (a non-virtual deleting destructor).
void func_00143840(EnvObj *obj)
{
    EnvObjCleanup14FB70(obj);
    MemFree1BD978(obj);
}

void func_00143A68(EnvObj *obj)
{
    EnvObjCleanup14FB70(obj);
    MemFree1BD978(obj);
}

struct UnkObj141728
{
    char pad00[0x08];
    int mField08; // 0x08
};

int func_00141728(UnkObj141728 **arg0)
{
    return (*arg0)->mField08;
}

void *MemAlloc1BD958(int); // 0x001BD958
struct UnkObj1C3BA8
{
    s16 Method1C3BA8(); // 0x001C3BA8
    int Method1C3BC8(); // 0x001C3BC8
};
extern "C" void func_001A7018(int);                 // 0x001A7018
extern "C" void func_001A7E88(int, int, int);       // 0x001A7E88
extern "C" void func_001A9298(int, int);            // 0x001A9298
s16 func_001A9370(int);                             // 0x001A9370
extern "C" void func_001A9AD8(void *, int, int, int); // 0x001A9AD8
extern "C" int func_0023F860(int);                  // 0x0023F860
extern "C" void func_0023F9C8(int);                 // 0x0023F9C8

struct UnkRes143438
{
    int mField00;     // 0x00
    int mField04;     // 0x04
    int mField08;     // 0x08
    s16 mField0C;     // 0x0C
    s16 mField0E;     // 0x0E
    char mField10[0x20]; // 0x10
};

struct UnkSrc143438
{
    char pad00[0x1E];
    u8 mField1E;      // 0x1E
    u8 pad1F;
    char mField20[0x20]; // 0x20
    char mField40[0x10]; // 0x40
};

UnkRes143438 *func_00143438(UnkSrc143438 *arg0, int arg1, int arg2, int arg3)
{
    UnkRes143438 *res = (UnkRes143438 *)MemAlloc1BD958(0x30);
    if (res != 0)
    {
        res->mField04 = arg1;
        res->mField00 = 1;
        res->mField0C = func_001A9370(((UnkObj1C3BA8 *)arg0)->Method1C3BC8());
        res->mField0E = ((UnkObj1C3BA8 *)arg0)->Method1C3BA8();
        res->mField08 = arg0->mField1E & 1;
        strncpy(res->mField10, arg0->mField20, 0x1F);
        int h = func_0023F860(arg2);
        if (h != 0)
        {
            func_001A9AD8(arg0->mField40, h, arg2, 1);
            func_001A7E88(h, arg3, arg2);
            func_001A9298(arg1, arg3);
            func_001A7018(0);
            func_0023F9C8(h);
        }
    }
    return res;
}

struct UnkEffect1424
{
    char pad00[0x24];
    int mField24; // 0x24
    char pad28[0x04];
    int mField2C; // 0x2C
};

struct UnkObj142428
{
    char pad00[0x20C];
    int mField20C; // 0x20C
};

int func_001425E8();                  // 0x001425E8
void func_00141860(int);              // 0x00141860
void func_00141A50(UnkEffect1424 *);  // 0x00141A50
void func_001BB348(int, int);         // 0x001BB348

int func_00142428(UnkObj142428 *arg0, UnkEffect1424 *arg1)
{
    int idx = func_001425E8();
    if (idx >= 0)
    {
        if (arg1->mField2C & 0x20)
        {
            func_00141860(arg1->mField24);
            func_00141A50(arg1);
        }
        func_001BB348(arg0->mField20C, idx);
    }
    return 1;
}

struct EnvObj;
struct UnkObjDef;

struct UnkSub1437D0
{
    char pad00[0x18];
    int mField18; // 0x18
};

struct UnkObj1437D0
{
    char pad00[0xA8];
    void *mFieldA8; // 0xA8
};

void *MemAlloc1BD958(int);                            // 0x001BD958
void func_0014FB08(EnvObj *, UnkObjDef *, int);       // 0x0014FB08

void *func_001437D0(int arg0, UnkObjDef *arg1, UnkObj1437D0 *arg2)
{
    UnkSub1437D0 *p = (UnkSub1437D0 *)MemAlloc1BD958(0x1C);
    if (p != 0)
    {
        func_0014FB08((EnvObj *)p, arg1, 0);
        p->mField18 = arg0;
        arg2->mFieldA8 = p;
    }
    return p;
}

void *func_001439F8(int arg0, UnkObjDef *arg1, UnkObj1437D0 *arg2)
{
    UnkSub1437D0 *p = (UnkSub1437D0 *)MemAlloc1BD958(0x1C);
    if (p != 0)
    {
        func_0014FB08((EnvObj *)p, arg1, 0);
        p->mField18 = arg0;
        arg2->mFieldA8 = p;
    }
    return p;
}

int *func_001B9978(int, int);         // 0x001B9978
void func_00143568(int *, f32, f32);  // 0x00143568

void func_00141548(int arg0, f32 arg1, f32 arg2)
{
    int *p = func_001B9978(data_0025E5E0[3], arg0);
    if (p != 0 && *p == 1)
        func_00143568(p, arg1, arg2);
}

struct UnkEntry143078
{
    int mField00;
    f32 mField04;
    char mName08[0x20];
};

UnkEntry143078 *func_00143078(const char *arg0, int arg1, f32 arg2)
{
    UnkEntry143078 *p = (UnkEntry143078 *)MemAlloc1BD958(0x28);
    if (p != 0)
    {
        p->mField00 = arg1;
        p->mField04 = arg2;
        strcpy(p->mName08, arg0);
    }
    return p;
}

void Release198F38(void *);     // 0x00198F38
void func_00191E40(void *);    // 0x00191E40
void __builtin_delete(void *); // 0x00100C08
void func_00142400();          // 0x00142400

void func_00140A40(void **arg0, int arg1)
{
    Release198F38(*arg0);
    if (arg1 & 1)
        __builtin_delete(arg0);
}

struct UnkObj140FA8
{
    void *mField00; // 0x00
    void *mField04; // 0x04
};

void func_00140FA8(UnkObj140FA8 *arg0, int arg1)
{
    Release198F38(arg0->mField00);
    func_00191E40(arg0->mField04);
    if (arg1 & 1)
        __builtin_delete(arg0);
}

void func_00141950(void *arg0, int arg1)
{
    ((UnkEffect1424 *)arg0)->mField2C |= 0x10;
    func_00142400();
    if (arg1 & 1)
        __builtin_delete(arg0);
}

// Synthesized from m2c (0x00140028)
struct UnkObj140028
{
    int mField00; // 0x00
    int mField04; // 0x04
    void Method140028();
};

int func_001423A0(void *); // 0x001423A0
extern "C" void __builtin_delete(void *);

void UnkEffect::func_001419A0(int arg1)
{
    if (arg1 != 0)
        mField2C |= 4;
    if (func_001423A0(this) == 0 && arg1 != 0 && this != 0)
    {
        mField2C |= 0x10;
        ((void (*)(void *))func_00142400)(this);
        __builtin_delete(this);
    }
}

void UnkObj140028::Method140028()
{
    this->mField00 = 0;
    this->mField04 = 0;
}

struct UnkObj143170
{
    char pad00[0x4];
    int mField04; // 0x04
    int mField08; // 0x08
    int mField0C; // 0x0C
};

UnkObj143170 *func_00142E58(void *, void *); // 0x00142E58
void func_00142DE0(void *, void *);          // 0x00142DE0
void func_001A9500(int);                     // 0x001A9500
void func_001AA230(int);                     // 0x001AA230

void func_00143170(void *arg0, int arg1)
{
    UnkObj143170 *obj = func_00142E58(data_0025E5E0, arg0);
    ((void (*)(int))func_001A8D50)(obj->mField08);
    func_001A9500(obj->mField0C);
    func_001AA230(obj->mField04);
    func_00142DE0(data_0025E5E0, arg0);
}

