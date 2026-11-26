#include "common/types.h"

// Functions of 0x0011C000..0x0011FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// UnkObj11F568 (0x0011F568): no RTTI; its layout is the fields these methods use.
struct UnkObj11F568
{
    char field_0x0[0x20];
    int mField20;                // 0x20

    void Method11F568(int arg1); // 0x0011F568
};

void UnkObj11F568::Method11F568(int arg1)
{
    mField20 = (int) (arg1 - 1);
}

struct EnvObj;
void PhysicsRelease1F3A70(void *); // 0x001F3A70
void func_00191E40(void *);        // 0x00191E40
void EnvObjCleanup14FB70(EnvObj *); // 0x0014FB70
void MemFree1BD978(void *);        // 0x001BD978

struct UnkObj11FA48
{
    char field_0x0[0x4C];
    void *mField4C;                // 0x4C
    void *mField50;                // 0x50
    void *mField54;                // 0x54
    void *mField58;                // 0x58
    char field_0x5C[0x14];
    void *mPhysics70;              // 0x70

    void Destroy11FA48();          // 0x0011FA48
};

void UnkObj11FA48::Destroy11FA48()
{
    PhysicsRelease1F3A70(mPhysics70);
    func_00191E40(mField4C);
    func_00191E40(mField50);
    func_00191E40(mField54);
    func_00191E40(mField58);
    EnvObjCleanup14FB70((EnvObj *)this);
    MemFree1BD978(this);
}
