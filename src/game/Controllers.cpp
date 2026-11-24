#include "game/Controllers.h"

// The game controllers come from several TUs (IP_PosCtrl and MotionCtrl share the one of
// DD_Event_Listener.cpp); grouped here because they are written identically.

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

void MBCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

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
