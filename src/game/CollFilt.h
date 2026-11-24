#ifndef GAME_COLLFILT_H
#define GAME_COLLFILT_H
// Whirl Tour: CollFilt, Papaya's collision filter on top of Ipion's IVP_Collision_Filter.
// Names of the IVP base class come from the open-source IVP SDK; CollFilt's own are ours.
class IVP_Environment;
class IVP_Real_Object;

struct CollGroup
{
    unsigned int mask;   // 0x00
    unsigned int test;   // 0x04
};

int CollGroupsCollide(const CollGroup *a, const CollGroup *b);  // 0x16F058, not yet decompiled

class IVP_Collision_Filter
{
public:
    virtual int check_objects_for_collision_detection(IVP_Real_Object *a, IVP_Real_Object *b) = 0;
    virtual void environment_will_be_deleted(IVP_Environment *env) = 0;
    virtual ~IVP_Collision_Filter();  // out of line: lives in its own translation unit (0x1C6478)
};

class CollFilt : public IVP_Collision_Filter
{
public:
    CollFilt();
    virtual int check_objects_for_collision_detection(IVP_Real_Object *a, IVP_Real_Object *b);
    virtual void environment_will_be_deleted(IVP_Environment *env);
    // no destructor declared: the game's slot 3 is the implicit one, a thunk to the base's
};

#endif
