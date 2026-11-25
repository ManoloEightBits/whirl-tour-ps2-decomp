#ifndef GAME_AI_BOSS_H
#define GAME_AI_BOSS_H

#include "common/types.h"
#include "game/AI_Agent.h"

// The actor of a boss attack ("player_hit_bossattack"): +0x10 is what the attack does to the
// Scooter it hits.
struct UnkAttackActor
{
    char field_0x00[0x10];
    f32 mField10; // 0x10
};

class AI_Boss : public AI_Agent
{
public:
    void func_0015EFB8(f32 amount); // 0x0015EFB8: player_hit_boss passes Player::GetStatFactor()

    char field_0xA0[0x138];
    UnkAttackActor *mAttack1D8; // 0x1D8: its +0x10 goes to Player::Action1722B0 (probably the current attack)
};

#endif
