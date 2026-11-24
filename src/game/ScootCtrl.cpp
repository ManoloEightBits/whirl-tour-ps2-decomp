#include "game/ScootCtrl.h"

int ScootCtrl::IsBoostInactive()
{
    return mBoostState < 1;
}

int ScootCtrl::IsBoostUnavailable()
{
    return ~(u32)mBoostState >> 31;
}

void ScootCtrl::SetBoostField62C(f32 val)
{
    mField62C = val;
}

void ScootCtrl::SetBoostField630(f32 val)
{
    mField630 = val;
}

void ScootCtrl::AddHealth(f32 percent)
{
    mHealth += percent * 100.0f;
    if (mHealth > 100.0f)
        mHealth = 100.0f;
}

void ScootCtrl::AddSpeedBoost(f32 amount, f32 dur)
{
    mSpeedBoostAmount = amount;
    mSpeedBoostDuration = dur;
}

void ScootCtrl::AddSpinBoost(f32 amount, f32 dur)
{
    mSpinBoostAmount = amount;
    mSpinBoostDuration = dur;
}

void ScootCtrl::AddJumpBoost(f32 amount, f32 dur)
{
    mJumpBoostAmount = amount;
    mJumpBoostDuration = dur;
}

void ScootCtrl::AddBalanceBoost(f32 amount, f32 dur)
{
    mBalanceBoostAmount = amount;
    mBalanceBoostDuration = dur;
}

int ScootCtrl::GetField1D0()
{
    return mField1D0;
}

int ScootCtrl::GetField1CC()
{
    return mField1CC;
}

f32 ScootCtrl::GetField90()
{
    return mField90;
}

void *ScootCtrl::GetPtr84()
{
    return mBlock84;
}

void *ScootCtrl::GetPtr130()
{
    return mBlock130;
}

void *ScootCtrl::GetPtrE0()
{
    return mBlockE0;
}

f32 ScootCtrl::GetField98()
{
    return mField98;
}

void ScootCtrl::SetField180(f32 val)
{
    mField180 = val;
}

void ScootCtrl::EnableField170()
{
    mField170 = 1;
}

void ScootCtrl::DisableField170()
{
    mField170 = 0;
}

void ScootCtrl::SetVec174(f32 x, f32 y, f32 z)
{
    mVec174X = x;
    mVec174Y = y;
    mVec174Z = z;
}

void *ScootCtrl::GetPtr78()
{
    return mBlock78;
}

int ScootCtrl::GetField1A0()
{
    return mField1A0;
}

int ScootCtrl::HasAdrenaline()
{
    if (mAdrenaline > 0.0f)
        return 1;
    return 0;
}

int ScootCtrl::IsGrounded()
{
    return (mFlags18 & 4) || mGround68 != 0;
}

#ifdef NON_MATCHING
// 5 of 12 instructions match. The logic is right; the FP registers are not: here `cur` gets $f0
// (it is returned) before the 0.0f constant, which sched1 hoists above the subtraction so that it
// lives longer and loses priority. In the game 0.0f gets $f0, next $f1 and cur $f2, and the
// zero store moves into a bc1tl delay slot. Result variables, do/while(0) and reordered
// conditions did not change it.
f32 ScootCtrl::ConsumeAdrenaline(f32 amount)
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
