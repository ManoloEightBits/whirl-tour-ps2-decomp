#ifndef GAME_AI_BOSS_H
#define GAME_AI_BOSS_H

#include "common/types.h"

// The actor of a boss attack ("player_hit_bossattack"): +0x10 is what the attack does to the
// Scooter it hits.
struct UnkAttackActor
{
    char field_0x00[0x10];
    f32 mField10; // 0x10
};

// Only what code outside the AI translation units uses so far. _vptr is at +0x9C (map_tus.py), so
// the data comes before the first virtual function (g++ 2.95 puts _vptr after it). Slot
// addresses are those of the AI_Boss vtable (0x002A3620); which class introduces each is unknown.
class AI_Agent
{
public:
    char field_0x00[0x9C];

    virtual void VirtSlot1();   // 0x00159B48
    virtual void VirtSlot2();   // 0x00159CB0
    virtual void VirtSlot3();   // 0x0015EE28
    virtual void VirtSlot4();   // 0x0015DC90
    virtual Vec3f *VirtSlot5(); // 0x0015EBB0: a position (player_hit_boss)
    virtual void VirtSlot6();   // 0x0015EBF0
    virtual void VirtSlot7();   // 0x0015EC00
    virtual f32 VirtSlot8();    // 0x0015ECF0: player_hit_boss tests it for <= 0
};

class AI_Boss : public AI_Agent
{
public:
    void func_0015EFB8(f32 amount); // 0x0015EFB8: player_hit_boss passes Player::GetStatFactor()

    char field_0xA0[0x138];
    UnkAttackActor *mAttack1D8; // 0x1D8: its +0x10 goes to Player::Action1722B0 (probably the current attack)
};

#endif
