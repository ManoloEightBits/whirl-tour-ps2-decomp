#include "game/Player.h"
#include "game/CollisionListeners.h"

void UnlockScooterGlobal(int scooterId);  // 0x00153C10
void SubComponentAction1(Scooter *);      // 0x001722B0
void SubComponentAction2(Scooter *);      // 0x001723F0
void func_0017F328(Scooter *);            // 0x0017F328
void func_0017F500(Scooter *);            // 0x0017F500
void func_00174198(Scooter *, void *);    // 0x00174198

void Player::Action17F328()
{
    func_0017F328(mScooter);
}

void Player::Action17F500()
{
    func_0017F500(mScooter);
}

void *Player::GetPtr40()
{
    return mBlock40;
}

void *Player::GetPtr58()
{
    return mBlock58;
}

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
    mScooter->AddSpeedBoost(amount, dur);
}

void Player::AddSpinBoost(f32 amount, f32 dur)
{
    mScooter->AddSpinBoost(amount, dur);
}

void Player::AddJumpBoost(f32 amount, f32 dur)
{
    mScooter->AddJumpBoost(amount, dur);
}

void Player::AddBalanceBoost(f32 amount, f32 dur)
{
    mScooter->AddBalanceBoost(amount, dur);
}

void Player::AddHealth(f32 percent)
{
    mScooter->AddHealth(percent);
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
    return mScooter->GetStatFactor();
}

int Player::IsBoostInactive()
{
    return mScooter->IsBoostInactive();
}

int Player::IsBoostUnavailable()
{
    return mScooter->IsBoostUnavailable();
}

void Player::SetBoostField62C(f32 val)
{
    mScooter->SetBoostField62C(val);
}

void Player::SetBoostField630(f32 val)
{
    mScooter->SetBoostField630(val);
}

void Player::ApplySpecialAction(int mode)
{
    mScooter->ApplySpecialAction(mode);
}

void Player::Action1722B0()
{
    SubComponentAction1(mScooter);
}

void Player::Action1723F0()
{
    SubComponentAction2(mScooter);
}

f32 Player::GetMaxConstant1000()
{
    return 1000.0f;
}

int Player::HasAdrenaline()
{
    return mScooter->HasAdrenaline();
}

f32 Player::ConsumeAdrenaline(f32 amount)
{
    return mScooter->ConsumeAdrenaline(amount);
}

void Player::Action17ECC8(void *arg)
{
    mScooter->func_0017ECC8(arg);
}

void Player::Action174198(void *arg)
{
    func_00174198(mScooter, arg);
}

void Player::func_001237E8(UnkCheckpoint *cp)
{
    if (cp->mOrder18 > mFieldB8)
    {
        mScooter->SetVec194(&cp->mVec34);
        Vec3f *d = &mVecC0;
        Vec3f *v = &cp->mVec1C;
        d->x = v->x;
        d->y = v->y;
        d->z = v->z;
        mFieldBC = 1;
    }
    else
    {
        mScooter->SetVec194(&cp->mVec40);
        Vec3f *d = &mVecC0;
        Vec3f *v = &cp->mVec28;
        d->x = v->x;
        d->y = v->y;
        d->z = v->z;
        mFieldBC = 0;
    }
    mFieldB8 = cp->mOrder18;
}

void Player::EnableFieldD3()
{
    mFieldD3 = 1;
}

int Player::GetScooterField500()
{
    return mScooter->GetField500();
}

// Collision callbacks (DD_CollisionCallback) from the table at 0x00281070, which pairs each with a
// key string: 0x001238C0 is "player_hit_bossattack", 0x001238E8 "player_hit_bossattackthrow". Both
// pass a float at +0x10 of one actor to the other actor's Scooter; the first takes the Scooter from
// `other`, the second from `self`.
struct UnkAttackActor
{
    char field_0x00[0x10];
    f32 mField10; // 0x10
};

void func_001238C0(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    UnkAttackActor *attack = (UnkAttackActor *)self->mActorA8;
    Player *player = (Player *)other->mActorA8;
    player->mScooter->func_0017EAA0(attack->mField10);
}

void func_001238E8(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Player *player = (Player *)self->mActorA8;
    UnkAttackActor *attack = (UnkAttackActor *)other->mActorA8;
    player->mScooter->func_0017EAA0(attack->mField10);
}
