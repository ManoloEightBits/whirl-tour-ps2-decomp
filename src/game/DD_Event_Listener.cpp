// Game TU at 0x00116B00..0x00117720: DD_Collision_Listener and DD_Event_Listener.
#include "game/CollisionListeners.h"

void func_00126708(void *obj, int);                                                   // 0x00126708
void func_00116B00(IVP_Real_Object_Stub *, IVP_Real_Object_Stub *, IVP_Event_Collision *); // 0x00116B00

static inline void RunCollisionEntries(IVP_Real_Object_Stub *a, IVP_Real_Object_Stub *b, IVP_Event_Collision *ev)
{
    u32 mask = a->mMask8C & b->mFlags88;
    if (mask == 0)
        return;
    DD_ActorInfo *actor = a->mActorA8;
    if (actor == 0)
        return;
    if (actor->mData08 == 0)
        return;
    DD_CollisionEntry *e = actor->mData08->mEntries88;
    for (u32 i = 0; i < actor->mData08->mNumEntries6D; i++, e++)
    {
        if (e->mCallback04 && (e->mMask00 & mask))
            e->mCallback04(a, b, e->mMask00, ev);
        if (e->mObj0C && (e->mMask00 & mask))
            func_00126708(e->mObj0C, 0);
    }
}

void DD_Collision_Listener::event_pre_collision(IVP_Event_Collision *ev)
{
    IVP_Contact_Situation *c = ev->mContact08;
    RunCollisionEntries(c->mObjects30[0], c->mObjects30[1], ev);
    RunCollisionEntries(c->mObjects30[1], c->mObjects30[0], ev);
    func_00116B00(c->mObjects30[0], c->mObjects30[1], ev);
    func_00116B00(c->mObjects30[1], c->mObjects30[0], ev);
}

void DD_Collision_Listener::event_post_collision(IVP_Event_Collision *)
{
}

void DD_Event_Listener::event_object_revived(IVP_Event_Object *ev)
{
    DD_ActorInfo *actor = ev->mObj04->mActorA8;
    if (actor != 0)
        actor->OnRevived();
}

void DD_Event_Listener::event_object_frozen(IVP_Event_Object *ev)
{
    DD_ActorInfo *actor = ev->mObj04->mActorA8;
    if (actor != 0)
        actor->OnFrozen();
}

void DD_Event_Listener::event_object_deleted(IVP_Event_Object *)
{
}

void DD_Event_Listener::event_object_created(IVP_Event_Object *)
{
}
