#ifndef GAME_COLLISION_LISTENERS_H
#define GAME_COLLISION_LISTENERS_H

#include "common/types.h"

// Whirl Tour: IVP_Listener_Object, IVP_Listener_Collision, DD_Event_Listener, MBCL, ScootCL
// (all RTTI class names recovered from SLUS_204.89).

struct DD_ActorInfo
{
    int mField00;
    u32 mFlags04; // 0x04

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
    char field_0x00[0xA8];
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
    void *mObj30;                // 0x30
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
    IVP_Listener_Collision();
    IVP_Listener_Collision(int enable_bits); // 0x001F6F10

    virtual void event_pre_collision(IVP_Event_Collision *);              // slot 1: 0x001F73D8
    virtual void event_post_collision(IVP_Event_Collision *);             // slot 2: 0x001F73E0
    virtual void event_collision_object_deleted(void *);                  // slot 3: 0x001F73E8
    virtual void event_friction_created(IVP_Friction_Info *);             // slot 4: 0x001F73F0
    inline virtual ~IVP_Listener_Collision() {}                           // slot 5: 0x001F6F28
};

class MBCL : public IVP_Listener_Collision
{
public:
    virtual void event_pre_collision(IVP_Event_Collision *);  // slot 1: 0x001616A0
    virtual void event_post_collision(IVP_Event_Collision *); // slot 2: 0x001616D0

    void *mOwner08;              // 0x08
    IVP_U_Float_Point mNormal0C; // 0x0C
    u32 mFlags18;                // 0x18
};

class ScootCL : public IVP_Listener_Collision
{
public:
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

#endif
