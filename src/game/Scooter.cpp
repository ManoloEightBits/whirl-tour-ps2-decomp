#include "game/Scooter.h"
#include "game/CollisionListeners.h"

void PhysicsClear1F34B0(void *obj, int flag); // 0x001F34B0
void func_0011A3E0(void *obj, int id);        // 0x0011A3E0
void func_0011A590(void *obj);                // 0x0011A590
void func_001BC438(void *obj, f32 a, f32 b);  // 0x001BC438
f32 func_001255C8();                          // 0x001255C8: the adrenaline cap

Vec3f *Scooter::GetPtr194()
{
    return &mVec194;
}

void Scooter::SetVec194(Vec3f *v)
{
    Vec3f *d = &mVec194; // the local pointer is what keeps the addiu (direct member stores fold it)
    d->x = v->x;
    d->y = v->y;
    d->z = v->z;
}

int Scooter::GetField500()
{
    return mField500;
}

void Scooter::SetActorAndClear1D8(void *actor)
{
    mPhysObj1D8->mActorA8 = (DD_ActorInfo *)actor;
    PhysicsClear1F34B0(mPhysObj1D8, 1);
}

int Scooter::IsBoostInactive()
{
    return mBoostState < 1;
}

int Scooter::IsBoostUnavailable()
{
    return ~(u32)mBoostState >> 31;
}

void Scooter::SetBoostField62C(f32 val)
{
    mField62C = val;
}

void Scooter::SetBoostField630(f32 val)
{
    mField630 = val;
}

void Scooter::TakeDamage(f32 amount)
{
    UnkScooterState *state = mState208;
    if (!(state->mFlags04 & 0x02400000) && state->mState00 != 6 && state->mState00 != 4)
    {
        if (!(mFlags18 & 8))
            mHealth -= amount * 100.0f;
        // The do { } while (0) (probably a macro) is required: without it GCC keeps amount in
        // $f13 from the start and `this` in $a2, and schedules the argument setup differently.
        do
        {
            mState208->mFlags04 |= 0x02000000;
            mState208->mField24 = 0;
        } while (0);
        mField36C = 1;
        func_001BC438(mField1A8, 0.1f, amount);
    }
}

void Scooter::func_0017EB48()
{
    func_0017ED58(0x11093);
    func_001BC438(mField1A8, 0.1f, 1.0f);
}

void Scooter::AddHealth(f32 percent)
{
    mHealth += percent * 100.0f;
    if (mHealth > 100.0f)
        mHealth = 100.0f;
}

void Scooter::AddSpeedBoost(f32 amount, f32 dur)
{
    mSpeedBoostAmount = amount;
    mSpeedBoostDuration = dur;
}

void Scooter::AddSpinBoost(f32 amount, f32 dur)
{
    mSpinBoostAmount = amount;
    mSpinBoostDuration = dur;
}

void Scooter::AddJumpBoost(f32 amount, f32 dur)
{
    mJumpBoostAmount = amount;
    mJumpBoostDuration = dur;
}

void Scooter::AddBalanceBoost(f32 amount, f32 dur)
{
    mBalanceBoostAmount = amount;
    mBalanceBoostDuration = dur;
}

int Scooter::GetField1D0()
{
    return mField1D0;
}

int Scooter::GetField1CC()
{
    return mField1CC;
}

f32 Scooter::GetField90()
{
    return mField90;
}

void *Scooter::GetPtr84()
{
    return mBlock84;
}

void *Scooter::GetPtr130()
{
    return mBlock130;
}

void *Scooter::GetPtrE0()
{
    return mBlockE0;
}

f32 Scooter::GetField98()
{
    return mField98;
}

void Scooter::SetField180(f32 val)
{
    mField180 = val;
}

void Scooter::EnableField170()
{
    mField170 = 1;
}

void Scooter::DisableField170()
{
    mField170 = 0;
}

void Scooter::SetVec174(f32 x, f32 y, f32 z)
{
    mVec174X = x;
    mVec174Y = y;
    mVec174Z = z;
}

void *Scooter::GetPtr78()
{
    return mBlock78;
}

void *Scooter::GetField1A0()
{
    return mField1A0;
}

int Scooter::HasAdrenaline()
{
    if (mAdrenaline > 0.0f)
        return 1;
    return 0;
}

f32 Scooter::AddAdrenaline(f32 amount)
{
    f32 max = func_001255C8();
    f32 next = mAdrenaline + amount;
    if (next > max)
    {
        mAdrenaline = max;
        return next - max;
    }
    mAdrenaline = next;
    return amount;
}

int Scooter::IsGrounded()
{
    return (mFlags18 & 4) || mGround68 != 0;
}

void Scooter::func_0017ED58(int arg)
{
    func_0011A3E0(mField1A0, arg);
}

void Scooter::func_0017ED78(const int *list)
{
    while (*list != 0)
    {
        func_0011A3E0(mField1A0, *list);
        list++;
    }
}

void Scooter::func_0017EDD0()
{
    func_0011A590(mField1A0);
}

void Scooter::func_0017EDF0(int flag)
{
    func_0011A3E0(mField1A0, !flag ? 0x11128 : 0x10128);
}

void Scooter::func_0017EE28(int flag)
{
    func_0011A3E0(mField1A0, !flag ? 0x110AD : 0x100AD);
}

#ifdef NON_MATCHING
// 5 of 12 instructions match. The logic is right; the FP registers are not: here `cur` gets $f0
// (it is returned) before the 0.0f constant, which sched1 hoists above the subtraction so that it
// lives longer and loses priority. In the game 0.0f gets $f0, next $f1 and cur $f2, and the
// zero store moves into a bc1tl delay slot. Result variables, do/while(0) and reordered
// conditions did not change it.
f32 Scooter::ConsumeAdrenaline(f32 amount)
{
    f32 cur = mAdrenaline;
    f32 next = cur - amount;
    if (next < 0.0f)
    {
        mAdrenaline = 0.0f;
        return cur;
    }
    mAdrenaline = next;
    return amount;
}
#endif
