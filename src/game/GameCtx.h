#ifndef WHIRL_TOUR_GAME_GAMECTX_H
#define WHIRL_TOUR_GAME_GAMECTX_H

// The game's code has an out-of-line copy of GameCtx's (inline) destructor besides the one expanded in
// DestroyGameCtx154C58: g++ emits it with #pragma interface here and #pragma implementation in
// GameCtx.cpp.
#pragma interface

#include "common/types.h"

// The game's state that outlives a level (gGameCtx262250): the mode, the options, each level's
// progress and the playlist. Field names come from the menus that show them (TODO.md, item 7).

// A music track the playlist can play.
struct BGMInfo
{
    char *mName00;
    s8 mFlag04;
    s8 mUnlocked05;
    char pad06[2];
};

// One level's progress (12 bytes).
struct LevelProgress
{
    int mGoals00;       // 0x00: goals done, of 7
    s8 mGoalDone04[7];  // 0x04: each goal
    s8 pad0B;
};

// What GameCtx::mObjs334 point to (deleted with the context).
struct UnkObj125CD8
{
    ~UnkObj125CD8(); // 0x00125CD8
};

struct GameCtxSub5AC
{
    int mField00;
};

struct GameCtx
{
    int mMode00;             // 0x000: the game mode, 0..7. Likely 0 Story and 2 Arcade (the level select
                             // tests {0, 2}; collectibles, which only Story has, {0, 3}); 4 uses the
                             // Versus degradation option
    int mSlot04;             // 0x004
    char pad08[0x0C];
    int mLevel14;            // 0x014: the level being played (0 Castle .. 7 Tibet)
    int mField18;            // 0x018
    int mCount1C;            // 0x01C
    char pad20[0x28];
    int *mField48;           // 0x048
    int mTrack4C;            // 0x04C: the playlist track playing
    int mNumTracks50;        // 0x050
    int mTracks54[41];       // 0x054: the playlist, on/off per track
    // Options (FEOptionsScreen::InitMenu16C6D8; the item order is the menu's, as seen in the game)
    int mActionCameras;      // 0x0F8: string 0x2C, on/off
    int mVibration;          // 0x0FC: string 0x2D, on/off
    int mBalanceMeter;       // 0x100: string 0x2E, on/off
    int pad104[5];
    int mNewScooter118;      // 0x118: set when collectibles unlock a scooter
    char pad11C[0xA8];
    int mArr1C4[6];          // 0x1C4
    int pad1DC[2];
    int mField1E4;           // 0x1E4
    char pad1E8[0x40];
    LevelProgress mLevels228[8]; // 0x228: Castle, Theme park, Suburbia, City in the sky, Subway,
                                 // Deep water rig, Movie set, Tibet
    int mArr288[23];         // 0x288
    int mArr2E4[10];         // 0x2E4
    int mArr30C[10];         // 0x30C
    UnkObj125CD8 *mObjs334[10]; // 0x334
    char pad35C[0x14];
    int mVersusTime;         // 0x370: 2 player options, string 0x37, an index for GetVersusTime154EA8
    int mVersusDegradation;  // 0x374: string 0x38, on/off
    f32 mFxVolume;           // 0x378: audio options, string 0x34, a slider
    f32 mMusicVolume;        // 0x37C: string 0x35, a slider
    int mInGameMusic;        // 0x380: string 0x36, on/off
    BGMInfo *mBGMTable384;   // 0x384
    int mFlags388[5];        // 0x388
    int mMaxLevel39C;        // 0x39C: the last level unlocked (0: only Castle)
    int mLevelFlags3A0[8];   // 0x3A0: one per level
    s8 mLevelBits3C0[8][5];  // 0x3C0: five per level
    s8 mScooterParts3E8[8][20]; // 0x3E8: the 20 "Scooters" collectibles of each level
    int mScooterPartsTotal488;   // 0x488: collectibles found in all levels
    int mScootersUnlocked48C[10]; // 0x48C: one more per 20 collectibles
    int mArr4B4[8];          // 0x4B4: one per level (func_00155250 sets them all)
    int mRaceOpen4D4[8];     // 0x4D4: the level can be played as a race (checkered flag on its icon)
    char pad4F4[0x38];
    int mArr52C[8];          // 0x52C: one per level (func_00155280 sets them all)
    char pad54C[0x5C];
    int mField5A8;           // 0x5A8: CreateScreen1101A8 adds a main-menu item when set
    GameCtxSub5AC *mSub5AC;  // 0x5AC
    char pad5B0[0x130];

    GameCtx();               // 0x00152528
    ~GameCtx()               // 0x00154B68 (also expanded in DestroyGameCtx154C58)
    {
        if (*mField48 > 0)
            delete[] mBGMTable384;
        for (int i = 0; i < 10; i++)
        {
            if (mObjs334[i] != 0)
                delete mObjs334[i];
        }
        delete mSub5AC;
    }
};

extern GameCtx *gGameCtx262250; // 0x00262250


#endif /* WHIRL_TOUR_GAME_GAMECTX_H */
