#include "game/CollisionListeners.h"

#define MIN(a, b) ((a) <= (b) ? (a) : (b))

void LunActCL::event_pre_collision(IVP_Event_Collision *ev)
{
    IVP_Real_Object_Stub *mine = mOwner08->mBody08->func_0014CB80();
    IVP_Contact_Situation *c = ev->mContact08;
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
    f32 t = 0.0f;
    if (objs[1]->mFlags88 & 0x10)
    {
        t = ((c->mPoint10.k[1] - 20.0f) >? 0.0f) * (1.0f / 15.0f) <? 1.0f;
        mOwner08->field_0x20 = (mOwner08->field_0x20 + t <? 1.0f) >? 0.0f;
        mOwner08->mFlags04 |= 1;
        DD_ActorInfo *actor = objs[1]->mActorA8;
        if (actor != 0 && actor->field_0x0C != 0)
            mOwner08->field_0x3C = actor->field_0x0C->field_0x10;
    }
    else
    {
        t = MIN(c->mPoint10.func_00208178(), 1.0f);
        mOwner08->field_0x20 = mOwner08->field_0x20 + t * 0.5f <? 1.0f;
        mOwner08->mFlags04 |= 2;
    }
    if (t > 0.0f)
        mOwner08->field_0xCC = 2.0f;
}
