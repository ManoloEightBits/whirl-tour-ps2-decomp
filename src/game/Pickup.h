#ifndef GAME_PICKUP_H
#define GAME_PICKUP_H

#include "common/types.h"
#include "game/Player.h"

// Whirl Tour: EnvObj, Pickup and its 10 subclasses (all RTTI class names).
// Note: in EnvObj, the vtable pointer is at offset +0x7C (after 0x7C bytes of non-polymorphic
// base data), as proven by every Pickup constructor and destructor storing the vtable at 0x7C($this).
struct PickupSpawnInfo
{
    char field_0x00[0x10];
    int mParam10;     // 0x10 (used by ScooterPickup and BGMPickup for mScooterId / mBGMId)
    int mType14;      // 0x14
    Vec3f mPos18;     // 0x18
};

class EnvObj
{
public:
    void *mField00;          // 0x00
    char field_0x04[0x14];
    void *mPhysicsObj18;     // 0x18
    char field_0x1C[0x18];
    int mCount34;            // 0x34
    int mCount38;            // 0x38
    void **mArray3C;         // 0x3C
    void **mArray40;         // 0x40
    Vec3f mPos44;            // 0x44
    Vec3f mPos50;            // 0x50
    int mField5C;            // 0x5C
    int mState60;            // 0x60
    int mField64;            // 0x64
    int mField68;            // 0x68
    int mField6C;            // 0x6C
    u8 *mPickupData70;       // 0x70
    f32 mHeightOffset74;     // 0x74
    int mField78;            // 0x78
};

class Pickup : public EnvObj
{
public:
    Pickup();
    Pickup(const Vec3f *pos, int type, void *def);   // 0x0011B060
    inline virtual ~Pickup();                        // 0x0011CB58
    virtual void Update(f32 dt);                     // 0x0011B3D8
    inline virtual void OnCollected(Player *player); // 0x0011CEB0

    void Call11B2A0();                // 0x0011CE70
    Vec3f *GetPos44();                // 0x0011CE90
    Vec3f *GetPos50();                // 0x0011CE98
    int IsState4();                   // 0x0011CEA0
    void SetFields68_6C(int a, int b); // 0x0011CF08
};

class KeyPickup : public Pickup
{
public:
    KeyPickup(const Vec3f *pos); // 0x0011B900
    virtual void Update(f32 dt);
    virtual void OnCollected(Player *player);

    f32 mVel80;    // 0x80
    f32 mFloor84;  // 0x84
    int mBounce88; // 0x88
};

class HealthPickup : public Pickup
{
public:
    HealthPickup(PickupSpawnInfo *info); // 0x0011D130
    virtual void OnCollected(Player *player);
};

class ScooterPickup : public Pickup
{
public:
    ScooterPickup(PickupSpawnInfo *info); // 0x0011D1B8
    virtual void OnCollected(Player *player);

    int mScooterId; // 0x80
};

class BGMPickup : public Pickup
{
public:
    BGMPickup(PickupSpawnInfo *info); // 0x0011D248
    virtual void OnCollected(Player *player);

    int mBGMId; // 0x80
};

class TransmitterPickup : public Pickup
{
public:
    TransmitterPickup(PickupSpawnInfo *info); // 0x0011D2D8
    virtual void OnCollected(Player *player);
};

class SpeedPickup : public Pickup
{
public:
    SpeedPickup(PickupSpawnInfo *info); // 0x0011D340
    virtual void OnCollected(Player *player);
};

class SpinPickup : public Pickup
{
public:
    SpinPickup(PickupSpawnInfo *info); // 0x0011D3C8
    virtual void OnCollected(Player *player);
};

class JumpPickup : public Pickup
{
public:
    JumpPickup(PickupSpawnInfo *info); // 0x0011D450
    virtual void OnCollected(Player *player);
};

class BalancePickup : public Pickup
{
public:
    BalancePickup(PickupSpawnInfo *info); // 0x0011D4D8
    virtual void OnCollected(Player *player);
};

class TimerPickup : public Pickup
{
public:
    TimerPickup(PickupSpawnInfo *info); // 0x0011D560
    virtual void OnCollected(Player *player);
};

#endif
