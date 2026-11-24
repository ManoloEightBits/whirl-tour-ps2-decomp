#include "game/CollisionListeners.h"

void ScootCL::event_pre_collision(IVP_Event_Collision *ev)
{
    IVP_Contact_Situation *c = ev->mContact08;
    mNormal28.k[0] = c->mNormal00.k[0];
    mNormal28.k[1] = c->mNormal00.k[1];
    mNormal28.k[2] = c->mNormal00.k[2];
    mSurf1C.k[0] = c->msurf20.k[0];
    mSurf1C.k[1] = c->msurf20.k[1];
    mSurf1C.k[2] = c->msurf20.k[2];
    mPoint10.k[0] = c->mPoint10.k[0];
    mPoint10.k[1] = c->mPoint10.k[1];
    mPoint10.k[2] = c->mPoint10.k[2];
    asm("");
    mFlags0C |= 1;
}

void ScootCL::event_collision_object_deleted(void *arg)
{
    IVP_Friction_Info *ev = (IVP_Friction_Info *)arg;
    IVP_Contact_Situation *c = ev->mContact04;
    // Both pointers are read before the vector copies: the game loads them first.
    void *mine = mObj08;
    void *other = c->mObjects30[0];
    mFricPos34.set_elems(c->msurf20.k[0], c->msurf20.k[1], c->msurf20.k[2]);
    mFricDir40.set_elems(c->mNormal00.k[0], c->mNormal00.k[1], c->mNormal00.k[2]);
    if (mine == other)
    {
        mFricDir40.set_negative(&mFricDir40);
    }
}

void ScootCL::event_friction_created(IVP_Friction_Info *)
{
}

void ScootCL::event_post_collision(IVP_Event_Collision *)
{
    delete this;
}
