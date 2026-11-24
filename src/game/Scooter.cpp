#include "game/Scooter.h"

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

int Scooter::GetField1A0()
{
    return mField1A0;
}

int Scooter::HasAdrenaline()
{
    if (mAdrenaline > 0.0f)
        return 1;
    return 0;
}

int Scooter::IsGrounded()
{
    return (mFlags18 & 4) || mGround68 != 0;
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
