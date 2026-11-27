#include "common/types.h"

// Functions of 0x001F0000..0x001F3FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

void func_001F2EE8(int *arg0, int arg1)
{
    *arg0 = arg1;
}

int func_001F2EF0(int *arg0)
{
    return *arg0;
}

int func_001F2F08(int arg0)
{
    return arg0;
}

int func_001F2F10(int arg0)
{
    return arg0;
}

int func_001F2F18(int arg0)
{
    return arg0;
}

int func_001F2F20(int arg0)
{
    return arg0;
}

int func_001F30B8(int arg0)
{
    return arg0 + 0x30;
}

extern "C" void func_001D6C90(void *);           // 0x001D6C90
extern "C" void func_001F6148(void *, void *, int); // 0x001F6148
extern "C" void func_001CB0C8(void *, void *);   // 0x001CB0C8
extern "C" void func_001F2768(void *, int);      // 0x001F2768
extern "C" void func_001EF7A8(void *, int);      // 0x001EF7A8
extern "C" void func_001F69B8(void *);           // 0x001F69B8
extern "C" void func_001F8328(void *, void *);   // 0x001F8328
extern "C" void *__builtin_new(int);             // 0x00100BE8
extern "C" void *func_001F9E20(void *);          // 0x001F9E20
extern "C" void func_001F9E80(void *, void *);   // 0x001F9E80
extern "C" void func_001FA390(void *, void *); // 0x001FA390
extern "C" void func_001FA248(void *, void *);   // 0x001FA248
extern "C" void func_001F7A68(void *, void *);   // 0x001F7A68
extern "C" void func_001F8E98(void *);           // 0x001F8E98
extern "C" void func_001F9100(void *, void *);   // 0x001F9100

struct UnkIVPTime
{
    u64 mVal;
} __attribute__((packed));

extern "C" void func_001F42B8(void *, UnkIVPTime *, void *, void *); // 0x001F42B8

struct UnkIVPEnv14
{
    char pad00[0xC];
    void *mListenerMgr0C; // 0x0C
    void *mField10;       // 0x10
    char pad14[0xF0];
    UnkIVPTime mTime104;  // 0x104
};

struct IVP_Real_Object
{
    char pad00[0x14];
    UnkIVPEnv14 *mEnv14;  // 0x14
    virtual ~IVP_Real_Object(); // 0x18 (vptr)
};

struct UnkIVPSub94
{
    int mField00;
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual ~UnkIVPSub94();
};

struct IVP_Real_Object_Fields
{
    char pad00[0x14];
    UnkIVPEnv14 *mEnv14;  // 0x14
    char pad18[0x60];
    struct
    {
        s64 mType78 : 8;
        s64 mCollDet78 : 2;
    } mFlags78;           // 0x78
    char pad80[0x14];
    UnkIVPSub94 *mSub94;  // 0x94
    char pad98[0x4];
    void *mCore9C;        // 0x9C
};

void PhysicsClear1F34B0(void *objVoid, int enable)
{
{
    IVP_Real_Object_Fields *obj = (IVP_Real_Object_Fields *)objVoid;
    if (enable != 0)
    {
        if (((int)(*(u64 *)&obj->mFlags78 >> 8) & 3) == 0)
        {
            func_001CB0C8(obj->mEnv14->mField10, obj);
            obj->mFlags78.mCollDet78 = 1;
        }
    }
    else if (((int)(*(u64 *)&obj->mFlags78 >> 8) & 3) != 0)
    {
        if (obj->mSub94 != 0)
            delete obj->mSub94;
        obj->mSub94 = 0;
        obj->mFlags78.mCollDet78 = 0;
        func_001F2768(obj, 1);
    }
}
}

void func_001F3470(IVP_Real_Object_Fields *obj)
{
    func_001D6C90(obj->mCore9C);
}

void func_001F3620(IVP_Real_Object_Fields *obj, int listener)
{
    func_001F6148(obj->mEnv14->mListenerMgr0C, obj, listener);
}

void PhysicsRelease1F3A70(void *obj)
{
    if (obj != 0)
        delete (IVP_Real_Object *)obj;
}

void func_001F3F30(void *obj, void *rot, void *pos)
{
    UnkIVPTime t = ((IVP_Real_Object_Fields *)obj)->mEnv14->mTime104;
    func_001F42B8(obj, &t, rot, pos);
}

struct UnkIVPCoreEnv
{
    void *mField00; // 0x00
    void *mField04; // 0x04
    void *mField08; // 0x08
    char pad0C[0xF8];
    UnkIVPTime mTime104; // 0x104
};

struct UnkIVPVec
{
    u16 mSize;
    u16 mCount;
    void **mElems;
    u32 mPad08;
};

struct UnkIVPVec4
{
    f32 x, y, z, w;
};

struct UnkIVPCore
{
    union
    {
        u64 mFlags00;
        struct
        {
            u64 mPad00 : 2;
            u64 mMovable00 : 2;
            u64 mFlag04 : 2;
        } mBits00;
    };                    // 0x00
    int mField08;         // 0x08
    UnkIVPCoreEnv *mEnv0C; // 0x0C
    char pad10[0x4C];
    UnkIVPVec mObjects5C; // 0x5C
    void *mField68;       // 0x68
    char pad6C[0x4];
    u8 mField70;          // 0x70
    char pad71[0x4F];
    UnkIVPVec4 mFieldC0;  // 0xC0
    char padD0[0x20];
    UnkIVPVec4 mFieldF0;  // 0xF0
    char pad100[0x60];
    UnkIVPVec mVec160;    // 0x160
    u8 *mField16C;        // 0x16C
    UnkIVPTime mTime170;  // 0x170
    char pad178[0x8];
    UnkIVPVec4 mField180; // 0x180
    char pad190[0x10];
    UnkIVPVec4 mField1A0; // 0x1A0
};

#ifdef NON_MATCHING
// 96 of 111 instructions differ: 64-bit bitfield assignment uses dsll32/dsrl and
// core->mField68 = 0 is duplicated into beql delay slots in the original binary.
extern "C" void func_001F1E40(IVP_Real_Object_Fields *obj, int arg1)
{
    UnkIVPCore *core = (UnkIVPCore *)obj->mCore9C;
    UnkIVPVec *objs = &core->mObjects5C;
    if (((int)(core->mFlags00 >> 2) & 3) != arg1)
    {
        for (int i = objs->mCount - 1; i >= 0; i--)
        {
            func_001F2768(objs->mElems[i], 0);
        }
        if (((int)(core->mFlags00 >> 2) & 3) != 0)
        {
            if (core->mField68 != 0)
                func_001EF7A8(core->mField68, 3);
        }
        core->mField68 = 0;
        if (core->mField70 < 8)
            func_001F69B8(core);
        core->mBits00.mMovable00 = arg1;
        if (arg1 == 1 && core->mField16C != 0)
        {
            func_001F8328(core->mField16C, core);
            u8 *p = (u8 *)func_001F9E20(__builtin_new(0x24));
            core->mField16C = p;
            func_001F9E80(p, core);
            UnkIVPVec *vec = &core->mVec160;
            *core->mField16C = 8;
            for (int i = vec->mCount - 1; i >= 0; i--)
            {
                for (int j = i; j < vec->mCount - 1; j++)
                {
                    vec->mElems[j] = vec->mElems[j + 1];
                }
                vec->mCount--;
            }
            func_001FA390(core->mEnv0C->mField08, core->mField16C);
            func_001FA248(core, core->mEnv0C->mField00);
        }
    }
}
#endif

#ifdef NON_MATCHING
// 70 of 97 instructions differ: mField1A0 = mFieldC0 uses VU0 lqc2/sqc2 and
// register/stack layout differs around UnkIVPTime arithmetic.
int PhysicsDestroy1F21A8(void *arg0)
{
    UnkIVPCore *core = (UnkIVPCore *)((IVP_Real_Object_Fields *)arg0)->mCore9C;
    if (((int)(core->mFlags00 >> 2) & 3) == 0)
    {
        if (((int)(core->mFlags00 >> 4) & 3) != 0)
        {
            func_001F7A68(core->mEnv0C, core);
        }
        if (core->mField70 < 8)
        {
            UnkIVPVec *objs = &core->mObjects5C;
            for (int i = objs->mCount - 1; i >= 0; i--)
            {
                func_001F2768(objs->mElems[i], 1);
            }
            core->mField180 = core->mFieldF0;
            core->mField1A0 = core->mFieldC0;
            UnkIVPTime t = core->mEnv0C->mTime104;
            struct { f32 hi; f32 lo; } d;
            d.hi = 20.0f;
            d.lo = 0.0f;
            f32 *tp = (f32 *)&t;
            f32 sum = (tp[0] - d.hi) + tp[1];
            s32 intPart = (s32)sum;
            f32 fInt = (f32)intPart;
            struct { f32 a; f32 b; } res;
            res.a = fInt;
            res.b = sum - fInt;
            core->mTime170 = *(UnkIVPTime *)&res;
            func_001F8E98(core->mField16C);
            return ((int (*)(void *, void *))func_001F9100)(core->mField16C, core->mEnv0C);
        }
    }
    return 1;
}
#endif

int func_001F3208(int arg0)
{
    return arg0 + 0x44;
}

