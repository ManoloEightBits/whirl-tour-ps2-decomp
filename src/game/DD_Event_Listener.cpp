#include "game/CollisionListeners.h"

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

int IVP_Listener_Collision::get_enabled_callbacks()
{
    return mEnableBits00;
}

IVP_Listener_Collision::IVP_Listener_Collision(int enable_bits)
{
    mEnableBits00 = enable_bits;
}

void IVP_Listener_Collision::event_pre_collision(IVP_Event_Collision *)
{
}

void IVP_Listener_Collision::event_post_collision(IVP_Event_Collision *)
{
}

void IVP_Listener_Collision::event_collision_object_deleted(void *)
{
}

void IVP_Listener_Collision::event_friction_created(IVP_Friction_Info *)
{
}
