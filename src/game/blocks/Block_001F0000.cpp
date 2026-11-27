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

