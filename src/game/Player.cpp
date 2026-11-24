#include "game/Player.h"

void UnlockScooterGlobal(int scooterId);  // 0x00153C10
void SubComponentAction1(ScootCtrl *);    // 0x001722B0
void SubComponentAction2(ScootCtrl *);    // 0x001723F0

void Player::AddKey()
{
    mKeys++;
}

int Player::GetKeys()
{
    return mKeys;
}

void Player::AddSpeedBoost(f32 amount, f32 dur)
{
    mScootCtrl->AddSpeedBoost(amount, dur);
}

void Player::AddSpinBoost(f32 amount, f32 dur)
{
    mScootCtrl->AddSpinBoost(amount, dur);
}

void Player::AddJumpBoost(f32 amount, f32 dur)
{
    mScootCtrl->AddJumpBoost(amount, dur);
}

void Player::AddBalanceBoost(f32 amount, f32 dur)
{
    mScootCtrl->AddBalanceBoost(amount, dur);
}

void Player::AddHealth(f32 percent)
{
    mScootCtrl->AddHealth(percent);
}

void Player::AddScooter(int scooterId)
{
    UnlockScooterGlobal(scooterId);
}

void Player::AddBGM(int bgmId)
{
    mBGMs[mNumBGMs] = bgmId;
    mNumBGMs++;
}

int Player::GetNumBGMs()
{
    return mNumBGMs;
}

int Player::GetBGM(int index)
{
    return mBGMs[index];
}

f32 Player::GetStatFactor()
{
    return mScootCtrl->GetStatFactor();
}

int Player::IsBoostInactive()
{
    return mScootCtrl->IsBoostInactive();
}

int Player::IsBoostUnavailable()
{
    return mScootCtrl->IsBoostUnavailable();
}

void Player::SetBoostField62C(f32 val)
{
    mScootCtrl->SetBoostField62C(val);
}

void Player::SetBoostField630(f32 val)
{
    mScootCtrl->SetBoostField630(val);
}

void Player::ApplySpecialAction(int mode)
{
    mScootCtrl->ApplySpecialAction(mode);
}

void Player::Action1722B0()
{
    SubComponentAction1(mScootCtrl);
}

void Player::Action1723F0()
{
    SubComponentAction2(mScootCtrl);
}

f32 Player::GetMaxConstant1000()
{
    return 1000.0f;
}

int Player::HasAdrenaline()
{
    return mScootCtrl->HasAdrenaline();
}

f32 Player::ConsumeAdrenaline(f32 amount)
{
    return mScootCtrl->ConsumeAdrenaline(amount);
}
