#pragma implementation
#include "common/types.h"
#include "game/GameCtx.h"
#include "game/FEScreen.h"
#include "common/libc.h"

// The game context (GameCtx, gGameCtx262250): its life cycle, the mode tests and each level's progress
// (0x00153C10..0x001566F8, after the constructor at 0x00152528). Functions not understood yet keep
// address names.

void func_00125D00(UnkObj125CD8 *); // 0x00125D00
void func_00125FA8(int, const char *, int, int); // 0x00125FA8
void func_00126138(int);        // 0x00126138
const char *func_00151D40(u16); // 0x00151D40
void func_00153AD8();           // 0x00153AD8
void UnlockAllLevels155238();   // 0x00155238
void func_00155250();           // 0x00155250
void func_00155280();           // 0x00155280
void UnlockAllScooters156158();           // 0x00156158
void func_00152610();           // 0x00152610
void func_0022FCC8(int, int, int, int); // 0x0022FCC8
int func_00155B48(f32 *, f32 *); // 0x00155B48
extern const char *const gLevelNames261C70[];      // "castle", "themepark", ... "tibet"
extern const int gLevelMenuIds2A2C50[];
extern const char *const gCharacterNames261C50[];  // "gavin", "niki", ... "marcus"
extern const int gCharacterTextIds2A2C30[];        // the characters' names in the text table
extern const char *const gScooterModels261C90[];   // "scooter_model_1" .. "scooter_model_10"
extern const int gScooterTextIds2A2C70[];          // the scooters' names in the text table
extern const int data_002A2C98[];                  // one per level, -1 for Movie set
extern const int data_002A2CB8[];                  // one per level, -1 for Movie set
extern const int data_002A2CD8[8][7];
extern const int gUnlockGoals261CB8[];
extern FEPad *gFEPads2659A0[4];


// Creates the context once (at start-up) and fills it (func_00152610).
#ifdef NON_MATCHING
// 38 of 55 instructions differ: our build puts a nop after the mult of the outer loop and before the
// first load of the inner one, and lays out the second loop's divide differently. Tried: a pointer to
// each level's row, a local context pointer, the count in a local.
// Marks collectible n of the level being played as found, counts all of them again and unlocks one more
// scooter per 20 (mNewScooter118 tells the front end).
void UnlockScooterGlobal(int n)
{
    gGameCtx262250->mScooterParts3E8[gGameCtx262250->mLevel14][n] = 1;
    gGameCtx262250->mScooterPartsTotal488 = 0;
    for (int level = 0; level < 8; level++)
    {
        for (int i = 0; i < 20; i++)
        {
            if (gGameCtx262250->mScooterParts3E8[level][i])
                gGameCtx262250->mScooterPartsTotal488 += 1;
        }
    }
    int count = gGameCtx262250->mScooterPartsTotal488 / 20;
    for (int i = 0; i <= count; i++)
    {
        if (!gGameCtx262250->mScootersUnlocked48C[i])
        {
            gGameCtx262250->mScootersUnlocked48C[i] = 1;
            gGameCtx262250->mNewScooter118 = 1;
        }
    }
}
#endif

void CreateGameCtx154C10()
{
    if (gGameCtx262250 == 0)
    {
        gGameCtx262250 = new GameCtx;
        func_00152610();
    }
}

void DestroyGameCtx154C58()
{
    if (gGameCtx262250 != 0)
    {
        delete gGameCtx262250;
        gGameCtx262250 = 0;
    }
}

void func_00154DE0(void *p)
{
    memset(p, 0, 0x74);
}

// The seconds of the "Versus time" option (2 player options); out of range gives 10.
f32 GetVersusTime154EA8(int index)
{
    switch (index)
    {
    default:
    case 0:
        return 10.0f;
    case 1:
        return 20.0f;
    case 2:
        return 30.0f;
    case 3:
        return 45.0f;
    case 4:
        return 60.0f;
    case 5:
        return 90.0f;
    case 6:
        return 120.0f;
    case 7:
        return 150.0f;
    case 8:
        return 180.0f;
    case 9:
        return 240.0f;
    case 10:
        return 300.0f;
    }
}

// The number of Versus time choices.
int GetVersusTimeCount154F80()
{
    return 11;
}

void func_00155030()
{
    UnlockAllLevels155238();
    func_00155250();
    func_00155280();
    func_00153AD8();
    UnlockAllScooters156158();
}

void func_00155A28()
{
    strlen(func_00151D40(0x82));
}

int func_00156300()
{
    return 0x134C;
}

int func_00156308()
{
    return 0x2490;
}

void func_001566B8(int arg0)
{
    func_00126138(arg0 + 0x65);
}

void func_001566D8(int arg0)
{
    func_00126138(arg0 + 0x3E9);
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_001557C8(u32 arg0)
{
    int var_v1;

    var_v1 = 0;
    switch (arg0)
    {
    case 0:
    case 2:
        var_v1 = 0;
        break;
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        var_v1 = 1;
        break;
    }
    return var_v1;
}

int func_00155B20(int *arg0, int *arg1)
{
    int temp_a0;
    int temp_v1;

    temp_a0 = *arg0;
    temp_v1 = *arg1;
    if (temp_a0 >= temp_v1)
    {
        return (temp_v1 >= temp_a0) ? 0 : -1;
    }
    return 1;
}


s8 GetGoalDone155070(int goal, int level)
{
    return gGameCtx262250->mLevels228[level].mGoalDone04[goal];
}

// The goals done in all eight levels.
int GetTotalGoals1550F8()
{
    int n = 0;
    for (int i = 0; i < 8; i++)
        n += gGameCtx262250->mLevels228[i].mGoals00;
    return n;
}

int func_001552B0()
{
    int temp_v1;
    int var_a1;

    temp_v1 = gGameCtx262250->mMode00;
    var_a1 = 0;
    if ((temp_v1 == 2) || (temp_v1 == 0))
    {
        var_a1 = 1;
    }
    return var_a1;
}

int func_001552E0(int arg0)
{
    int temp_v0;
    int var_a1;

    var_a1 = 0;
    if (arg0 != 7)
    {
        temp_v0 = gGameCtx262250->mMode00;
        if (temp_v0 != 5)
        {
            var_a1 = temp_v0 != 1;
        }
    }
    return var_a1;
}

int func_00155808()
{
    return (u32) (gGameCtx262250->mMode00 - 4) >= 2U;
}

int func_001559D0()
{
    return (u32) (gGameCtx262250->mMode00 - 1) >= 2U;
}

int func_001559F0()
{
    int temp_v1;
    int var_a0;

    temp_v1 = gGameCtx262250->mMode00;
    var_a0 = 0;
    if ((temp_v1 == 0) || (temp_v1 == 3) || (temp_v1 == 2))
    {
        var_a0 = 1;
    }
    return var_a0;
}

int func_001560C0()
{
    int temp_v1;
    int var_a0;

    temp_v1 = gGameCtx262250->mMode00;
    var_a0 = 0;
    if ((temp_v1 == 0) || (temp_v1 == 3))
    {
        var_a0 = 1;
    }
    return var_a0;
}

void func_00155368()
{
    if (gGameCtx262250->mField18 == 0 &&
        (gGameCtx262250->mMode00 == 0 || gGameCtx262250->mMode00 == 3 || gGameCtx262250->mMode00 == 7))
        gGameCtx262250->mLevelFlags3A0[gGameCtx262250->mLevel14] = 1;
}

int func_001553C0()
{
    return gGameCtx262250->mLevelFlags3A0[gGameCtx262250->mLevel14];
}

void func_001553E0(int n)
{
    if (gGameCtx262250->mMode00 == 0 || gGameCtx262250->mMode00 == 3 || gGameCtx262250->mMode00 == 7)
        gGameCtx262250->mLevelBits3C0[gGameCtx262250->mLevel14][n] = 1;
}

s8 func_00155438(int n)
{
    return gGameCtx262250->mLevelBits3C0[gGameCtx262250->mLevel14][n];
}

int func_00155460()
{
    int result = 0;
    if ((gGameCtx262250->mMode00 == 0 || gGameCtx262250->mMode00 == 3 || gGameCtx262250->mMode00 == 6 ||
         gGameCtx262250->mMode00 == 7) && gGameCtx262250->mField18 == 0)
        result = gGameCtx262250->mLevel14 != 7;
    return result;
}

int func_00155508()
{
    int result = 0;
    if ((u32)(gGameCtx262250->mMode00 - 3) >= 2)
        result = gGameCtx262250->mField18 == 0;
    return result;
}

int func_00155538(int n)
{
    return gGameCtx262250->mFlags388[n] == 1;
}

void func_00155558(int n)
{
    if (gGameCtx262250->mFlags388[n] == 0)
        gGameCtx262250->mFlags388[n] = 1;
}

// The levels' file names.
const char *const *func_001551F0()
{
    return gLevelNames261C70;
}

const int *GetLevelMenuIds155228()
{
    return gLevelMenuIds2A2C50;
}

void UnlockAllLevels155238()
{
    gGameCtx262250->mMaxLevel39C = 7;
}

void func_00155250()
{
    for (int i = 0; i < 8; i++)
        gGameCtx262250->mArr4B4[i] = 1;
}

void func_00155280()
{
    for (int i = 0; i < 8; i++)
        gGameCtx262250->mArr52C[i] = 1;
}

void func_00155588(int n)
{
    gGameCtx262250->mFlags388[n] = 2;
}

int func_001555C0()
{
    int any = 0;
    for (int i = 0; i < 6; i++)
    {
        if (gGameCtx262250->mArr1C4[i] != 0)
            any = 1;
    }
    return any;
}

int func_00155740()
{
    int result = 0;
    if (gGameCtx262250->mMode00 != 6)
        result = gGameCtx262250->mField1E4 != 0;
    return result;
}

int func_00155828()
{
    return gGameCtx262250->mField18 == 1;
}

int func_00155840()
{
    int result = 0;
    if (gGameCtx262250->mField18 != 1)
    {
        switch ((u32)gGameCtx262250->mMode00)
        {
        default:
        case 0:
        case 2:
        case 3:
        case 6:
        case 7:
            result = 1;
            break;
        case 1:
        case 5:
            result = 0;
            break;
        case 4:
            result = gGameCtx262250->mVersusDegradation;
            break;
        }
    }
    return result;
}

int func_00155970()
{
    return gGameCtx262250->mField18 != 1;
}

int func_00155988()
{
    int result = 0;
    if ((gGameCtx262250->mMode00 != 1 && gGameCtx262250->mLevelFlags3A0[gGameCtx262250->mLevel14] == 0) ||
        gGameCtx262250->mField18 == 2)
        result = 1;
    return result;
}

// The name of the playlist track playing, when it is a valid, enabled one.
char *GetCurrentTrackName155AD8()
{
    int track = gGameCtx262250->mTrack4C;
    if (track >= 0 && track < gGameCtx262250->mNumTracks50)
    {
        if (gGameCtx262250->mBGMTable384[track].mFlag04 != 0)
            return gGameCtx262250->mBGMTable384[track].mName00;
    }
    return 0;
}


// Per level, the goals done (GetLevelGoals1550D8 is at 0x001550D8).
int GetLevelGoals1550D8(int level)
{
    return gGameCtx262250->mLevels228[level].mGoals00;
}

int func_00155EC0()
{
    return gGameCtx262250->mField1DC;
}

// Each player's choices (FECharacterScreen, FEScooterScreen) and controller.
void SetPlayerCharacter155ED0(int player, int character, int arg2)
{
    gGameCtx262250->mCharacter288[player] = character;
    gGameCtx262250->mArr2B0[player] = arg2;
}

const char *GetCharacterName155EF0(int player)
{
    return gCharacterNames261C50[gGameCtx262250->mCharacter288[player]];
}

const char *const *GetCharacterNames155F20()
{
    return gCharacterNames261C50;
}

const int *GetCharacterTextIds155F30()
{
    return gCharacterTextIds2A2C30;
}

void SetPlayerScooter155F40(int player, int model, int arg2)
{
    gGameCtx262250->mScooterModel2D8[player] = model;
    gGameCtx262250->mArr2E4[player] = arg2;
}

s8 GetPlayerScooter155F68(int player)
{
    return gGameCtx262250->mScooterModel2D8[player];
}

void SetPlayerPad155F80(int player, int pad)
{
    gGameCtx262250->mPad20[player] = pad;
}

FEPad *GetPlayerPad155F98(int player)
{
    return gFEPads2659A0[gGameCtx262250->mPad20[player]];
}

int GetPlayerPadIndex155FC8(int player)
{
    return gGameCtx262250->mPad20[player];
}

int func_00155FE0()
{
    return gGameCtx262250->mCount50C;
}

// Sets entry n once; the count of set entries goes into every player's mArr30C.
void func_00155FF0(int n)
{
    if (gGameCtx262250->mArr510[n] == 0)
    {
        gGameCtx262250->mArr510[n] = 1;
        gGameCtx262250->mCount50C++;
        for (int i = 0; i < 10; i++)
            gGameCtx262250->mArr30C[i] = gGameCtx262250->mCount50C;
    }
}

int func_00156050()
{
    if (gGameCtx262250->mField18 == 1)
        return data_002A2C98[gGameCtx262250->mLevel14];
    return -1;
}

int func_00156088()
{
    if (gGameCtx262250->mField18 == 1)
        return data_002A2CB8[gGameCtx262250->mLevel14];
    return -1;
}

// Whether collectible n of the level being played has been found.
s8 GetScooterPart1560F0(int n)
{
    return gGameCtx262250->mScooterParts3E8[gGameCtx262250->mLevel14][n];
}

// The collectibles found in a level (of 20).
int GetLevelScooters156118(int level)
{
    int count = 0;
    for (int i = 0; i < 20; i++)
    {
        if (gGameCtx262250->mScooterParts3E8[level][i])
            count++;
    }
    return count;
}

void UnlockAllScooters156158()
{
    for (int i = 0; i < 10; i++)
    {
        gGameCtx262250->mScootersUnlocked48C[i] = 1;
        for (int j = 0; j < 5; j++)
            gGameCtx262250->mScooterBits573[i][j] = 1;
    }
}

const char *const *GetScooterModels1561B8()
{
    return gScooterModels261C90;
}

const int *GetScooterTextIds1561C8()
{
    return gScooterTextIds2A2C70;
}

const char *GetScooterModel1561D8(int player)
{
    return gScooterModels261C90[gGameCtx262250->mScooterModel2D8[player]];
}

void func_001562E8()
{
    gGameCtx262250->mField5A8 = 1;
    gGameCtx262250->mField11C = 1;
}

void func_00151D20(int);          // 0x00151D20
int func_00142320();              // 0x00142320
void func_001425E0(int, f32);     // 0x001425E0
extern int data_0025E5DC;
extern const int data_002A2DB8[];
extern const int data_002A2DD8[];

void func_00154E80(int arg0)
{
    gGameCtx262250->mField35C = arg0;
    func_00151D20(arg0);
}

void func_00154F88(f32 vol)
{
    gGameCtx262250->mFxVolume = vol;
    if (data_0025E5DC != 0)
        func_001425E0(func_00142320(), vol);
}

int func_00155198()
{
    return data_002A2DB8[gGameCtx262250->mLevel14];
}

void func_001551C0()
{
    for (int i = 6; i >= 0; i--)
        gGameCtx262250->mArr104[i] = 0;
    gGameCtx262250->mField120 = 0;
}

const char *func_00155200()
{
    return gLevelNames261C70[gGameCtx262250->mLevel14];
}

int GetLevelKey155310(int level)
{
    if (level < 6)
        return gGameCtx262250->mArr510[data_002A2CB8[level]];
    if (level == 6)
        return gGameCtx262250->mField54C;
    return 0;
}

int func_001555A8(int idx)
{
    return data_002A2DD8[idx];
}

void func_00155658()
{
    for (int i = 0; i < 6; i++)
        gGameCtx262250->mArr4F4[i] = 1;
    gGameCtx262250->mField5A8 = 1;
}

void func_00153CE8(int arg0, int arg1, int arg2)
{
    if (gGameCtx262250->mArr550[arg0][arg1] == 0)
    {
        gGameCtx262250->mArr550[arg0][arg1] = 1;
        if (gGameCtx262250->mField120 < 10)
        {
            gGameCtx262250->mEvents124[gGameCtx262250->mField120].mField00 = 1;
            gGameCtx262250->mEvents124[gGameCtx262250->mField120].mField04 = arg0;
            gGameCtx262250->mEvents124[gGameCtx262250->mField120].mField08 = arg1;
            gGameCtx262250->mEvents124[gGameCtx262250->mField120].mField0C = arg2;
            gGameCtx262250->mField120++;
        }
    }
}

void func_00153D80(int arg0, int arg1, int arg2)
{
    if (gGameCtx262250->mScooterBits573[arg0][arg1] == 0)
    {
        gGameCtx262250->mScooterBits573[arg0][arg1] = 1;
        if (gGameCtx262250->mField120 < 10)
        {
            gGameCtx262250->mEvents124[gGameCtx262250->mField120].mField00 = 0;
            gGameCtx262250->mEvents124[gGameCtx262250->mField120].mField04 = arg0;
            gGameCtx262250->mEvents124[gGameCtx262250->mField120].mField08 = arg1;
            gGameCtx262250->mEvents124[gGameCtx262250->mField120].mField0C = arg2;
            gGameCtx262250->mField120++;
        }
    }
}

int func_001556F8()
{
{
    int ret = 0;
    int mode = gGameCtx262250->mMode00;
    if (mode != 1 && mode != 6 && mode != 5)
    {
        if (gGameCtx262250->mField18 != 1)
            ret = 1;
    }
    return ret;
}
}

int func_001558A8()
{
{
    int ret = 0;
    int mode = gGameCtx262250->mMode00;
    if (mode != 1 && mode != 6 && mode != 5)
    {
        if (gGameCtx262250->mField18 != 1)
            ret = 1;
    }
    return ret;
}
}

int func_00155940()
{
{
    int mode = gGameCtx262250->mMode00;
    if (mode == 5)
        return 0;
    return gGameCtx262250->mCount1C >= 2;
}
}

int func_00155B48(f32 *arg0, f32 *arg1)
{
    if (*arg0 < *arg1)
        return 1;
    if (*arg1 < *arg0)
        return -1;
    return 0;
}

int func_00155B80(f32 *arg0, f32 *arg1)
{
    if (*arg0 < *arg1)
        return -1;
    if (*arg1 < *arg0)
        return 1;
    return 0;
}

int func_00155BB8()
{
{
    int ret = 0;
    int mode = gGameCtx262250->mMode00;
    if (mode != 1 && mode != 4 && mode != 5)
        ret = 1;
    return ret;
}
}

void func_00154A70(u32 arg0)
{
    int id = arg0 + 0x3E9;
    switch (arg0)
    {
    case 0:
        func_00125FA8(id, "DATA:scoot_01", 0, 0);
        break;
    case 1:
        func_00125FA8(id, "DATA:scoot_02", 0, 0);
        break;
    case 2:
        func_00125FA8(id, "DATA:scoot_03", 0, 0);
        break;
    case 3:
        func_00125FA8(id, "DATA:scoot_04", 0, 0);
        break;
    case 4:
        func_00125FA8(id, "DATA:scoot_05", 0, 0);
        break;
    case 5:
        func_00125FA8(id, "DATA:scoot_06", 0, 0);
        break;
    case 6:
        func_00125FA8(id, "DATA:scoot_07", 0, 0);
        break;
    case 7:
        func_00125FA8(id, "DATA:scoot_08", 0, 0);
        break;
    case 8:
        func_00125FA8(id, "DATA:scoot_09", 0, 0);
        break;
    case 9:
        func_00125FA8(id, "DATA:scoot_10", 0, 0);
        break;
    }
}

void func_00154CF8(GameCtxSub5AC *p, int arg1)
{
{
    int i;
    memset(p, 0, 0xB8);
    for (i = 0; i < 4; i++)
        func_00154DE0(&p->mSubB8[i]);
    memset(p->mArr288, 0, 0xB8);
    for (i = 0; i < 8; i++)
        p->mArr288[i].mField04 = 1e9f;
    func_00154DE0(&p->mSub340);
    memset(p->mArr3B4, 0, 0xB8);
    if (arg1 != 0)
    {
        for (i = 0; i < 8; i++)
            p->mArr3B4[i].mField04 = 1e9f;
    }
}
}

#ifdef NON_MATCHING
// 18/31 diffs: loop scheduling (addiu $a1, -1; addiu $a0, 4 before vs after lw/ori/sw) and 1 nop at +0x044.
void func_00154E00(int arg0)
{
    gGameCtx262250->mField368 = arg0;
    if (arg0 != 0)
    {
        for (int i = 0; i < 4; i++)
        {
            FEPad *pad = gFEPads2659A0[i];
            pad->mFlags04 |= 2;
        }
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        FEPad *pad = gFEPads2659A0[i];
        pad->mFlags04 &= ~2;
    }
}
#endif

void func_00154FD8()
{
    for (int i = 0; i < 10; i++)
        func_00125D00(gGameCtx262250->mObjs334[i]);
}

const char *func_00155090(int arg0)
{
    return func_00151D40(data_002A2CD8[gGameCtx262250->mLevel14][arg0]);
}

int GetGoalsToUnlock155130()
{
    if (gGameCtx262250->mMaxLevel39C >= 6)
        return 0;
    int sum = 0;
    for (int i = 0; i < 8; i++)
        sum += gGameCtx262250->mLevels228[i].mGoals00;
    return gUnlockGoals261CB8[gGameCtx262250->mMaxLevel39C] - sum;
}

int func_001555F8()
{
    int ret = -1;
    for (int i = 0; i < 6; i++)
    {
        if (gGameCtx262250->mArr1C4[i] != 0)
        {
            gGameCtx262250->mArr1C4[i] = 0;
            ret = i;
            break;
        }
    }
    return ret;
}

void func_00155690()
{
    if (gGameCtx262250->mRaceOpen4D4[gGameCtx262250->mLevel14] == 0)
    {
        gGameCtx262250->mRaceOpen4D4[gGameCtx262250->mLevel14] = 1;
        int all = 1;
        for (int i = 0; i < 8; i++)
        {
            if (gGameCtx262250->mRaceOpen4D4[i] == 0)
                all = 0;
        }
        if (all != 0)
        {
            gGameCtx262250->mArr4F4[3] = 1;
            gGameCtx262250->mArr1C4[3] = 1;
        }
    }
}

void func_00155A50()
{
    int unlocked = 0;
    for (int i = 0; i < gGameCtx262250->mNumTracks50; i++)
    {
        if (unlocked < 3)
        {
            if (gGameCtx262250->mBGMTable384[i].mUnlocked05 == 0)
            {
                gGameCtx262250->mBGMTable384[i].mUnlocked05 = 1;
                gGameCtx262250->mBGMTable384[i].mFlag04 = 1;
                unlocked++;
            }
        }
    }
}

void func_00155C58(int arg0, int arg1, int arg2, f32 arg3)
{
    GameCtxSub74 *sub;
    if (gGameCtx262250->mField18 == 0)
        sub = &gGameCtx262250->mSub5AC[gGameCtx262250->mLevel14].mSubB8[arg0];
    else if (gGameCtx262250->mField18 == 2)
        return;
    else if (arg0 == 0)
        sub = &gGameCtx262250->mSub5AC[gGameCtx262250->mLevel14].mSub340;
    else
        return;
    sub->mArr04[3].mField08 = arg2;
    sub->mArr04[3].mField00 = arg3;
    sub->mArr04[3].mField04 = arg1;
    strcpy(sub->mArr04[3].mName0C, gGameCtx262250->mName1E8);
    func_0022FCC8((int)sub->mArr04, 4, sizeof(GameCtxSub1C), (int)func_00155B48);
    int n = sub->mCount00 + 1;
    sub->mCount00 = (n < 4) ? n : 3;
}

int func_00155D30(int arg0)
{
    if (gGameCtx262250->mField18 == 0)
        return gGameCtx262250->mSub5AC[gGameCtx262250->mLevel14].mSubB8[arg0].mCount00;
    if (gGameCtx262250->mField18 == 2)
        return 0;
    if (arg0 == 0)
        return gGameCtx262250->mSub5AC[gGameCtx262250->mLevel14].mSub340.mCount00;
    return 0;
}

int func_00155768()
{
    int ret = 1;
    switch (gGameCtx262250->mField18)
    {
    case 0:
        break;
    case 1:
        ret = 0;
        break;
    case 2:
        ret = func_001557C8(gGameCtx262250->mLevel14) == 0;
        break;
    }
    return ret;
}

int func_00155BF0()
{
    if (gGameCtx262250->mField18 == 0)
        return gGameCtx262250->mSub5AC[gGameCtx262250->mLevel14].mField00;
    if (gGameCtx262250->mField18 == 2)
        return gGameCtx262250->mSub5AC[gGameCtx262250->mLevel14].mArr3B4[0].mField00;
    return gGameCtx262250->mSub5AC[gGameCtx262250->mLevel14].mArr288[0].mField00;
}

void func_00156200()
{
    gGameCtx262250->mFieldF4 = gGameCtx262250->mField35C;
    gGameCtx262250->mActionCameras = gGameCtx262250->mField364;
    gGameCtx262250->mVibration = gGameCtx262250->mField368;
    gGameCtx262250->mBalanceMeter = gGameCtx262250->mField36C;
    for (int i = 0; i < gGameCtx262250->mNumTracks50; i++)
        gGameCtx262250->mTracks54[i] = gGameCtx262250->mBGMTable384[i].mFlag04;
}

void func_00156270()
{
    gGameCtx262250->mField35C = gGameCtx262250->mFieldF4;
    gGameCtx262250->mField364 = gGameCtx262250->mActionCameras;
    gGameCtx262250->mField368 = gGameCtx262250->mVibration;
    gGameCtx262250->mField36C = gGameCtx262250->mBalanceMeter;
    for (int i = 0; i < gGameCtx262250->mNumTracks50; i++)
        gGameCtx262250->mBGMTable384[i].mFlag04 = gGameCtx262250->mTracks54[i];
}

void func_001565F0(u32 arg0)
{
    int id = arg0 + 0x65;
    switch (arg0)
    {
    case 0:
        func_00125FA8(id, "DATA:char_0", 0, 0);
        break;
    case 1:
        func_00125FA8(id, "DATA:char_1", 0, 0);
        break;
    case 2:
        func_00125FA8(id, "DATA:char_2", 0, 0);
        break;
    case 3:
        func_00125FA8(id, "DATA:char_3", 0, 0);
        break;
    case 4:
        func_00125FA8(id, "DATA:char_4", 0, 0);
        break;
    case 5:
        func_00125FA8(id, "DATA:char_5", 0, 0);
        break;
    case 6:
        func_00125FA8(id, "DATA:char_6", 0, 0);
        break;
    }
}
