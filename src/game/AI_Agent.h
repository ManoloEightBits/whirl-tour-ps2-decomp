#ifndef GAME_AI_AGENT_H
#define GAME_AI_AGENT_H

#include "common/types.h"

// Base of AI_Pedestrian, AI_Race, AI_Vehicle and AI_Boss (RTTI: AI_Agent : EnvObj; the EnvObj part is
// still the padding below). _vptr is at +0x9C (map_tus.py): g++ 2.95 puts it after the data of the
// class that introduces the first virtual function. Its vtable (0x002A3098) has __pure_virtual in
// slots 1-7 and its own functions in 8-10: they were inline (emitted once, in the first TU that needed
// them: slot 8 in AI_Pedestrian's, 9 and 10 in AI_Race's, which is why those addresses sit there).
// Slots 5-7 are the agent's matrix: row 3 (the position), row 2 and the whole matrix.
class AI_Agent
{
public:
    char field_0x00[0x20];
    u32 mFlags20;               // 0x20: AI_Race::func_0010BC20 tests 0x2000 and sets 8
    char field_0x24[0x78];

    virtual ~AI_Agent() = 0;            // slot 1
    virtual void VirtSlot2() = 0;       // slot 2
    virtual void VirtSlot3() = 0;       // slot 3
    virtual void VirtSlot4() = 0;       // slot 4
    virtual Vec3f *GetPosition() = 0;   // slot 5: matrix row 3 (player_hit_boss uses the boss's)
    virtual Vec4f *GetRow2() = 0;       // slot 6: matrix row 2
    virtual Mat4x4f *GetMatrix() = 0;   // slot 7
    void func_0010B198();               // 0x0010B198 (non-virtual; AI_Race::Action10B198 calls it)

    virtual f32 VirtSlot8() { return 0.0f; } // slot 8, 0x00106568 (AI_Boss: mField138, tested <= 0 by player_hit_boss)
    virtual void VirtSlot9() {}              // slot 9, 0x0010B910
    virtual void VirtSlot10() {}             // slot 10, 0x0010B918
};

#endif
