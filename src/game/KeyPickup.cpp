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

void Pickup::SetFields68_6C(int a, int b)
{
    mField68 = a;
    mField6C = b;
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
    player->AddHealth(*(f32 *)(mPickupData70 + 0x90));
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
    u8 *data = mPickupData70;
    player->AddSpeedBoost(*(f32 *)(data + 0x8C), *(f32 *)(data + 0x90));
}

SpinPickup::SpinPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("spinpickup"))
{
}

void SpinPickup::OnCollected(Player *player)
{
    u8 *data = mPickupData70;
    player->AddSpinBoost(*(f32 *)(data + 0x8C), *(f32 *)(data + 0x90));
}

JumpPickup::JumpPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("jumppickup"))
{
}

void JumpPickup::OnCollected(Player *player)
{
    u8 *data = mPickupData70;
    player->AddJumpBoost(*(f32 *)(data + 0x8C), *(f32 *)(data + 0x90));
}

BalancePickup::BalancePickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("balancepickup"))
{
}

void BalancePickup::OnCollected(Player *player)
{
    u8 *data = mPickupData70;
    player->AddBalanceBoost(*(f32 *)(data + 0x8C), *(f32 *)(data + 0x90));
}

TimerPickup::TimerPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mType14, FindPickupDef("timerpickup"))
{
}

void TimerPickup::OnCollected(Player *)
{
    SendScriptEvent(HashStringCRC32("add_time"), 0, mPickupData70 + 0x8C);
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
    field_0x90 = 0;
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
