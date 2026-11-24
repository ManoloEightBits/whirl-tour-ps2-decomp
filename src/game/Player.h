#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "common/types.h"
#include "game/ScootCtrl.h"

// Whirl Tour: the object a pickup is handed when collected. The class name is ours (hypothesis);
// offsets and method shapes are proven by 0x00123548..0x001237A0 and the Pickup subclasses.
class Player
{
public:
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

    char field_0x00[0x2C];
    ScootCtrl *mScootCtrl;  // 0x2C
    char field_0x30[0x74];
    int mKeys;              // 0xA4
    int mNumBGMs;           // 0xA8
    int mBGMs[16];          // 0xAC
};

#endif
