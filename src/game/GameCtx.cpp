#pragma implementation
#include "common/types.h"
#include "game/GameCtx.h"
#include "common/libc.h"

// The game context (GameCtx, gGameCtx262250): its life cycle, the mode tests and each level's progress
// (0x00153C10..0x001566F8, after the constructor at 0x00152528). Functions not understood yet keep
// address names.

void func_00126138(int);        // 0x00126138
const char *func_00151D40(u16); // 0x00151D40
void func_00153AD8();           // 0x00153AD8
void UnlockAllLevels155238();   // 0x00155238
void func_00155250();           // 0x00155250
void func_00155280();           // 0x00155280
void func_00156158();           // 0x00156158
void func_00152610();           // 0x00152610
extern const int data_00261C70[];
extern const int gLevelMenuIds2A2C50[];


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

int func_00154F80()
{
    return 0xB;
}

void func_00155030()
{
    UnlockAllLevels155238();
    func_00155250();
    func_00155280();
    func_00153AD8();
    func_00156158();
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

const int *func_001551F0()
{
    return data_00261C70;
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

