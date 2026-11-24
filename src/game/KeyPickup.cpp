#include "game/Pickup.h"
#include "game/CollisionListeners.h"

extern "C" char *func_00231F08(char *dst, const char *src, u32 n); // 0x00231F08 (runtime library; probably strncpy)

u32 HashStringCRC32(const char *str);                    // 0x001B1CD0
int SendScriptEvent(u32 eventCrc, int arg1, void *arg2); // 0x001266D0
void *FindPickupDef(const char *name);                   // 0x00126518
void PickupHelper11B2A0(Pickup *);                       // 0x0011B2A0
void PhysicsDestroy1F21A8(void *);                       // 0x001F21A8
void PhysicsClear1F34B0(void *, int);                    // 0x001F34B0
void PhysicsRelease1F3A70(void *);                       // 0x001F3A70
void CleanupNode194EC0(void *);                          // 0x00194EC0
void EnvObjCleanup14FB70(EnvObj *);                      // 0x0014FB70

static inline f32 AbsF(f32 x)
{
    return __builtin_fabsf(x);
}

void Pickup::Call11B2A0()
{
    PickupHelper11B2A0(this);
}

Vec3f *Pickup::GetPos44()
{
    return &mPos44;
}

Vec3f *Pickup::GetPos50()
{
    return &mPos50;
}

int Pickup::IsState4()
{
    return mState60 == 4;
}

void Pickup::OnCollected(Player *)
{
}

void Pickup::SetCallback68(void (*callback)(int), int arg)
{
    mCallback68 = callback;
    mCallbackArg6C = arg;
}

inline Pickup::~Pickup()
{
    PhysicsDestroy1F21A8(mPhysicsObj18);
    PhysicsClear1F34B0(mPhysicsObj18, 0);
    PhysicsRelease1F3A70(mPhysicsObj18);
    if (mCount34 > 0)
    {
        for (int i = 0; i < mCount34; i++)
        {
            if (mArray3C[i] != 0)
                CleanupNode194EC0(mArray3C[i]);
        }
        if (mArray3C != 0)
            delete[] mArray3C;
    }
    if (mCount38 > 0)
    {
        for (int i = 0; i < mCount38; i++)
        {
            if (mArray40[i] != 0)
                CleanupNode194EC0(mArray40[i]);
        }
        if (mArray40 != 0)
            delete[] mArray40;
    }
    EnvObjCleanup14FB70(this);
}

// Stub key method to trigger Pickup vtable and RTTI emission before subclasses;
// ignored in config/probes.txt until Pickup::Update (0x0011B3D8) is decompiled.
void Pickup::Update(f32)
{
}

void KeyPickup::Update(f32 dt)
{
    Pickup::Update(dt);
    if (mBounce88 != 0)
    {
        mHeightOffset74 += mVel80 * dt;
        mVel80 -= 9.8f * dt;
        if (mHeightOffset74 < mFloor84)
        {
            mVel80 = -mVel80 * 0.4f;
            mHeightOffset74 = mFloor84 + (mFloor84 - mHeightOffset74);
            if (AbsF(mVel80) < 0.5f)
            {
                mHeightOffset74 = mFloor84;
                mBounce88 = 0;
            }
        }
    }
}

void KeyPickup::OnCollected(Player *player)
{
    player->AddKey();
}

HealthPickup::HealthPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("healthpickup"))
{
}

void HealthPickup::OnCollected(Player *player)
{
    player->AddHealth(mDef70->field_0x90);
}

ScooterPickup::ScooterPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("scooterpickup"))
{
    mScooterId = info->mParam10;
}

void ScooterPickup::OnCollected(Player *player)
{
    player->AddScooter(mScooterId);
}

BGMPickup::BGMPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("bgmpickup"))
{
    mBGMId = info->mParam10;
}

void BGMPickup::OnCollected(Player *player)
{
    player->AddBGM(mBGMId);
}

TransmitterPickup::TransmitterPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("transmitterpickup"))
{
}

void TransmitterPickup::OnCollected(Player *)
{
}

SpeedPickup::SpeedPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("speedpickup"))
{
}

void SpeedPickup::OnCollected(Player *player)
{
    PickupDef *def = mDef70;
    player->AddSpeedBoost(def->field_0x8C, def->field_0x90);
}

SpinPickup::SpinPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("spinpickup"))
{
}

void SpinPickup::OnCollected(Player *player)
{
    PickupDef *def = mDef70;
    player->AddSpinBoost(def->field_0x8C, def->field_0x90);
}

JumpPickup::JumpPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("jumppickup"))
{
}

void JumpPickup::OnCollected(Player *player)
{
    PickupDef *def = mDef70;
    player->AddJumpBoost(def->field_0x8C, def->field_0x90);
}

BalancePickup::BalancePickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("balancepickup"))
{
}

void BalancePickup::OnCollected(Player *player)
{
    PickupDef *def = mDef70;
    player->AddBalanceBoost(def->field_0x8C, def->field_0x90);
}

TimerPickup::TimerPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("timerpickup"))
{
}

void TimerPickup::OnCollected(Player *)
{
    SendScriptEvent(HashStringCRC32("add_time"), 0, &mDef70->field_0x8C);
}

void PickupDef::func_0011CAD0(const char *name)
{
    func_00231F08(mName00, name, 0x3F);
    field_0x5C = 0;
    field_0x60 = 0;
    for (int i = 0; i < 5; i++)
    {
        field_0x64[i] = 0;
        field_0x78[i] = 0;
    }
    field_0x40 = 0;
    for (int j = 4; j >= 0; j--)
        field_0x44[j] = 0;
    field_0x9C = 0;
    field_0x58 = 0;
    field_0x90 = 0.0f;
    field_0x94 = 0;
    field_0x98 = 0;
    field_0x8C = 10.0f;
}

// Collision callback of pickups (DD_CollisionCallback; its address sits in a data table).
void func_0011CEB8(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Pickup *pickup = (Pickup *)self->mActorA8;
    Player *player = (Player *)other->mActorA8;
    if ((u32)pickup->mState60 < 2)
    {
        pickup->OnCollected(player);
        pickup->func_0011B7B8();
    }
}

void Pickup::func_0011CC90(int enable)
{
    for (int i = 0; i < mCount34; i++)
    {
        if (enable)
        {
            if (mArray3C[i] == 0)
                mArray3C[i] = func_00194DE0(mDef70->field_0x64[i]);
            if (mArray3C[i] != 0)
            {
                func_00194F40(mArray3C[i]);
                mArray3C[i]->field_0x70 = mArray3C[i]->field_0x10->field_0x4C;
            }
        }
        else if (mArray3C[i] != 0)
        {
            func_00194F90(mArray3C[i]);
        }
    }
}

// Has to be a separate inline function taking the pickup: written in place, GCC schedules the
// mDef70 reload after the constructor's this, and the registers differ from the game.
static inline void SpawnCollectEffect(Pickup *p)
{
    if (p->mDef70->field_0x9C != 0)
        (new UnkEffect(p->mDef70->field_0x9C, &p->mPos44, 0, 20.0f, 1.0f, 1.0f))->func_001419A0(1);
}

void Pickup::func_0011B7B8()
{
    if (mState60 == 4 || mState60 == 2)
        return;
    if (mCallback68 != 0)
        mCallback68(mCallbackArg6C);
    mState60 = 2;
    mField64 = 0;
    func_0011CD80(1);
    SpawnCollectEffect(this);
}
