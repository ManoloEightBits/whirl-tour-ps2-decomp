#include "common/types.h"

// Functions of 0x00160000..0x00163FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00163698(); // 0x00163698

void func_00163A30()
{
    func_00163698();
}

// UnkObj1618D0 (0x001618D0..0x001618E8): no RTTI; its layout is the fields these methods use.
struct UnkObj1618D0
{
    char field_0x0[0x1C];
    int mField1C;                // 0x1C
    char field_0x20[0xC];
    f32 mField2C;                // 0x2C

    void SetField2C(f32 v);      // 0x001618C8
    int GetField1C();            // 0x001618D0
    void Method1618D8(int arg1); // 0x001618D8
    void Method1618E8(int arg1); // 0x001618E8
};

void UnkObj1618D0::SetField2C(f32 v)
{
    mField2C = v;
}

int UnkObj1618D0::GetField1C()
{
    return mField1C;
}

void UnkObj1618D0::Method1618D8(int arg1)
{
    mField1C |= arg1;
}

void UnkObj1618D0::Method1618E8(int arg1)
{
    mField1C &= ~arg1;
}

struct EnvObj;
void PhysicsRelease1F3A70(void *); // 0x001F3A70
void func_0016FCC8(void *, int);   // 0x0016FCC8
void EnvObjCleanup14FB70(EnvObj *); // 0x0014FB70
void MemFree1BD978(void *);        // 0x001BD978

struct UnkObj161708
{
    char field_0x0[0xF4];
    void *mFieldF4;                // 0xF4
    void *mPhysicsF8;              // 0xF8

    void Destroy161708();          // 0x00161708
};

void UnkObj161708::Destroy161708()
{
    PhysicsRelease1F3A70(mPhysicsF8);
    if (mFieldF4 != 0)
    {
        func_0016FCC8(mFieldF4, 3);
    }
    EnvObjCleanup14FB70((EnvObj *)this);
    MemFree1BD978(this);
}
