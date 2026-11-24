#ifndef GAME_COLLISION_LISTENERS_H
#define GAME_COLLISION_LISTENERS_H

#include "common/types.h"

// Whirl Tour: IVP_Listener_Object, IVP_Listener_Collision, DD_Event_Listener, DD_Collision_Listener,
// AI_PedestrianCL, MBCL, ScootCL, LunActCL, MarActCL
// (all RTTI class names recovered from SLUS_204.89).

struct IVP_Real_Object_Stub;
struct IVP_Event_Collision;

typedef void (*DD_CollisionCallback)(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32 mask,
                                     IVP_Event_Collision *ev);

// One collision reaction of an actor (0x10 bytes), run by DD_Collision_Listener.
struct DD_CollisionEntry
{
    u32 mMask00;                     // 0x00: matched against the collision mask
    DD_CollisionCallback mCallback04; // 0x04
    int field_0x08;
    void *mObj0C;                    // 0x0C: passed to func_00126708(obj, 0)
};

struct DD_ActorData
{
    char field_0x00[0x6D];
    u8 mNumEntries6D;                 // 0x6D
    char field_0x6E[0x1A];
    DD_CollisionEntry mEntries88[1];  // 0x88: mNumEntries6D entries
};

struct UnkActorRef
{
    char field_0x00[0x10];
    int field_0x10; // copied to LunAct::field_0x3C
};

struct DD_ActorInfo
{
    int mField00;
    u32 mFlags04;           // 0x04
    DD_ActorData *mData08;  // 0x08
    UnkActorRef *field_0x0C;

    // The do { } while (0) wrapper (probably a macro in the original source) is required:
    // without it GCC keeps the actor in $v1 instead of $a0 and drops the nop before the
    // return in event_object_revived.
    inline void OnRevived()
    {
        do
        {
            if (mFlags04 & 8)
                mFlags04 |= 0x10;
        } while (0);
    }

    inline void OnFrozen()
    {
        do
        {
            if (mFlags04 & 8)
                mFlags04 &= ~0x10;
        } while (0);
    }
};

struct IVP_Real_Object_Stub
{
    char field_0x00[0x88];
    u32 mFlags88;           // 0x88: collision type bits (MarActCL tests 0x800 and 0x400)
    u32 mMask8C;            // 0x8C: types this object reacts to (DD_Collision_Listener)
    char field_0x90[0x18];
    DD_ActorInfo *mActorA8; // 0xA8
};

struct IVP_Event_Object
{
    void *mEnvironment00;           // 0x00
    IVP_Real_Object_Stub *mObj04;   // 0x04
};

class IVP_Listener_Object
{
public:
    virtual void event_object_deleted(IVP_Event_Object *) = 0;  // slot 1
    virtual void event_object_created(IVP_Event_Object *) = 0;  // slot 2
    virtual void event_object_revived(IVP_Event_Object *) = 0;  // slot 3
    virtual void event_object_frozen(IVP_Event_Object *) = 0;   // slot 4
    inline virtual ~IVP_Listener_Object() {}                    // slot 5: 0x001F6E98
};

class DD_Event_Listener : public IVP_Listener_Object
{
public:
    virtual void event_object_deleted(IVP_Event_Object *);      // slot 1: 0x001173A8
    virtual void event_object_created(IVP_Event_Object *);      // slot 2: 0x001173B0
    virtual void event_object_revived(IVP_Event_Object *);      // slot 3: 0x00117340
    virtual void event_object_frozen(IVP_Event_Object *);       // slot 4: 0x00117370
};

struct IVP_U_Float_Point
{
    f32 k[3];

    f32 func_00208178(); // 0x00208178 (IVP code; LunActCL clamps it to 1, probably the length)

    inline void set_negative(const IVP_U_Float_Point *p)
    {
        k[0] = -p->k[0];
        k[1] = -p->k[1];
        k[2] = -p->k[2];
    }

    inline void set_elems(f32 a, f32 b, f32 c)
    {
        k[0] = a;
        k[1] = b;
        k[2] = c;
    }
};

struct IVP_Contact_Situation
{
    IVP_U_Float_Point mNormal00; // 0x00
    char field_0x0C[4];
    IVP_U_Float_Point mPoint10;  // 0x10
    char field_0x1C[4];
    IVP_U_Float_Point msurf20;   // 0x20
    char field_0x2C[4];
    IVP_Real_Object_Stub *mObjects30[2]; // 0x30: the two colliding objects
};

struct IVP_Friction_Info
{
    int mField00;
    IVP_Contact_Situation *mContact04; // 0x04
};

struct IVP_Event_Collision
{
    int mField00;
    int mField04;
    IVP_Contact_Situation *mContact08; // 0x08
};

class IVP_Listener_Collision
{
public:
    int mEnableBits00; // 0x00 (before _vptr at +0x04!)

    int get_enabled_callbacks(); // 0x001F6F08
#ifdef IVP_LISTENER_COLLISION_OUT_OF_LINE
    // The IVP library has an out-of-line copy of the constructor (0x001F6F10, emitted by
    // IVP_Listener_Collision.cpp), while game code inlines it (MBCL passes 3, ScootCL 7, MarActCL and
    // DD_Collision_Listener the default 1).
    IVP_Listener_Collision(int enable_bits = 1);
#else
    IVP_Listener_Collision(int enable_bits = 1) { mEnableBits00 = enable_bits; }
#endif

    virtual void event_pre_collision(IVP_Event_Collision *);              // slot 1: 0x001F73D8
    virtual void event_post_collision(IVP_Event_Collision *);             // slot 2: 0x001F73E0
    virtual void event_collision_object_deleted(void *);                  // slot 3: 0x001F73E8
    virtual void event_friction_created(IVP_Friction_Info *);             // slot 4: 0x001F73F0
    inline virtual ~IVP_Listener_Collision() {}                           // slot 5: 0x001F6F28
};

class DD_Collision_Listener : public IVP_Listener_Collision
{
public:
    // No constructor of its own: the implicit one is inlined at 0x00115AB0. An explicit inline one
    // would be emitted in this class's key-function TU, and the game has no such copy.
    virtual void event_pre_collision(IVP_Event_Collision *);  // slot 1: 0x00116C80
    virtual void event_post_collision(IVP_Event_Collision *); // slot 2: 0x00117718
};

class AI_PedestrianCL : public IVP_Listener_Collision
{
public:
    AI_PedestrianCL(IVP_Real_Object_Stub *obj); // inlined at 0x00103930 (enable bits 3); not decompiled yet
    virtual void event_pre_collision(IVP_Event_Collision *);  // slot 1: 0x00106820
    virtual void event_post_collision(IVP_Event_Collision *); // slot 2: 0x001068E0

    IVP_Real_Object_Stub *mObj08; // 0x08: the pedestrian's own object
    IVP_U_Float_Point mNormal0C;  // 0x0C: contact normal pointing away from the other object
    DD_ActorData *mData18;        // 0x18: actor data of the object it touched
};

class MBCL : public IVP_Listener_Collision
{
public:
    MBCL(void *owner); // inlined at 0x0015F7AC (enable bits 3); not decompiled yet
    virtual void event_pre_collision(IVP_Event_Collision *);  // slot 1: 0x001616A0
    virtual void event_post_collision(IVP_Event_Collision *); // slot 2: 0x001616D0

    void *mOwner08;              // 0x08
    IVP_U_Float_Point mNormal0C; // 0x0C
    u32 mFlags18;                // 0x18
};

class ScootCL : public IVP_Listener_Collision
{
public:
    ScootCL(void *obj); // inlined at 0x00171534 (enable bits 7); not decompiled yet
    virtual void event_pre_collision(IVP_Event_Collision *);     // slot 1: 0x0017DFC8
    virtual void event_post_collision(IVP_Event_Collision *);    // slot 2: 0x0017E0A8
    virtual void event_collision_object_deleted(void *);         // slot 3: 0x0017E028
    virtual void event_friction_created(IVP_Friction_Info *);    // slot 4: 0x0017E0A0

    void *mObj08;                 // 0x08
    u32 mFlags0C;                 // 0x0C
    IVP_U_Float_Point mPoint10;   // 0x10
    IVP_U_Float_Point mSurf1C;    // 0x1C
    IVP_U_Float_Point mNormal28;  // 0x28
    IVP_U_Float_Point mFricPos34; // 0x34
    IVP_U_Float_Point mFricDir40; // 0x40
};

// Class of the getters at 0x0014CAE8..0x0014CB80; no RTTI, name unknown.
struct UnkBody
{
    IVP_Real_Object_Stub *func_0014CB80(); // returns field 0x70
};

// Owner of a MarActCL (name inferred from the listener's RTTI name; no RTTI of its own).
struct MarAct
{
    int field_0x00;
    u32 mFlags04;      // 0x04: MarActCL sets bit 0 or bit 1
    UnkBody *mBody08;  // 0x08
};

// Owner of a LunActCL (name inferred from the listener's RTTI name; no RTTI of its own).
struct LunAct
{
    int field_0x00;
    u32 mFlags04;      // 0x04: LunActCL sets bit 0 or bit 1
    UnkBody *mBody08;  // 0x08
    char pad_0x0C[0x14];
    f32 field_0x20;    // kept in 0..1 by LunActCL
    char pad_0x24[0x18];
    int field_0x3C;
    char pad_0x40[0x8C];
    f32 field_0xCC;    // LunActCL sets 2.0
};

class LunActCL : public IVP_Listener_Collision
{
public:
    virtual void event_pre_collision(IVP_Event_Collision *); // slot 1: 0x001463A8

    LunAct *mOwner08; // 0x08
};

class MarActCL : public IVP_Listener_Collision
{
public:
    MarActCL(MarAct *owner);                                 // 0x0014BC00
    virtual void event_pre_collision(IVP_Event_Collision *); // slot 1: 0x0014BC20

    MarAct *mOwner08; // 0x08
};

#endif
