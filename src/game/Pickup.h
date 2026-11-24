#ifndef GAME_PICKUP_H
#define GAME_PICKUP_H

#include "common/types.h"
#include "game/Player.h"

// Whirl Tour: EnvObj, Pickup and its 10 subclasses (all RTTI class names).
// Note: in EnvObj, the vtable pointer is at offset +0x7C (after 0x7C bytes of non-polymorphic
// base data), as proven by every Pickup constructor and destructor storing the vtable at 0x7C($this).
class EnvObjBaseData
{
public:
    void *mField00;          // 0x00
    char field_0x04[0x14];
    void *mPhysicsObj;       // 0x18
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

class EnvObj : public EnvObjBaseData
{
public:
    virtual ~EnvObj();
};

class Pickup : public EnvObj
{
public:
    Pickup();
    virtual ~Pickup();
    virtual void Update(f32 dt);
    virtual void OnCollected(Player *player);

    Vec3f *GetPos44();                // 0x0011CE90
    Vec3f *GetPos50();                // 0x0011CE98
    int IsState4();                   // 0x0011CEA0
    void SetFields68_6C(int a, int b); // 0x0011CF08
};

class KeyPickup : public Pickup
{
public:
    virtual ~KeyPickup();
    virtual void Update(f32 dt);
    virtual void OnCollected(Player *player);

    f32 mVel80;    // 0x80
    f32 mFloor84;  // 0x84
    int mBounce88; // 0x88
};

class HealthPickup : public Pickup
{
public:
    virtual ~HealthPickup();
    virtual void OnCollected(Player *player);
};

class ScooterPickup : public Pickup
{
public:
    virtual ~ScooterPickup();
    virtual void OnCollected(Player *player);

    int mScooterId; // 0x80
};

class BGMPickup : public Pickup
{
public:
    virtual ~BGMPickup();
    virtual void OnCollected(Player *player);

    int mBGMId; // 0x80
};

class TransmitterPickup : public Pickup
{
public:
    virtual ~TransmitterPickup();
    virtual void OnCollected(Player *player);
};

class SpeedPickup : public Pickup
{
public:
    virtual ~SpeedPickup();
    virtual void OnCollected(Player *player);
};

class SpinPickup : public Pickup
{
public:
    virtual ~SpinPickup();
    virtual void OnCollected(Player *player);
};

class JumpPickup : public Pickup
{
public:
    virtual ~JumpPickup();
    virtual void OnCollected(Player *player);
};

class BalancePickup : public Pickup
{
public:
    virtual ~BalancePickup();
    virtual void OnCollected(Player *player);
};

class TimerPickup : public Pickup
{
public:
    virtual ~TimerPickup();
    virtual void OnCollected(Player *player);
};

#endif
