// Game TU at 0x00116B00..0x00117727: DD_Collision_Listener, Global_Phantom_Listener and DD_Event_Listener.
#include "game/CollisionListeners.h"
#include "game/UnkEffect.h"

void func_00126708(void *obj, int);           // 0x00126708
void func_001F3F30(void *obj, void *a, void *b); // 0x001F3F30 (IVP code; fills b with the object's position)

// Spawns a's hit effects that react to b, when the hit is strong enough.
void func_00116B00(IVP_Real_Object_Stub *a, IVP_Real_Object_Stub *b, IVP_Event_Collision *ev)
{
    f32 strength = 1.0f;
    if (ev != 0)
        strength = ev->mField00;
    DD_ActorInfo *actor = a->mActorA8;
    if (actor == 0)
        return;
    if (strength > 0.75f)
    {
        DD_ActorData *data = actor->mData08;
        f32 sum = a->field_0x9C->field_0x150 + b->field_0x9C->field_0x150;
        for (int i = 0; i < data->mNumHitEffectsF4; i++)
        {
            DD_HitEffect *fx = &data->mHitEffectsF8[i];
            if ((fx->mMask04 & b->mFlags88) && sum >= 2.0f)
            {
                Vec4f pos;
                Vec4f rot;
                func_001F3F30(a, &rot, &pos);
                Vec3f p;
                // The do/while(0) (probably a copy macro, as in AI_PedestrianCL) gives the game's
                // three loads before the three stores, and its argument order for func_001F3F30.
                do
                {
                    p.x = pos.x;
                    p.y = pos.y;
                    p.z = pos.z;
                } while (0);
                UnkEffect *e = new UnkEffect(fx->mId00, &p, 0, data->field_0xF0, 1.0f, 1.0f);
                e->field_0x1C = sum * 0.1f <? 1.0f;
                e->func_001419A0(1);
            }
        }
    }
}

inline void DD_Collision_Listener::func_001173B8(IVP_Real_Object_Stub *a, IVP_Real_Object_Stub *b, u32 mask,
                                                IVP_Event_Collision *ev)
{
    DD_ActorInfo *actor = a->mActorA8;
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

inline void DD_Collision_Listener::func_00117498(IVP_Real_Object_Stub *a, IVP_Real_Object_Stub *b, u32 mask,
                                                IVP_Event_Collision *ev)
{
    DD_ActorInfo *actor = a->mActorA8;
    if (actor->mData08 == 0)
        return;
    DD_CollisionEntry *e = actor->mData08->mEntries88;
    for (u32 i = 0; i < actor->mData08->mNumEntries6D; i++, e++)
    {
        if (e->mCallback08 && (e->mMask00 & mask))
            e->mCallback08(a, b, e->mMask00, ev);
    }
}

inline void DD_Collision_Listener::func_00117550(IVP_Real_Object_Stub *a, IVP_Real_Object_Stub *b,
                                                IVP_Event_Collision *ev)
{
    u32 mask = a->mMask8C & b->mFlags88;
    if (mask == 0)
        return;
    if (a->mActorA8 == 0)
        return;
    func_001173B8(a, b, mask, ev);
}

inline void DD_Collision_Listener::func_00117648(IVP_Real_Object_Stub *a, IVP_Real_Object_Stub *b,
                                                IVP_Event_Collision *ev)
{
    u32 mask = a->mMask8C & b->mFlags88;
    if (mask == 0)
        return;
    if (a->mActorA8 == 0)
        return;
    func_00117498(a, b, mask, ev);
}

void DD_Collision_Listener::event_pre_collision(IVP_Event_Collision *ev)
{
    IVP_Contact_Situation *c = ev->mContact08;
    func_00117550(c->mObjects30[0], c->mObjects30[1], ev);
    func_00117550(c->mObjects30[1], c->mObjects30[0], ev);
    func_00116B00(c->mObjects30[0], c->mObjects30[1], ev);
    func_00116B00(c->mObjects30[1], c->mObjects30[0], ev);
}

void Global_Phantom_Listener::mindist_entered_volume(IVP_Controller_Phantom *ph, IVP_Mindist_Base *md)
{
    IVP_Real_Object_Stub *objs[2];
    md->get_objects(objs);
    // Put the phantom's own object first.
    if (objs[0] != ph->mObject00)
    {
        objs[1] = objs[0];
        objs[0] = ph->mObject00;
    }
    u32 m0 = objs[0]->mMask8C & objs[1]->mFlags88;
    u32 m1 = objs[1]->mMask8C & objs[0]->mFlags88;
    if (m0)
    {
        DD_Collision_Listener::func_00117550(objs[0], objs[1], 0);
        func_00116B00(objs[0], objs[1], 0);
    }
    if (m1 && objs[1]->field_0x1C == 0)
    {
        DD_Collision_Listener::func_00117550(objs[1], objs[0], 0);
        func_00116B00(objs[1], objs[0], 0);
    }
}

void Global_Phantom_Listener::mindist_left_volume(IVP_Controller_Phantom *ph, IVP_Mindist_Base *md)
{
    IVP_Real_Object_Stub *objs[2];
    md->get_objects(objs);
    if (objs[0] != ph->mObject00)
    {
        objs[1] = objs[0];
        objs[0] = ph->mObject00;
    }
    DD_Collision_Listener::func_00117648(objs[0], objs[1], 0);
    if (objs[1]->field_0x1C == 0)
        DD_Collision_Listener::func_00117648(objs[1], objs[0], 0);
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

void Global_Phantom_Listener::phantom_is_going_to_be_deleted_event(IVP_Controller_Phantom *)
{
}
