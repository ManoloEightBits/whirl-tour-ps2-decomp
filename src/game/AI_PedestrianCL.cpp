#include "game/CollisionListeners.h"

// Negates the copied contact normal and falls back to straight up when it is steeper than 45 degrees.
// The shape matters for the match: the do/while(0) around the copy (a macro, most likely) puts the
// contact in $v1, and loading `up` before the test gives its temporary $f1.
static inline void FixNormal(IVP_U_Float_Point *n)
{
    n->set_negative(n);
    IVP_U_Float_Point up;
    up.set_elems(0.0f, 1.0f, 0.0f);
    f32 a = up.k[0];
    f32 b = up.k[1];
    f32 c = up.k[2];
    if (n->k[1] < 0.707f)
        n->set_elems(a, b, c);
}

void AI_PedestrianCL::event_pre_collision(IVP_Event_Collision *ev)
{
    IVP_Contact_Situation *c = ev->mContact08;
    do
    {
        mNormal0C.k[0] = c->mNormal00.k[0];
        mNormal0C.k[1] = c->mNormal00.k[1];
        mNormal0C.k[2] = c->mNormal00.k[2];
    } while (0);
    FixNormal(&mNormal0C);
    DD_ActorInfo *actor = (c->mObjects30[0] != mObj08) ? c->mObjects30[0]->mActorA8 : c->mObjects30[1]->mActorA8;
    if (actor != 0)
        mData18 = actor->mData08;
}

void AI_PedestrianCL::event_post_collision(IVP_Event_Collision *)
{
    delete this;
}
