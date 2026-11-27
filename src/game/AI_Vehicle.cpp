#include "game/AI_Vehicle.h"

void func_00193100(UnkNode *node); // 0x00193100

f32 AI_Vehicle::GetFieldEC()
{
    return mFieldEC;
}

void AI_Vehicle::SetFieldEC(f32 v)
{
    mFieldEC = v;
}

void AI_Vehicle::AddFieldEC(f32 v)
{
    mFieldEC += v;
}

void AI_Vehicle::SubFieldEC(f32 v)
{
    mFieldEC -= v;
}

UnkVehicleParams * AI_Vehicle::GetParams11C()
{
    return mParams11C;
}

int AI_Vehicle::GetFieldF0()
{
    return mFieldF0;
}

int AI_Vehicle::GetFieldF4()
{
    return mFieldF4;
}

int AI_Vehicle::GetField104()
{
    return mField104;
}

int * AI_Vehicle::GetPtr108()
{
    return &mField108;
}

f32 * AI_Vehicle::GetPtr10C()
{
    return &mField10C;
}

void AI_Vehicle::SetField10C(f32 v)
{
    mField10C = v;
}

void AI_Vehicle::AddField10C(f32 v)
{
    mField10C += v;
}

Vec3f * AI_Vehicle::GetPtrE0()
{
    return &mFieldE0;
}

Vec4f * AI_Vehicle::GetRow1()
{
    return &mMatrixA0.row[1];
}

Vec4f * AI_Vehicle::GetRow0()
{
    return &mMatrixA0.row[0];
}

f32 AI_Vehicle::GetSpeed1C()
{
    return mParams11C->mSpeed1C;
}

f32 AI_Vehicle::GetFieldF8()
{
    return mFieldF8;
}

void AI_Vehicle::SetFieldF8(f32 v)
{
    mFieldF8 = v;
}

f32 AI_Vehicle::GetFieldFC()
{
    return mFieldFC;
}

f32 AI_Vehicle::GetField100()
{
    return mField100;
}

f32 AI_Vehicle::GetWheelRadius6C()
{
    return mParams11C->mWheelRadius6C;
}

void AI_Vehicle::Action10E468()
{
    func_0010E468();
}

void AI_Vehicle::func_0010E468()
{
    if (mNode138 != NULL)
        func_00193100(mNode138);
}

void AI_Vehicle::Action10D1A0()
{
    func_0010D1A0();
}

f32 AI_Vehicle::func_0010E4B0(f32 v)
{
    mFlags20 &= ~0x10000;
    f32 next = mFieldF8 + v;
    if (next < mParams11C->mSpeed1C)
    {
        mFieldF8 = next;
        return next;
    }
    mFlags20 &= ~0x40000;
    mFieldF8 = mParams11C->mSpeed1C;
    return mFieldF8;
}

f32 AI_Vehicle::func_0010E508(f32 v)
{
    f32 next = mFieldF8 - v;
    if (0.0f < next)
    {
        mFieldF8 = next;
        return next;
    }
    mFlags20 = (mFlags20 & ~0x20000) | 0x10000;
    mFieldF8 = 0.0f;
    return 0.0f;
}

void AI_Vehicle::func_0010E558(UnkObj58 *obj)
{
    obj->mField58 = func_0012CCB0(obj->mField58);
}

Vec3f *AI_Vehicle::GetPosition()
{
    return (Vec3f *)&mMatrixA0.row[3];
}

Vec4f *AI_Vehicle::GetRow2()
{
    return &mMatrixA0.row[2];
}

Mat4x4f *AI_Vehicle::GetMatrix()
{
    return &mMatrixA0;
}

struct EnvObj;
struct UnkObj194EC0;
void EnvObjCleanup14FB70(EnvObj *);         // 0x0014FB70
void PhysicsDestroy1F21A8(void *);          // 0x001F21A8
void PhysicsClear1F34B0(void *, int);       // 0x001F34B0
void PhysicsRelease1F3A70(void *);          // 0x001F3A70
void func_00141950(void *, int);            // 0x00141950
void func_00151608(void *);                 // 0x00151608
void Method194EC0(UnkObj194EC0 *);          // 0x00194EC0 (wait: Method194EC0__12UnkObj194EC0)

struct UnkObj194EC0
{
    void Method194EC0();                    // 0x00194EC0
};

#ifdef NON_MATCHING
// Matches 100% (47/47 insns); gated until AI_Agent : EnvObj is wired so __tf8AI_Agent matches.
AI_Vehicle::~AI_Vehicle()
{
    func_00151608(mField13C);
    if (mFieldF0 != 0)
    {
        PhysicsDestroy1F21A8((void *)mFieldF0);
        PhysicsClear1F34B0((void *)mFieldF0, 0);
        PhysicsRelease1F3A70((void *)mFieldF0);
        mFieldF0 = 0;
    }
    if (mField120 != 0)
    {
        func_00141950(mField120, 3);
        if (mField124 != 0)
            func_00141950(mField124, 3);
    }
    if (mNode138 != 0)
        ((UnkObj194EC0 *)mNode138)->Method194EC0();
    EnvObjCleanup14FB70((EnvObj *)this);
}
#endif
