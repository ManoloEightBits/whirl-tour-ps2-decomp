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
int func_0011F650(void *obj);                        // 0x0011F650
int func_00175970(Scooter *s, int id, f32 value);    // 0x00175970
void func_0011EE30(void *obj, void *p);              // 0x0011EE30
void func_0017E2A0(Scooter *s, f32 val);             // 0x0017E2A0
void func_00172060(Scooter *s);                      // 0x00172060
void func_0017F288(Scooter *s, void *a, void *b);    // 0x0017F288
f32 func_0017F728(Scooter *s);                       // 0x0017F728

Mat4x4f *Player::GetScooterPtr130()
{
    return (Mat4x4f *)mScooter->GetPtr130();
}

void Player::SetScooterField180(f32 val)
{
    mScooter->SetField180(val);
}

void Player::EnableScooterField170()
{
    mScooter->EnableField170();
}

void Player::DisableScooterField170()
{
    mScooter->DisableField170();
}

void Player::SetScooterVec174(f32 x, f32 y, f32 z)
{
    mScooter->SetVec174(x, y, z);
}

void *Player::GetScooterPtr84()
{
    return mScooter->GetPtr84();
}

Vec3f *Player::GetScooterPtr78()
{
    return mScooter->GetPtr78();
}

void *Player::GetScooterField1A0()
{
    return mScooter->GetField1A0();
}

DD_ActorInfo *Player::GetFieldA0()
{
    return mAmbientAreaA0;
}

int Player::TestAmbientStateD2(u8 mask)
{
    return mAmbientStateD2 & mask;
}

void Player::SetAmbientStateD2(u8 mask)
{
    mAmbientStateD2 |= mask;
}

void Player::ClearAmbientStateD2(u8 mask)
{
    mAmbientStateD2 &= ~mask;
}

f32 Player::GetScooterField70()
{
    return mScooter->GetField70();
}

int Player::GetScooterField6C()
{
    return mScooter->GetField6C();
}

f32 Player::Action17F728()
{
    return func_0017F728(mScooter);
}

void Player::Action17E468()
{
    mScooter->func_0017E468();
}

void Player::Action17E450()
{
    mScooter->func_0017E450();
}

int Player::Action17E478()
{
    return mScooter->func_0017E478();
}

int Player::IsScooterState4()
{
    return mScooter->func_0017E4B8() == 4;
}

void Player::Action17E4A0()
{
    mScooter->func_0017E4A0();
}

void Player::Action17E490()
{
    mScooter->func_0017E490();
}

void Player::Action17E2A0(f32 val)
{
    func_0017E2A0(mScooter, val);
}

void Player::Action172060()
{
    func_00172060(mScooter);
}

void Player::Action17ED58_100FA()
{
    mScooter->func_0017ED58(0x100FA);
}

int Player::Action17E4B8()
{
    return mScooter->func_0017E4B8();
}

void Player::ClearScooterField9C()
{
    mScooter->ClearField9C();
}

f32 Player::GetScooterField98()
{
    return mScooter->GetField98();
}

int Player::Action17E4D0()
{
    return mScooter->func_0017E4D0();
}

void Player::SetScooterField544(f32 val)
{
    mScooter->SetField544(val);
}

void Player::SetScooterField558(f32 val)
{
    mScooter->SetField558(val);
}

void Player::SetScooterField5BC(f32 val)
{
    mScooter->SetField5BC(val);
}

void Player::SetScooterFieldCC(int val)
{
    mScooter->SetFieldCC(val);
}

int Player::GetFieldB8()
{
    return mFieldB8;
}

u8 Player::GetFieldD3()
{
    return mFieldD3;
}

void Player::Action17EDF0(int flag)
{
    mScooter->func_0017EDF0(flag);
}

void Player::Action17EE28(int flag)
{
    mScooter->func_0017EE28(flag);
}

void Player::SetScooterFieldC8(f32 val)
{
    mScooter->SetFieldC8(val);
}

int Player::Action17F718()
{
    return mScooter->func_0017F718();
}

int Player::GetScooterField504()
{
    return mScooter->GetField504();
}

int Player::GetScooterField508()
{
    return mScooter->GetField508();
}

int Player::GetScooterField50C()
{
    return mScooter->GetField50C();
}

void Player::ClearScooterFields50C_508()
{
    mScooter->ClearFields50C_508();
}

void Player::SetFieldD4(int v)
{
    mFieldD4 = v;
}

int Player::GetFieldD4()
{
    return mFieldD4;
}

int Player::GetField30()
{
    return mField30;
}

int Player::GetField34()
{
    return mField34;
}

int Player::func_00123208()
{
    if (mField28 != 0)
        return func_0011F650(mField28);
    return 0;
}

void *Player::GetField28()
{
    return mField28;
}

void Player::Action17F288(void *a, void *b)
{
    func_0017F288(mScooter, a, b);
}

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

//With -ffast-math (verify.py) GCC turns this into a bare sqrt.s, as in the game.
extern "C" float sqrtf(float);

// "player_hit_boss": within 5 units, the player hits the boss when its boost state and the side
// the boss is on agree; otherwise the boss's attack hits the player.
void func_00123AE8(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    AI_Boss *boss = (AI_Boss *)other->mActorA8;
    Player *player = (Player *)self->mActorA8;
    Vec3f *bossPos = boss->GetPosition();
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
        player->Action1722B0(boss->GetPosition(), boss->mAttack1D8->mField10);
    }
}

void func_001416A0(void *); // 0x001416A0

struct UnkSub11F_08
{
    char field_0x00[0x3C];
    f32 mField3C; // 0x3C
};

struct UnkSub11F_50
{
    char field_0x00[0x10];
    Vec3f mVec10; // 0x10
};

struct UnkSub11F_6C
{
    char field_0x000[0x158];
    f32 mField158; // 0x158
};

struct UnkObj11F
{
    int mField00;
    int mField04;
    UnkSub11F_08 *mSub08; // 0x08
    char field_0x0C[0x10];
    int mField1C;         // 0x1C
    int mField20;
    int mField24;
    f32 mField28;         // 0x28
    f32 mField2C;         // 0x2C
    char field_0x30[0x20];
    UnkSub11F_50 *mSub50; // 0x50
    char field_0x54[0x18];
    UnkSub11F_6C *mSub6C; // 0x6C
    int mField70;         // 0x70
    int mField74;
    int mField78;
    int mField7C;         // 0x7C

    f32 GetSub08Field3C();              // 0x0011F8E8
    void GetSub50Vec10(Vec3f *out);     // 0x0011F978
    void SetSub50Vec10(const Vec3f *v); // 0x0011F9A0
    f32 GetSub6CField158();             // 0x0011F9C8
    int GetField7C();                   // 0x0011F9D8
    int GetField70();                   // 0x0011F9E0
    int GetField1C();                   // 0x0011F9E8
    f32 GetField28();                   // 0x0011FA28
    void SetField28(f32 v);             // 0x0011FA30
    f32 GetField2C();                   // 0x0011FA38
    void SetField2C(f32 v);             // 0x0011FA40
};

f32 UnkObj11F::GetSub08Field3C()
{
    return mSub08->mField3C;
}

void UnkObj11F::GetSub50Vec10(Vec3f *out)
{
    Vec3f *s = &mSub50->mVec10;
    out->x = s->x;
    out->y = s->y;
    out->z = s->z;
}

void UnkObj11F::SetSub50Vec10(const Vec3f *v)
{
    Vec3f *d = &mSub50->mVec10;
    d->x = v->x;
    d->y = v->y;
    d->z = v->z;
}

f32 UnkObj11F::GetSub6CField158()
{
    return mSub6C->mField158;
}

int UnkObj11F::GetField7C()
{
    return mField7C;
}

int UnkObj11F::GetField70()
{
    return mField70;
}

int UnkObj11F::GetField1C()
{
    return mField1C;
}

void func_0011F9F0(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    ((UnkObj11F *)other->mActorA8)->mField7C = 1;
    func_001416A0(self->mActorA8);
}

void func_0011FA18(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    ((UnkObj11F *)other->mActorA8)->mField7C = 0;
}

f32 UnkObj11F::GetField28()
{
    return mField28;
}

void UnkObj11F::SetField28(f32 v)
{
    mField28 = v;
}

f32 UnkObj11F::GetField2C()
{
    return mField2C;
}

void UnkObj11F::SetField2C(f32 v)
{
    mField2C = v;
}
