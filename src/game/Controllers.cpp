#include "common/libc.h"
#include "game/Controllers.h"

extern "C" float sqrtf(float);
extern "C" float fabsf(float);
extern "C" void func_001F9FC8(void *, void *); // 0x001F9FC8
void func_001B2DF0(Vec4f *out, void *arg); // 0x001B2DF0

struct Vec4f16
{
    f32 x, y, z, w;
} __attribute__((aligned(16)));

static inline void VecZero(Vec3f *v)
{
    v->x = 0.0f;
    v->y = 0.0f;
    v->z = 0.0f;
}

static inline void VecSet(Vec3f *d, const Vec3f *s)
{
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

static inline void VecSetElems(Vec3f *d, f32 x, f32 y, f32 z)
{
    d->x = x;
    d->y = y;
    d->z = z;
}

static inline void VecAddScaled(Vec3f *d, const Vec3f *s, f32 f)
{
    VecSetElems(d, d->x + f * s->x, d->y + f * s->y, d->z + f * s->z);
}

// The game controllers come from several TUs (IP_PosCtrl and MotionCtrl share the one of
// DD_Event_Listener.cpp); grouped here because they are written identically.

void IP_PosCtrl::SetPos0C(const Vec3f *v)
{
    VecSet(&mPos0C, v);
}

void IP_PosCtrl::ClearPos0C()
{
    VecZero(&mPos0C);
}

IP_PosCtrl::IP_PosCtrl(UnkCtrlObj *obj)
{
    mCore08 = obj->mCore9C;
    mObj04 = obj;
    VecZero(&mPos0C);
    func_001FA148(this, mCore08);
}

void IP_PosCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

void IP_PosCtrl::do_simulation_controller(void *, void *)
{
    Vec4f a;
    Vec4f b;
    func_001F3F30(mObj04, &a, &b); // results unused
    Vec3f *pos = &mPos0C;
    f32 x = pos->x;
    mCore08->field_0xB0.x = x;
    f32 y = pos->y;
    mCore08->field_0xB0.y = y;
    f32 z = pos->z;
    mCore08->field_0xB0.z = z;
    mCore08->field_0x90.x = 0.0f;
    mCore08->field_0x90.y = 0.0f;
    mCore08->field_0x90.z = 0.0f;
}

int IP_PosCtrl::get_controller_priority()
{
    return 500;
}

IP_PosCtrl::~IP_PosCtrl()
{
    func_001FA170(this, mCore08);
}

void MotionCtrl::ClearFlag04_1()
{
    mFlags04 &= ~1;
}

void MotionCtrl::SetFlag04_1()
{
    mFlags04 |= 1;
}

void MotionCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

int MotionCtrl::get_controller_priority()
{
    return 500;
}

MotionCtrl::~MotionCtrl()
{
    func_001FA170(this, mCore80);
}

void IP_RotCtrl::func_00118300(void *arg)
{
    Vec4f q;
    func_001B2DF0(&q, arg);
    do
    {
        mQuat10.x = q.x;
        mQuat10.y = q.y;
        mQuat10.z = q.z;
        mQuat10.w = -q.w;
    } while (0);
}

IP_RotCtrl::IP_RotCtrl(UnkCtrlObj *obj, f32 val)
{
    mCore08 = obj->mCore9C;
    mObj04 = obj;
    Vec4f a;
    Vec4f b;
    func_001F3F30(obj, &a, &b);
    do
    {
        mQuat10.x = a.x;
        mQuat10.y = a.y;
        mQuat10.z = a.z;
        mQuat10.w = a.w;
    } while (0);
    mField20 = val;
    func_001FA148(this, mCore08);
}

void IP_RotCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

int IP_RotCtrl::get_controller_priority()
{
    return 500;
}

IP_RotCtrl::~IP_RotCtrl()
{
    func_001FA170(this, mCore08);
}

int IP_AnimCtrl::TestFlag04_1()
{
    return mFlags04 & 1;
}

void IP_AnimCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

int IP_AnimCtrl::get_controller_priority()
{
    return 500;
}

IP_AnimCtrl::~IP_AnimCtrl()
{
    func_001FA170(this, mCore0C);
}

void MBCtrl::SetFlags04(u8 mask)
{
    mFlags04 |= mask;
}

u8 MBCtrl::GetFlags04()
{
    return mFlags04;
}

void MBCtrl::ClearFlags04(u8 mask)
{
    mFlags04 &= ~mask;
}

void MBCtrl::SetVel08(Vec3f v)
{
    mVel08 = v;
}

void MBCtrl::SetPos14(Vec3f v)
{
    mFlags04 |= 1;
    mPos14 = v;
}

f32 MBCtrl::GetHorizDist18E950()
{
    UnkCore *c = mCore24;
    f32 x = c->field_0xB0.x;
    f32 z = c->field_0xB0.z;
    return sqrtf(x * x + z * z);
}

Vec3f *MBCtrl::GetPtr14()
{
    return &mPos14;
}

void MBCtrl::AddCorePosB0(const Vec3f *v)
{
    mCore24->field_0xB0.x += v->x;
    mCore24->field_0xB0.y += v->y;
    mCore24->field_0xB0.z += v->z;
}

MBCtrl::MBCtrl(UnkCtrlObj *obj)
{
    mFlags04 = 0;
    VecZero(&mVel08);
    VecZero(&mPos14);
    mCore24 = obj->mCore9C;
    mObj20 = obj;
    func_001FA148(this, mCore24);
}

void MBCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

void MBCtrl::do_simulation_controller(void *event, void *)
{
    if (mFlags04 & 1)
    {
        mFlags04 &= ~1;
        VecZero(&mCore24->field_0x90);
        VecSet(&mCore24->field_0xB0, &mPos14);
    }
    f32 dt = *(f32 *)event;
    VecAddScaled(&mCore24->field_0xB0, &mVel08, dt);
    VecSetElems(&mPos14, mCore24->field_0xB0.x, mCore24->field_0xB0.y, mCore24->field_0xB0.z);
}

int MBCtrl::get_controller_priority()
{
    return 500;
}

MBCtrl::~MBCtrl()
{
    func_001FA170(this, mCore24);
}

void ScootCtrl::SetPos08(const Vec3f *v)
{
    mFlags04 |= 7;
    VecSet(&mPos08, v);
}

void ScootCtrl::SetPos08X(f32 x)
{
    mPos08.x = x;
    mFlags04 |= 1;
}

void ScootCtrl::SetPos08Y(f32 y)
{
    mPos08.y = y;
    mFlags04 |= 2;
}

void ScootCtrl::SetPos08Z(f32 z)
{
    mPos08.z = z;
    mFlags04 |= 4;
}

void ScootCtrl::SetVel14(f32 x, f32 y, f32 z)
{
    VecSetElems(&mVel14, x, y, z);
}

void ScootCtrl::ClearFlags04_7()
{
    mFlags04 &= ~7;
}

void ScootCtrl::AddCoreVel90(const Vec3f *v)
{
    mCore24->field_0x90.x += v->x;
    mCore24->field_0x90.y += v->y;
    mCore24->field_0x90.z += v->z;
}

ScootCtrl::ScootCtrl(UnkCtrlObj *obj)
{
    VecZero(&mPos08);
    VecZero(&mVel14);
    mFlags04 = 0;
    mCore24 = obj->mCore9C;
    mObj20 = obj;
    func_001FA148(this, mCore24);
}

void ScootCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

int ScootCtrl::get_controller_priority()
{
    return 500;
}

ScootCtrl::~ScootCtrl()
{
    func_001FA170(this, mCore24);
}

void ScootCtrl::do_simulation_controller(void *event, void *)
{
    if (mFlags04 & 7)
        VecZero(&mCore24->field_0x90);
    if (mFlags04 & 1)
    {
        f32 v = mPos08.x;
        mFlags04 &= ~1;
        mCore24->field_0xB0.x = v;
    }
    if (mFlags04 & 2)
    {
        f32 v = mPos08.y;
        mFlags04 &= ~2;
        mCore24->field_0xB0.y = v;
    }
    if (mFlags04 & 4)
    {
        f32 v = mPos08.z;
        mFlags04 &= ~4;
        mCore24->field_0xB0.z = v;
    }
    f32 dt = *(f32 *)event;
    VecAddScaled(&mCore24->field_0xB0, &mVel14, dt);
}

struct UnkMotionParams117D30
{
    f32 mField00; // 0x00
    f32 mField04; // 0x04
    f32 mField08; // 0x08
    f32 mField0C; // 0x0C
    f32 mField10; // 0x10
    f32 mField14; // 0x14
    f32 mField18; // 0x18
    f32 mField1C; // 0x1C
    f32 mField20; // 0x20
    f32 mField24; // 0x24
    f32 mField28; // 0x28
    f32 mField2C; // 0x2C
    f32 mField30; // 0x30
    f32 mField34; // 0x34
    f32 mField38; // 0x38
    f32 mField3C; // 0x3C
    f32 mField40; // 0x40
    char pad44[0x0C];
};

UnkMotionParams117D30 *func_00117D30(UnkMotionParams117D30 *arg0)
{
{
    memset(arg0, 0, 0x50);
    VecSetElems((Vec3f *)&arg0->mField30, 1000000.0f, 1000000.0f, 1000000.0f);
    arg0->mField40 = 1000000.0f;
    arg0->mField20 = 0.8f;
    arg0->mField24 = 1.0f;
    VecSetElems((Vec3f *)&arg0->mField00, 0.8f, 0.8f, 0.8f);
    VecSetElems((Vec3f *)&arg0->mField10, 1.0f, 1.0f, 1.0f);
    return arg0;
}
}

#ifdef NON_MATCHING
// 2/3, 28/31, 35/38 match: GCC schedules sq into jr $ra delay slot in Method117EA0, and
// hoists lw $v1, 0x78($a0) before sq in Method117F68/Method117FE8.
void MotionCtrl::Method117EA0(const Vec4f *v)
{
    do { *(Vec4f16 *)&mVec40 = *(const Vec4f16 *)v; } while (0);
}

void MotionCtrl::Method117F68(const Vec4f *v)
{
    f32 *p = &mVec10.x;
    f32 dx = v->x - mVec10.x;
    f32 dy = v->y - p[1];
    f32 dz = v->z - p[2];
    if (dx * dx + dy * dy + dz * dz != 0.0f)
    {
        *(Vec4f16 *)&mVec10 = *(const Vec4f16 *)v;
        func_001F9FC8(mField78->mField90, mCore80);
    }
}

void MotionCtrl::Method117FE8(const Vec4f *v)
{
    f32 *p = &mVec20.x;
    f32 dot = v->x * mVec20.x + v->y * p[1] + v->z * p[2] + v->w * p[3];
    if (fabsf(dot - 1.0f) < 1e-10f)
        return;
    *(Vec4f16 *)&mVec20 = *(const Vec4f16 *)v;
    func_001F9FC8(mField78->mField90, mCore80);
}
#endif
