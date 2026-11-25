#include "game/Player.h"
#include "game/CollisionListeners.h"
#include "game/AI_Boss.h"

void UnlockScooterGlobal(int scooterId);  // 0x00153C10
void SubComponentAction1(Scooter *, Vec3f *pos, f32 amount); // 0x001722B0
void SubComponentAction2(Scooter *);      // 0x001723F0
void func_0017F328(Scooter *);            // 0x0017F328
void func_0017F500(Scooter *);            // 0x0017F500
void func_00174198(Scooter *, void *);    // 0x00174198
void func_0011F8F8(void *obj, Vec3f *out);           // 0x0011F8F8
int func_00175970(Scooter *s, int id, f32 value);    // 0x00175970
void func_0011EE30(void *obj, void *p);              // 0x0011EE30

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

int Player::func_00123488(int id, f32 value)
{
    if (mField28 != NULL)
    {
        mField24 = 0;
        Vec3f pos;
        func_0011F8F8(mField28, &pos);
        Vec3f *scooterPos = mScooter->GetPtr78();
        Vec3f d; // computed and never used; the game keeps the stores
        f32 dx = pos.x - scooterPos->x;
        f32 dy = pos.y - scooterPos->y;
        f32 dz = pos.z - scooterPos->z;
        d.x = dx;
        d.y = dy;
        d.z = dz;
    }
    if (!func_00175970(mScooter, id, value))
        return 0;
    if (mField28 == NULL)
        return 0;
    func_0011EE30(mField28, mScooter->GetPtr130());
    return 1;
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

void Player::Action1722B0(Vec3f *pos, f32 amount)
{
    SubComponentAction1(mScooter, pos, amount);
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

f32 Player::AddAdrenaline(f32 amount)
{
    return mScooter->AddAdrenaline(amount);
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
void func_001238C0(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    UnkAttackActor *attack = (UnkAttackActor *)self->mActorA8;
    Player *player = (Player *)other->mActorA8;
    player->mScooter->TakeDamage(attack->mField10);
}

void func_001238E8(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Player *player = (Player *)self->mActorA8;
    UnkAttackActor *attack = (UnkAttackActor *)other->mActorA8;
    player->mScooter->TakeDamage(attack->mField10);
}

// "player_enter_vehicle"
void func_00123910(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Player *player = (Player *)other->mActorA8;
    player->mVehicle3C = self;
}

// "player_leave_vehicle"
void func_00123920(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Player *player = (Player *)other->mActorA8;
    player->mVehicle3C = 0;
}

// "player_hit_pickup" (the pickup side, "pickup_hit_player", does the work)
void func_00123930(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
}

struct UnkGapActor
{
    char field_0x00[0x1C];
    int mField1C;   // 0x1C
    char field_0x20[4];
    u32 mFlags24;   // 0x24
};

// "player_hit_gap"
void func_00123938(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    UnkGapActor *gap = (UnkGapActor *)self->mActorA8;
    Player *player = (Player *)other->mActorA8;
    if (gap != NULL && gap->mField1C != 0 && !(gap->mFlags24 & 2))
        func_00174198(player->mScooter, gap);
}

// "player_hit_checkpoint": the body of Player::func_001237E8 again, or EnableFieldD3 for order 99.
// Calling those two declared inline matches this function too, but then GCC drops their
// out-of-line copies at 0x001237E8 and 0x00123890, which the game has.
void func_00123980(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    UnkCheckpoint *cp = (UnkCheckpoint *)other->mActorA8;
    Player *player = (Player *)self->mActorA8;
    if (cp != NULL)
    {
        if (cp->mOrder18 == 99)
        {
            player->mFieldD3 = 1;
        }
        else
        {
            if (cp->mOrder18 > player->mFieldB8)
            {
                player->mScooter->SetVec194(&cp->mVec34);
                Vec3f *d = &player->mVecC0;
                Vec3f *v = &cp->mVec1C;
                d->x = v->x;
                d->y = v->y;
                d->z = v->z;
                player->mFieldBC = 1;
            }
            else
            {
                player->mScooter->SetVec194(&cp->mVec40);
                Vec3f *d = &player->mVecC0;
                Vec3f *v = &cp->mVec28;
                d->x = v->x;
                d->y = v->y;
                d->z = v->z;
                player->mFieldBC = 0;
            }
            player->mFieldB8 = cp->mOrder18;
        }
    }
}

// "player_hit_restart"
void func_00123A40(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
}

// "player_enter_ambientarea"
void func_00123A48(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Player *player = (Player *)other->mActorA8;
    DD_ActorInfo *area = self->mActorA8;
    if (player->mAmbientAreaA0 != area)
    {
        player->mAmbientAreaA0 = area;
        player->mAmbientStateD2 = 9;
    }
    else
        player->mAmbientStateD2 |= 0x10;
}

// "player_left_ambientarea"
void func_00123A78(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Player *player = (Player *)other->mActorA8;
    if (!(player->mAmbientStateD2 & 0x10))
    {
        player->mAmbientAreaA0 = 0;
        player->mAmbientStateD2 = 10;
        return;
    }
    player->mAmbientStateD2 &= ~0x10;
}

// "player_enter_player"
void func_00123AA8(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Player *player = (Player *)self->mActorA8;
    Player *otherPlayer = (Player *)other->mActorA8;
    if (player != NULL && otherPlayer != NULL)
        player->mOtherPlayer38 = otherPlayer;
}

// "player_leave_player"
void func_00123AC8(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Player *player = (Player *)self->mActorA8;
    Player *otherPlayer = (Player *)other->mActorA8;
    if (player != NULL && otherPlayer != NULL)
        player->mOtherPlayer38 = 0;
}

Vec3f *func_00122DC8(Player *player);   // 0x00122DC8: the player's position
Mat4x4f *func_00122D08(Player *player); // 0x00122D08: the player's matrix (row 2 is used)

// With -ffast-math (verify.py) GCC turns this into a bare sqrt.s, as in the game.
extern "C" float sqrtf(float);

// "player_hit_boss": within 5 units, the player hits the boss when its boost state and the side
// the boss is on agree; otherwise the boss's attack hits the player.
void func_00123AE8(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    AI_Boss *boss = (AI_Boss *)other->mActorA8;
    Player *player = (Player *)self->mActorA8;
    Vec3f *bossPos = boss->VirtSlot5();
    Vec3f *pos = func_00122DC8(player);
    f32 dx = bossPos->x - pos->x;
    f32 dy = bossPos->y - pos->y;
    f32 dz = bossPos->z - pos->z;
    Vec3f d;
    d.x = dx;
    d.y = dy;
    d.z = dz;
    Vec3f side;
    side.x = -dz;
    side.y = dy;
    side.z = dx;
    Vec4f *axis = &func_00122D08(player)->row[2];
    f32 dot = axis->x * side.x + axis->y * side.y + axis->z * side.z;
    if (sqrtf(d.x * d.x + d.y * d.y + d.z * d.z) > 5.0f)
        return;
    if (player->GetStatFactor() > 0.0f &&
        ((player->IsBoostInactive() && dot >= 0.0f) || (player->IsBoostUnavailable() && dot <= 0.0f)))
    {
        boss->func_0015EFB8(player->GetStatFactor());
        player->ApplySpecialAction(boss->VirtSlot8() <= 0.0f);
    }
    else
    {
        player->Action1722B0(boss->VirtSlot5(), boss->mAttack1D8->mField10);
    }
}
