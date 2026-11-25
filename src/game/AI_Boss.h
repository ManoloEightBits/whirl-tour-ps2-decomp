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

// What AI_Boss+0x1E0 points to: an object with a 4x4 matrix at +0x50, whose rows the boss returns (as
// AI_Race does for its Player's matrix). No RTTI; the name is ours.
struct UnkBossObj1E0
{
    char field_0x00[0x50];
    Mat4x4f mMatrix50; // 0x50
};

// Boss settings: the boss script's keys, read by the parser 0x0015DD70 (keyword table 0x00262398:
// properties, talking, view, lookatsettings, states, distancereach, distancesearch, ...) into a buffer
// of the level loader 0x0012BBB0, which copies it into a 0x20C-byte heap object. Field names are the
// keys (tools/analysis/keyword_fields.py); the gaps hold values read through other buffers (attack,
// sounds, movement, the per-state probabilities). Not used by matched code yet. +0x10 is the collision
// damage; AI_Boss::mAttack1D8 points to something whose +0x10 is the damage dealt to the player, so it
// may be this object (unchecked).
struct UnkBossParams
{
    char field_0x00[0xC];
    f32 mWeakness0C;        // 0x0C "weakness"
    f32 mCollisionDamage10; // 0x10 "collisiondamage"
    char field_0x14[0x8];
    f32 mRange1C;           // 0x1C "range"
    f32 mWall20;            // 0x20 "wall"
    f32 mLookAt24;          // 0x24 "lookat"
    f32 mBodyToHeadTurn28;  // 0x28 "bodytoheadturn"
    char field_0x2C[0x4];
    f32 mHearRange30;       // 0x30 "hearrange"
    f32 mMinApproach34;     // 0x34 "minapproach"
    f32 mMaxApproach38;     // 0x38 "maxapproach"
    f32 mMinPercentage3C;   // 0x3C "minpercentage"
    f32 mMaxRandChange40;   // 0x40 "maxrandchange"
    f32 mTurnThreshold44;   // 0x44 "turnthreshold"
    f32 mRadius48;          // 0x48 "radius" (distancereach or distancesearch section, unchecked)
    f32 mRadius4C;          // 0x4C "radius" (the other one)
    char field_0x50[0x8];
    f32 mInvTime58;         // 0x58 "invtime"
    char field_0x5C[0x18C];
    f32 mProbability1E8;    // 0x1E8 "probability"
    f32 mInterval1EC;       // 0x1EC "interval"
    char field_0x1F0[0x1C];
};
STATIC_ASSERT(sizeof(UnkBossParams) == 0x20C, UnkBossParams_size);

// RTTI: AI_Boss : AI_Agent (_vptr at +0x9C). Its __tf is still the generated stub in src/rtti/; the
// accessors after it (0x0015E9B8..0x0015EE0F) were drafted with tools/analysis/gen_accessors.py.
class AI_Boss : public AI_Agent
{
public:
    f32 GetAttackField10();         // 0x0015EB78
    Vec4f *GetObj1E0Row3();         // 0x0015EBB0
    void Action161978();            // 0x0015EBC0
    Vec4f *GetObj1E0Row1();         // 0x0015EBE0
    Vec4f *GetObj1E0Row2();         // 0x0015EBF0
    Vec4f *GetObj1E0Row0();         // 0x0015EC00
    f32 GetField138();              // 0x0015ECF0
    void SetBits134(int bits);      // 0x0015EDD0
    void ClearBits134(int bits);    // 0x0015EDE0
    int TestFlags20_200();          // 0x0015EDF8
    void func_0015EFB8(f32 amount); // 0x0015EFB8: player_hit_boss passes Player::GetStatFactor()
    UnkBossObj1E0 *GetObj1E0();       // 0x0015E9B8
    UnkAttackActor *GetField1D8();                  // 0x0015EAF0
    int GetField1DC();                  // 0x0015EAF8
    int GetField188();                  // 0x0015EB88
    int GetField18C();                  // 0x0015EB90
    void SetField18C(int v);            // 0x0015EB98
    int GetField190();                  // 0x0015EBA0
    void SetField190(int v);            // 0x0015EBA8
    int *GetPtr174();                   // 0x0015EC38
    f32 GetField180();                  // 0x0015EC60
    void SetField180(f32 v);            // 0x0015EC68
    f32 GetField184();                  // 0x0015EC70
    void SetField184(f32 v);            // 0x0015EC78
    void AddField184(f32 v);            // 0x0015EC80
    u8 GetField13C();                   // 0x0015EC90
    void SetField13C(u8 v);             // 0x0015EC98
    int GetField15C();                  // 0x0015ECA0
    int GetField158();                  // 0x0015ECA8
    int *GetPtrB0();                    // 0x0015ECB0
    int *GetPtrF0();                    // 0x0015ECB8
    int *GetPtrE0();                    // 0x0015ECC0
    int GetField1E4();                  // 0x0015ECC8
    int GetField130();                  // 0x0015ECD0
    int GetField160();                  // 0x0015ECD8
    u8 GetField13D();                   // 0x0015ECE0
    void SetField13D(u8 v);             // 0x0015ECE8
    void SetField138(f32 v);            // 0x0015ECF8
    f32 GetField164();                  // 0x0015ED28
    void SetField164(f32 v);            // 0x0015ED30
    void AddField164(f32 v);            // 0x0015ED38
    f32 GetField168();                  // 0x0015ED48
    void SetField168(f32 v);            // 0x0015ED50
    void AddField168(f32 v);            // 0x0015ED58
    f32 GetField16C();                  // 0x0015ED68
    void SetField16C(f32 v);            // 0x0015ED70
    void AddField16C(f32 v);            // 0x0015ED78
    f32 GetField170();                  // 0x0015ED88
    void SetField170(f32 v);            // 0x0015ED90
    int GetField134();                  // 0x0015EDC8
    int GetField1F0();                  // 0x0015EE08

    char field_0xA0[0x10];
    int mFieldB0;             // 0xB0
    char field_0xB4[0x2C];
    int mFieldE0;             // 0xE0
    char field_0xE4[0xC];
    int mFieldF0;             // 0xF0
    char field_0xF4[0x3C];
    int mField130;            // 0x130
    int mField134;            // 0x134
    f32 mField138;            // 0x138
    u8 mField13C;             // 0x13C
    u8 mField13D;             // 0x13D
    char field_0x13E[0x1A];
    int mField158;            // 0x158
    int mField15C;            // 0x15C
    int mField160;            // 0x160
    f32 mField164;            // 0x164
    f32 mField168;            // 0x168
    f32 mField16C;            // 0x16C
    f32 mField170;            // 0x170
    int mField174;            // 0x174
    char field_0x178[0x8];
    f32 mField180;            // 0x180
    f32 mField184;            // 0x184
    int mField188;            // 0x188
    int mField18C;            // 0x18C
    int mField190;            // 0x190
    char field_0x194[0x44];
    UnkAttackActor *mAttack1D8; // 0x1D8: its +0x10 goes to Player::Action1722B0 (probably the current attack)
    int mField1DC;            // 0x1DC
    UnkBossObj1E0 *mObj1E0;   // 0x1E0
    int mField1E4;            // 0x1E4
    char field_0x1E8[0x8];
    int mField1F0;            // 0x1F0
};

#endif
