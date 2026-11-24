// IVP library TU (0x001F6EC8..0x001F73F0): out-of-line IVP_Listener_Collision functions. Defining the
// first virtual here also emits its vtable, destructor and __tf, which the game code only calls.
#define IVP_LISTENER_COLLISION_OUT_OF_LINE
#include "game/CollisionListeners.h"

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
