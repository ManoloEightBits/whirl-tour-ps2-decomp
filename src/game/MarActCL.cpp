#include "game/CollisionListeners.h"

int MarAct::TestFlag100()
{
    return mFlags04 & 0x100;
}

int MarAct::TestFlag200()
{
    return mFlags04 & 0x200;
}

void *MarAct::GetBodyPtr50()
{
    return mBody08->GetPtr50();
}

f32 MarAct::Action14CB50()
{
    return mBody08->func_0014CB50();
}

void MarAct::SetField18(int v)
{
    mField18 = v;
}

int MarAct::GetField1C()
{
    return mField1C;
}

int MarAct::GetField10()
{
    return mField10;
}

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

void *UnkBody::GetPtr50()
{
    return mBlock50;
}

void *UnkBody::GetPtr60()
{
    return mBlock60;
}

f32 UnkBody::func_0014CB50()
{
    return ((IVP_U_Float_Point *)((char *)mObj70->field_0x9C + 0xB0))->func_00208178();
}

void *UnkBody::GetPtr20()
{
    return mBlock20;
}

IVP_Real_Object_Stub *UnkBody::func_0014CB80()
{
    return mObj70;
}
