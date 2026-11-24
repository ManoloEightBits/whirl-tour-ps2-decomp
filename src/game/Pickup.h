#ifndef GAME_PICKUP_H
#define GAME_PICKUP_H

#include "common/types.h"
#include "game/Player.h"
#include "game/UnkEffect.h"

// Whirl Tour: EnvObj, Pickup and its 10 subclasses (all RTTI class names).
// Note: in EnvObj, the vtable pointer is at offset +0x7C (after 0x7C bytes of non-polymorphic
// base data), as proven by every Pickup constructor and destructor storing the vtable at 0x7C($this).
// Object definition passed to Pickup's constructor (a pickup type's own one, or FindPickupDef("objkey")).
struct UnkObjDef
{
    char pad_0x00[0x3C];
    f32 field_0x3C; // copied to EnvObj::mField5C
};

struct PickupSpawnInfo
{
    char field_0x00[0x10];
    int mParam10;     // 0x10 (used by ScooterPickup and BGMPickup for mScooterId / mBGMId)
    UnkObjDef *mObjDef14; // 0x14
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

// A keyword of UnkParser::func_001C1D28's table; the parser sets mToken14 to the matching mId00.
struct UnkKeyword
{
    int mId00;
    const char *mName04;
};

// Script parser used by many loaders (no RTTI; name unknown).
struct UnkParser
{
    char field_0x0000[0x14];
    int mToken14;               // 0x14: id of the last keyword read
    char field_0x0018[0x1014];
    int mEof102C;               // 0x102C: nonzero at the end of the input

    void func_001C1D28(const UnkKeyword *keywords); // 0x001C1D28: reads the next keyword
    void func_001C2C10();                           // 0x001C2C10: skips an unknown keyword
    // 0x001C2C78: reads a string value. It returns something: with void, PickupDef::func_0011AD28
    // gets $v0 instead of $v1 for a value it loads right after the call.
    int func_001C2C78(const char *key, char *out);
    void func_001C3270(const char *key, f32 *out);  // 0x001C3270: reads a float value
};

// Definition data of a pickup type (name from FindPickupDef, 0x00126518).
struct PickupDef
{
    // Field names are the keys of a "pickup" block (see func_0011AD28).
    char mName00[0x40];          // 0x00: at most 63 characters are copied
    int mNumMeshes40;            // 0x40
    u32 mMeshes44[5];            // 0x44: CRC32s of the "mesh" names (models)
    u32 mIcs58;                  // 0x58: CRC32 of the "ics" name; passed to func_001262B0
    int mNumCreation5C;          // 0x5C: number of mCreation64 entries (EnvObj::mArray3C nodes)
    int mNumDestruction60;       // 0x60: number of mDestruction78 entries (EnvObj::mArray40 nodes)
    int mCreation64[5];          // 0x64: "fountain"s of the "fountains type creation" block
    int mDestruction78[5];       // 0x78: "fountain"s of the "fountains type destruction" block
    f32 mTimeLimit8C;            // 0x8C: "timelimit" (10.0 by default); first OnCollected parameter
    f32 mParam1_90;              // 0x90: "param1"; second OnCollected parameter (HealthPickup: health)
    f32 mRegenerate94;           // 0x94: "regenerate"; copied to EnvObj::mField78
    f32 mRegenDelta98;           // 0x98: "regendelta"
    u32 mSound9C;                // 0x9C: CRC32 of the "sound" name, played when collected (0 = none)

    void func_0011AD28(char *name, UnkParser *p); // reads a "pickup" block (name: buffer for the name)
    void func_0011CAD0(const char *name); // resets the definition and sets its name
};

class EnvObj
{
public:
    void *mField00;          // 0x00
    char field_0x04[0x14];
    void *mPhysicsObj18;     // 0x18
    int mCount1C;            // 0x1C: models drawn by PickupHelper11B2A0
    void *mArray20[5];       // 0x20
    int mCount34;            // 0x34
    int mCount38;            // 0x38
    UnkNode **mArray3C;      // 0x3C: mCount34 entries
    UnkNode **mArray40;      // 0x40: mCount38 entries
    Vec3f mPos44;            // 0x44
    Vec3f mPos50;            // 0x50
    f32 mField5C;            // 0x5C
    int mState60;            // 0x60
    int mField64;            // 0x64
    void (*mCallback68)(int); // 0x68: called with mCallbackArg6C when the pickup is collected
    int mCallbackArg6C;       // 0x6C
    PickupDef *mDef70;       // 0x70
    f32 mHeightOffset74;     // 0x74
    f32 mField78;            // 0x78
};

class Pickup : public EnvObj
{
public:
    Pickup();
    Pickup(const Vec3f *pos, UnkObjDef *objDef, PickupDef *def); // 0x0011B060
    inline virtual ~Pickup();                        // 0x0011CB58
    virtual void Update(f32 dt);                     // 0x0011B3D8
    inline virtual void OnCollected(Player *player); // 0x0011CEB0

    void Call11B2A0();                // 0x0011CE70
    Vec3f *GetPos44();                // 0x0011CE90
    Vec3f *GetPos50();                // 0x0011CE98
    int IsState4();                   // 0x0011CEA0
    void SetCallback68(void (*callback)(int), int arg); // 0x0011CF08
    void func_0011B7B8();             // 0x0011B7B8
    inline void func_0011CC90(int enable); // 0x0011CC90: starts or stops the mArray3C nodes (defined in KeyPickup.cpp after the constructor)
    inline void func_0011CD80(int enable); // 0x0011CD80: same for the mArray40 nodes (defined in KeyPickup.cpp after the constructor)
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
