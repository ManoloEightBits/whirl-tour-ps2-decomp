#include "game/CollFilt.h"

struct IVP_Real_Object_Layout
{
    char pad[0x88];
    CollGroup group;  // 0x88
};

CollFilt::CollFilt()
{
}

int CollFilt::check_objects_for_collision_detection(IVP_Real_Object *a, IVP_Real_Object *b)
{
    return CollGroupsCollide(&((IVP_Real_Object_Layout *)a)->group, &((IVP_Real_Object_Layout *)b)->group);
}

void CollFilt::environment_will_be_deleted(IVP_Environment *)
{
    delete this;
}
