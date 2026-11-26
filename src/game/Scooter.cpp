#include "common/libc.h"
#include "game/Scooter.h"
#include "game/CollisionListeners.h"
#include "game/Tricks.h"
#include "game/GameCtx.h"
#include "game/UnkEffect.h"

int func_0011A940(void *obj); // 0x0011A940

int func_001850D0(void *obj, UnkTrickSeq *seq); // 0x001850D0: nonzero when obj accepts seq


void PhysicsClear1F34B0(void *obj, int flag); // 0x001F34B0
void func_0011A3E0(void *obj, int id);        // 0x0011A3E0
void func_0011A590(void *obj);                // 0x0011A590
void func_001BC438(void *obj, f32 a, f32 b);  // 0x001BC438
f32 func_001255C8();                          // 0x001255C8: the adrenaline cap
int func_00125968(int id);                    // 0x00125968
int func_00125808();                          // 0x00125808
int func_001257E0();                          // 0x001257E0
void func_00186080(int value);                // 0x00186080
int func_001860F0(int obj);                   // 0x001860F0
void func_00185E20(int obj, int arg);         // 0x00185E20
void func_00185F50(int obj);                  // 0x00185F50

struct UnkScooterTimer
{
    u32 mFlags00; // 0x00
    u32 mMask04;  // 0x04
    f32 mTimer08; // 0x08
    f32 mDur0C;   // 0x0C

    void Init(u32 mask, f32 dur);      // 0x0017E0E0
};

void UnkScooterTimer::Init(u32 mask, f32 dur)
{
    mFlags00 = 0;
    mMask04 = mask;
    mTimer08 = dur;
    mDur0C = dur;
}

void Scooter::Method17E298()
{
}

int Scooter::GetField18()
{
    return mFlags18;
}

f32 Scooter::GetField70()
{
    return mHealth;
}

int Scooter::GetField6C()
{
    return mField6C;
}

void Scooter::func_0017E450()
{
    mState208->mFlags04 |= 0x10000;
}

void Scooter::func_0017E468()
{
    mState208->mFlags04 &= 0xFFFF;
}

int Scooter::func_0017E478()
{
    return mState208->mFlags04 & 0x10000;
}

void Scooter::func_0017E490()
{
    mFlags18 |= 8;
}

void Scooter::func_0017E4A0()
{
    *(int *)&mFlags18 &= ~8;
}

int Scooter::func_0017E4B8()
{
    return mState208->mState00;
}

void Scooter::ClearField9C()
{
    *(int *)&mField9C = 0;
}

int Scooter::func_0017E4D0()
{
    return mField52C != 0;
}

void Scooter::SetField544(f32 v)
{
    mField544 = v;
}

void Scooter::SetField558(f32 v)
{
    mField558 = v;
}

void Scooter::SetField5BC(f32 v)
{
    mField5BC = v;
}

void Scooter::SetFieldCC(int v)
{
    mFieldCC = v;
}

void Scooter::SetFieldC8(f32 v)
{
    mFieldC8 = v;
}

f32 Scooter::func_0017E508()
{
    f32 mul = 1.0f;
    if (mFlags18 & 0x400)
        mul = mParams1C0->mAdrenaline158;
    if (mSpeedBoostAmount > 0.0f)
        mul *= mSpeedBoostDuration;
    return mFieldC8 * mul;
}

f32 Scooter::func_0017E558()
{
    if (mSpinBoostAmount > 0.0f)
        return mSpinBoostDuration;
    return 1.0f;
}

f32 Scooter::func_0017E588()
{
    if (mJumpBoostAmount > 0.0f)
        return mJumpBoostDuration;
    return 1.0f;
}

f32 Scooter::func_0017E5B8()
{
    if (mBalanceBoostAmount > 0.0f)
        return mBalanceBoostDuration;
    return 1.0f;
}

f32 Scooter::func_0017E5E8()
{
    f32 mul = 1.0f;
    if (mFlags18 & 0x400)
        mul = mParams1C0->mAdrenaline158;
    if (mSpeedBoostAmount > 0.0f)
        mul *= mSpeedBoostDuration;
    return mFieldC8 * mul * mParams1C0->mField7C;
}

f32 Scooter::func_0017E640()
{
    f32 mul = 1.0f;
    if (mFlags18 & 0x400)
        mul = mParams1C0->mAdrenaline158;
    if (mSpeedBoostAmount > 0.0f)
        mul *= mSpeedBoostDuration;
    return mFieldC8 * mul * mParams1C0->mField68;
}

f32 Scooter::func_0017E698()
{
    f32 mul = 1.0f;
    if (mFlags18 & 0x400)
        mul = mParams1C0->mAdrenaline158;
    if (mSpeedBoostAmount > 0.0f)
        mul *= mSpeedBoostDuration;
    return mFieldC8 * mul * mParams1C0->mSpeedMin118;
}

int Scooter::GetField504()
{
    return mField504;
}

int Scooter::GetField508()
{
    return mField508;
}

int Scooter::GetField50C()
{
    return mField50C;
}

void Scooter::ClearFields50C_508()
{
    mField508 = 0;
    mField50C = 0;
}

f32 Scooter::ScaleRampLaunch(f32 v)
{
    if (gGameCtx262250->mField18 == 1)
        v = (v - 1.0f) * mParams1C0->mRampLaunch15C + 1.0f;
    return v;
}

f32 Scooter::ScaleWedgeLaunch(f32 v)
{
    if (gGameCtx262250->mField18 == 1)
        v = (v - 1.0f) * mParams1C0->mWedgeLaunch160 + 1.0f;
    return v;
}

f32 Scooter::RandomStartAcc124()
{
    f32 val = mParams1C0->mStartAcc124;
    if ((rand() % 101 - 50) * 0.02f < 0.0f)
        val = -val;
    return val;
}

f32 Scooter::RandomStartAcc100()
{
    f32 val = mParams1C0->mStartAcc100;
    if ((rand() % 101 - 50) * 0.02f < 0.0f)
        val = -val;
    return val;
}

f32 Scooter::RandomStartAcc13C()
{
    f32 val = mParams1C0->mStartAcc13C;
    if ((rand() % 101 - 50) * 0.02f < 0.0f)
        val = -val;
    return val;
}

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

f32 Scooter::GetStatFactor()
{
    if (mState208->mState00 == 1 && mField210 >= 0 &&
        (func_00125968(mField210) == 3 || func_00125968(mField210) == 4))
        return 1.0f;
    if (mState208->mState00 == 13)
        return 1.0f;
    if (mBoostState != 0)
        return mField634 * 0.5f;
    return 0.0f;
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

void Scooter::ApplySpecialAction(int mode)
{
    if (mBoostState != 0)
    {
        if (mode)
            mField6C += func_00125808();
        else
            mField6C += func_001257E0();
        return;
    }
    func_00186080(mField500);
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

Vec3f *Scooter::GetPtr78()
{
    return &mPos78;
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

void Scooter::func_0017EF30()
{
    int v = func_0011A940(mField368);
    if (v != 0)
    {
        mField370->func_00141A18();
        mField370->SetField28(v);
        mField370->func_001419A0(0);
    }
}

void Scooter::Action1850D0(int seq)
{
    func_001850D0(mField20C, func_001258F8(seq));
}

void Scooter::func_0017F500(int a, int b)
{
    mField27C = b;
    mField280 = a;
}

void Scooter::func_0017F568()
{
    mField518 = 0;
    mField510 = mField98;
}

void Scooter::func_0017F690(int arg)
{
    int prev;
    if (((UnkScooterSub500 *)mField500)->mField04 != 0)
        prev = func_001860F0(mField500);
    else
        prev = 0;
    func_00185E20(mField500, arg);
    f32 diff = func_001860F0(mField500) - prev;
    asm("");
    mAdrenaline += diff;
}

int Scooter::func_0017F718()
{
    return ((UnkScooterSub500 *)mField500)->mField04 == 0;
}

void Scooter::func_0017F790(UnkScooterArgC *arg)
{
    if (arg->mField0C > 0)
        func_00185F50(mField500);
}

f32 Scooter::func_0017F820()
{
    f32 mul = 1.0f;
    if (mFlags18 & 0x400)
        mul = mParams1C0->mAdrenaline158;
    if (mSpeedBoostAmount > 0.0f)
        mul *= mSpeedBoostDuration;
    return mField9C * (mField90 / (mFieldC8 * mul * mParams1C0->mField7C)) * -0.43633235f;
}

void Scooter::func_0017F898(f32 x, f32 y, f32 z)
{
    Vec3f v;
    v.x = x;
    v.y = y;
    v.z = z;
    UnkScooterSub1CC *sub = (UnkScooterSub1CC *)mField1CC;
    sub->mSub24->mField90 += v.x;
    sub->mSub24->mField94 += v.y;
    sub->mSub24->mField98 += v.z;
}

#ifdef NON_MATCHING
// 5 of 12 instructions match. The logic is right; the FP registers are not: here `cur` gets $f0
// (it is returned) before the 0.0f constant, which sched1 hoists above the subtraction so that it
// lives longer and loses priority. In the game 0.0f gets $f0, next $f1 and cur $f2, and the
// zero store moves into a bc1tl delay slot. Result variables, do/while(0) and reordered
// conditions did not change it, and neither did -ffast-math (with >=, 0.0f >, a zero variable or
// the result in a variable).
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

int Scooter::Method17F8F0(f32 v)
{
    int trick = -1;
    if (v < mField90)
    {
        if (func_001850D0(mField20C, func_001258F8(0x27)) != 0)
            trick = 0x4F;
        else
            trick = (func_001850D0(mField20C, func_001258F8(0x26)) != 0) ? 0x50 : -1;
    }
    return trick;
}
