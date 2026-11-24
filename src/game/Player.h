#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "common/types.h"
#include "game/Scooter.h"

// Passed to Player::func_001237E8. Its +0x18 is compared with Player+0xB8 to pick one of two position
// pairs; "checkpoint" is a guess.
struct UnkCheckpoint
{
    char field_0x00[0x18];
    int mOrder18;  // 0x18
    Vec3f mVec1C;  // 0x1C
    Vec3f mVec28;  // 0x28
    Vec3f mVec34;  // 0x34
    Vec3f mVec40;  // 0x40
};

// Whirl Tour: the object a pickup is handed when collected. The class name is ours (hypothesis);
// offsets and method shapes are proven by 0x00123438..0x001238B8 and the Pickup subclasses.
class Player
{
public:
    void Action17F328();                         // 0x00123438
    void Action17F500();                         // 0x00123458
    void *GetPtr40();                            // 0x00123478
    void *GetPtr58();                            // 0x00123480
    void AddKey();                               // 0x00123548
    int GetKeys();                               // 0x00123558
    void AddSpeedBoost(f32 amount, f32 dur);     // 0x00123560
    void AddSpinBoost(f32 amount, f32 dur);      // 0x00123580
    void AddJumpBoost(f32 amount, f32 dur);      // 0x001235A0
    void AddBalanceBoost(f32 amount, f32 dur);   // 0x001235C0
    void AddHealth(f32 percent);                 // 0x001235E0
    void AddScooter(int scooterId);              // 0x00123600
    void AddBGM(int bgmId);                      // 0x00123620
    int GetNumBGMs();                            // 0x00123640
    int GetBGM(int index);                       // 0x00123648
    f32 GetStatFactor();                         // 0x00123658
    int IsBoostInactive();                       // 0x00123678
    int IsBoostUnavailable();                    // 0x00123698
    void SetBoostField62C(f32 val);              // 0x001236B8
    void SetBoostField630(f32 val);              // 0x001236D8
    void ApplySpecialAction(int mode);           // 0x001236F8
    void Action1722B0();                         // 0x00123718
    void Action1723F0();                         // 0x00123738
    f32 GetMaxConstant1000();                    // 0x00123758
    int HasAdrenaline();                         // 0x00123768
    f32 ConsumeAdrenaline(f32 amount);           // 0x00123788
    void Action17ECC8(void *arg);                // 0x001237A8
    void Action174198(void *arg);                // 0x001237C8
    void func_001237E8(UnkCheckpoint *cp);       // 0x001237E8
    void EnableFieldD3();                        // 0x00123890
    int GetScooterField500();                    // 0x001238A0

    char field_0x00[0x2C];
    Scooter *mScooter;      // 0x2C
    char field_0x30[0x10];
    char mBlock40[0x18];    // 0x40
    char mBlock58[0x4C];    // 0x58
    int mKeys;              // 0xA4
    int mNumBGMs;           // 0xA8
    int mBGMs[3];           // 0xAC (0xB8 onwards is read by 0x001237E8 as separate fields)
    int mFieldB8;           // 0xB8
    int mFieldBC;           // 0xBC
    Vec3f mVecC0;           // 0xC0..0xCB
    char field_0xCC[7];     // 0xCC..0xD2
    u8 mFieldD3;            // 0xD3
};

#endif
