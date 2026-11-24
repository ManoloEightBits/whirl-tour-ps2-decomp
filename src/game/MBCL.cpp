#include "game/CollisionListeners.h"

void MBCL::event_pre_collision(IVP_Event_Collision *ev)
{
    IVP_Contact_Situation *c = ev->mContact08;
    mNormal0C.k[0] = c->mNormal00.k[0];
    mNormal0C.k[1] = c->mNormal00.k[1];
    mNormal0C.k[2] = c->mNormal00.k[2];
    asm("");
    mFlags18 |= 1;
}

void MBCL::event_post_collision(IVP_Event_Collision *)
{
    delete this;
}
