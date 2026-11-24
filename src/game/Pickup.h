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

struct UnkNodeDesc
{
    char pad_0x00[0x4C];
    f32 field_0x4C;
};

// Objects a pickup creates from its definition's ids (functions at 0x00194DE0..0x00194F90).
struct UnkNode
{
    char pad_0x00[0x10];
    UnkNodeDesc *field_0x10;
    char pad_0x14[0x5C];
    f32 field_0x70;
};

UnkNode *func_00194DE0(int id);  // 0x00194DE0
void func_00194F40(UnkNode *);   // 0x00194F40
void func_00194F90(UnkNode *);   // 0x00194F90

// 0x30-byte object spawned at a position (constructor 0x001418E0); also used by func_00116B00.
class UnkEffect
{
public:
    UnkEffect(int id, const Vec3f *pos, int, f32, f32, f32); // 0x001418E0
    void func_001419A0(int);                                 // 0x001419A0

    char pad_0x00[0x30];
};

// Definition data of a pickup type (name from FindPickupDef, 0x00126518).
struct PickupDef
{
    char mName00[0x40];   // 0x00: at most 63 characters are copied
    int field_0x40;
    int field_0x44[5];    // 0x44
    int field_0x58;
    int field_0x5C;
    int field_0x60;
    int field_0x64[5];    // 0x64: ids of the EnvObj::mArray3C nodes
    int field_0x78[5];    // 0x78: ids of the EnvObj::mArray40 nodes
    f32 field_0x8C;       // 10.0 by default; first OnCollected parameter (TimerPickup: time to add)
    f32 field_0x90;       // second OnCollected parameter (HealthPickup: health)
    int field_0x94;
    int field_0x98;
    int field_0x9C;       // id of the UnkEffect spawned when collected (0 = none)

    void func_0011CAD0(const char *name); // resets the definition and sets its name
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
    UnkNode **mArray3C;      // 0x3C: mCount34 entries
    UnkNode **mArray40;      // 0x40: mCount38 entries
    Vec3f mPos44;            // 0x44
    Vec3f mPos50;            // 0x50
    int mField5C;            // 0x5C
    int mState60;            // 0x60
    int mField64;            // 0x64
    void (*mCallback68)(int); // 0x68: called with mCallbackArg6C when the pickup is collected
    int mCallbackArg6C;       // 0x6C
    PickupDef *mDef70;       // 0x70
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
    void SetCallback68(void (*callback)(int), int arg); // 0x0011CF08
    void func_0011B7B8();             // 0x0011B7B8
    void func_0011CC90(int enable);   // 0x0011CC90: starts or stops the mArray3C nodes
    // 0x0011CD80: same for the mArray40 nodes. Inline: func_0011B7B8 has it inlined, and the
    // out-of-line copy comes from this class's key-function TU.
    void func_0011CD80(int enable)
    {
        for (int i = 0; i < mCount38; i++)
        {
            if (enable)
            {
                if (mArray40[i] == 0)
                    mArray40[i] = func_00194DE0(mDef70->field_0x78[i]);
                if (mArray40[i] != 0)
                {
                    func_00194F40(mArray40[i]);
                    mArray40[i]->field_0x70 = mArray40[i]->field_0x10->field_0x4C;
                }
            }
            else if (mArray40[i] != 0)
            {
                func_00194F90(mArray40[i]);
            }
        }
    }
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
