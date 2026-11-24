#include "game/CollisionListeners.h"

MarActCL::MarActCL(MarAct *owner) : IVP_Listener_Collision(1)
{
    mOwner08 = owner;
}

void MarActCL::event_pre_collision(IVP_Event_Collision *ev)
{
    IVP_Contact_Situation *c = ev->mContact08;
    IVP_Real_Object_Stub *mine = mOwner08->mBody08->func_0014CB80();
    IVP_Real_Object_Stub *objs[2];
    if (c->mObjects30[0] == mine)
    {
        objs[0] = c->mObjects30[0];
        objs[1] = c->mObjects30[1];
    }
    else
    {
        objs[0] = c->mObjects30[1];
        objs[1] = c->mObjects30[0];
    }
    u32 flags = objs[1]->mFlags88;
    if (flags & 0x800)
        mOwner08->mFlags04 |= 1;
    else if (flags & 0x400)
        mOwner08->mFlags04 |= 2;
}
