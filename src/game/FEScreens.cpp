#include "common/libc.h"
#include "game/GL.h"
#include "game/FEScreen.h"

struct BGMInfo
{
    char *mName00;
    u8 mFlag04;
    s8 mUnlocked05;
    char pad06[2];
};

// One level's progress in the game context (12 bytes; GetLevelGoals1550D8 reads mGoals00).
struct FELevelProgress
{
    int mGoals00;  // 0x00: goals done, of 7
    int mField04;  // 0x04
    int mField08;  // 0x08
};

struct GameCtxFE
{
    int pad00;
    int mSlot04;
    char pad08[0x0C];
    int mField14;
    int mField18;
    int mCount1C;
    char pad20[0x30];
    int mNumTracks50;
    int mTracks54[41];
    // Options (FEOptionsScreen::InitMenu16C6D8; the item order is the menu's, as seen in the game)
    int mActionCameras;  // 0xF8: string 0x2C, on/off
    int mVibration;      // 0xFC: string 0x2D, on/off
    int mBalanceMeter;   // 0x100: string 0x2E, on/off
    char pad104[0x124];
    FELevelProgress mLevels228[8]; // 0x228: Castle, Theme park, Suburbia, City in the sky, Subway,
                                   // Deep water rig, Movie set, Tibet
    int mArr288[23];
    int mArr2E4[10];
    int mArr30C[10];
    char pad334[0x3C];
    int mVersusTime;        // 0x370: 2 player options, string 0x37, an index for GetVersusTime154EA8
    int mVersusDegradation; // 0x374: string 0x38, on/off
    f32 mFxVolume;       // 0x378: audio options, string 0x34, a slider
    f32 mMusicVolume;    // 0x37C: string 0x35, a slider
    int mInGameMusic;    // 0x380: string 0x36, on/off
    BGMInfo *mBGMTable384;
    char pad388[0x14];
    int mMaxLevel39C;    // 0x39C: the last level unlocked (0: only Castle)
    char pad3A0[0x48];
    u8 mScooterParts3E8[8][20]; // 0x3E8: the 20 "Scooters" collectibles of each level
    char pad488[0x4C];
    int mRaceOpen4D4[8]; // 0x4D4: the level can be played as a race (checkered flag on its icon)

    static inline GameCtxFE *Get()
    {
        extern GameCtxFE *gGameCtx262250;
        return gGameCtx262250;
    }
};
extern GameCtxFE *gGameCtx262250;
extern const int gOptionsMenuIds2627A8[];
extern const int gOptionsMenuKinds2627C8[];
extern const int gAudioMenuIds2627E8[];
extern const int gAudioMenuKinds262800[];
extern const int gTwoPlayerMenuIds262818[];
extern const int gTwoPlayerMenuKinds262828[];

extern const int gMonsterMenuIds259F10[];
extern int gMovCreditData282F68[];

void *FindFont1264A8(const char *name);
void Release198F38(void *);
void CleanupDialog1309E0(void *);
u32 HashStringCRC32(const char *str);
void PlaySoundCRC141520(u32 crc);
void DrawBegin19A640();
void DrawEnd19A6B0();
void func_00113BD0();
void func_00158330(void *, int);
int func_001586D0(void *);
int func_00158790(void *, int, int, int, int);
int func_00158860(void *);
int func_001433F8(void *);
void func_00143170(void *, int);
void *func_00143100(const char *, int);
void func_001432A0(void *, f32);
void func_00143270(void *);
void func_0011A820(void *);
int func_0011A470(void *);
int func_0011A570(void *);
void func_0011A3E0(void *, int);
void func_00119210(void *, f32);
void func_00191E40(void *);
void PhysicsRelease1F3A70(void *);
void MemFree1BD978(void *);
void *func_00192130(int, int, void *, void *, f32);
void *func_00113FA0();
void func_00197200(void *);
void func_00192248(void *);
const int *GetLevelMenuIds155228();
const char *func_00151D40(u16 id);
void *func_001262E0(int);
void *func_00126280(int id);
void func_00119560(void *actor, int, int);
void func_00191F80(void *cam, Mat4x4f *view, Mat4x4f *m);
void func_00191FD0(void *cam, Mat4x4f *proj);
void func_00196430(void *model, void *tex);
const int *func_00155F30();
int func_00155FC8(int);
const int *func_001561C8();
f32 GetVersusTime154EA8(int index);
void func_00196E38(void *movie);
void func_00192350(void *credits);
f32 Sin1B1910(f32 x);
void func_00121428(void *stats, TextObj *text, const char *title, f32 x, f32 y, f32, f32, f32, f32, f32, f32,
                   f32, f32, f32, f32);
void DrawModel196110(void *model);
extern FEPad *gFEPads2659A0[4];
UnkRes126250 *func_00126250(int);
int GetLevelGoals1550D8(int level);
int GetGoalsToUnlock155130();
int GetLevelKey155310(int level);
int GetLevelScooters156118(int level);
void func_00158140(void *, void *, int, int, f32, f32);
void func_00156200();
void func_00155F40(int, int, int);
void func_00141950(void *, int);
void func_00155ED0(int, int, int);

// 1. FEMcScreen
FEMcScreen::FEMcScreen(FEOwner *owner, int mode, void *mc)
    : FEScreen(0, 3, owner)
{
    mMc16C = mc;
    mState168 = 900;
    mField164 = 0;
    mMode170 = mode;
    if (mode == 100 || mode == 200)
        mState168 = mode;
}

FEMcScreen::~FEMcScreen()
{
}

void FEMcScreen::VirtSlot2(f32 dt)
{
    FEScreen::VirtSlot2(dt);
    switch (mState168)
    {
    case 100:
        if (func_001586D0(mMc16C))
            AdvanceState168();
        break;
    case 200:
        if (func_00158790(mMc16C, gGameCtx262250->mSlot04, 0, 0, 0))
            AdvanceState168();
        break;
    case 101:
    case 201:
        if (func_00158860(mMc16C))
            mState168 = 900;
        break;
    case 900:
        mField164 = 1;
        break;
    }
}

void FEMcScreen::VirtSlot3()
{
    DrawBegin19A640();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    if (mMode170 != 200)
        func_00113BD0();
    func_00158330(mMc16C, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    DrawEnd19A6B0();
}

int FEMcScreen::VirtSlot7()
{
    return mField164;
}

// 2. FEMonsterScreen
FEMonsterScreen::FEMonsterScreen(FEOwner *owner)
    : FEScreen(0x69, 2, owner)
{
    CreateMenuA(gMonsterMenuIds259F10, 3);
    mField40 = 1;
    mText164 = CreateTextObj198E48(FindFont1264A8("font_body"), 0, 0.0f, 0.0f, 0.0f);
}

FEMonsterScreen::~FEMonsterScreen()
{
    Release198F38(mText164);
}

void FEMonsterScreen::VirtSlot2(f32 dt)
{
    FEScreen::VirtSlot2(dt);
    if (gGameCtx262250->mCount1C >= 2)
        mMenu0C->EnableItem(0);
    else
        mMenu0C->DisableItem(0);
    if (gGameCtx262250->mCount1C < 10)
        mMenu0C->EnableItem(1);
    else
        mMenu0C->DisableItem(1);
    if (gGameCtx262250->mCount1C > 0)
        mMenu0C->EnableItem(2);
    else
        mMenu0C->DisableItem(2);
    if (mMenu0C->mState1C != 0 && mMenu0C->mSelected0C == 2)
    {
        gGameCtx262250->mCount1C--;
        mMenu0C->mState1C = 0;
    }
}

#ifdef NON_MATCHING
// 117 of 131 instructions differ: the game keeps two copies of gGameCtx262250's address (the loop test
// has its own) and all four constants (150, 350, 750, 50) in registers, which takes two more saved
// registers than this; loop forms (for/while, the max as if or ternary) and the text macros did not
// change it.
// Lists the last (up to) six entries: number, score (func_00155FC8) and name, 50 units apart.
void FEMonsterScreen::VirtSlot3()
{
    char number[0x40];
    char score[0x40];

    FEScreen::VirtSlot3();
    f32 y = 530.0f;
    DrawBegin19A640();
    mText164->mScale1C.Set(0.6f, 0.65f, 1.0f);
    mText164->mColor28 = 0x80808080;
    int n = gGameCtx262250->mCount1C - 6;
    for (int i = n >= 0 ? n : 0; i < gGameCtx262250->mCount1C; i++)
    {
        sprintf(number, func_00151D40(0x6B), i + 1);
        sprintf(score, func_00151D40(0x6C), func_00155FC8(i) + 1);
        mText164->mPos04.Set(150.0f, y, 0.0f);
        mText164->mString30 = number;
        DrawText19B758(mText164);
        mText164->mPos04.Set(350.0f, y, 0.0f);
        mText164->mString30 = score;
        DrawText19B758(mText164);
        mText164->mPos04.Set(750.0f, y, 0.0f);
        mText164->mString30 = func_00151D40(func_00155F30()[gGameCtx262250->mArr288[i]]);
        DrawText19B758(mText164);
        y -= 50.0f;
        }
    DrawEnd19A6B0();
}
#endif

// 3. FEPlaylistScreen
FEPlaylistScreen::FEPlaylistScreen(FEOwner *owner, int arg2)
    : FEScreen(0x67, 1, owner)
{
    mField180 = arg2;
    mField164 = 0;
    mSelected168 = 0;
    mCount16C = 0;
    mTimer18C = 0.0f;
    mBlink190 = 0;
    mStream194 = 0;
    mField178 = 0;
    mField17C = 0;
    mPlayingIdx188 = -1;
    mText184 = CreateTextObj198E48(FindFont1264A8("font_body"), 0, 0.0f, 0.0f, 0.0f);
    mEnabled170 = new int[gGameCtx262250->mNumTracks50];
    mTracks174 = new int[gGameCtx262250->mNumTracks50];
    InitTracks112A78();
    for (int i = 0; i < gGameCtx262250->mNumTracks50; i++)
    {
        mEnabled170[i] = gGameCtx262250->mTracks54[i];
    }
}

FEPlaylistScreen::~FEPlaylistScreen()
{
    Release198F38(mText184);
    if (mStream194 != 0)
        func_00143170(mStream194, 4);
    if (mEnabled170 != 0)
        delete[] mEnabled170;
    if (mTracks174 != 0)
        delete[] mTracks174;
}

void FEPlaylistScreen::InitTracks112A78()
{
    mCount16C = 0;
    for (int i = 0; i < GameCtxFE::Get()->mNumTracks50; i++)
    {
        if (GameCtxFE::Get()->mBGMTable384[i].mUnlocked05 != 0)
        {
            mTracks174[mCount16C] = i;
            mCount16C++;
        }
    }
}

void FEPlaylistScreen::VirtSlot2(f32 dt)
{
    FEScreen::VirtSlot2(dt);
    mTimer18C -= dt;
    if (mTimer18C <= 0.0f)
    {
        mBlink190++;
        mTimer18C = 0.5f;
    }
    if (mStream194 != 0 && func_001433F8(mStream194))
    {
        func_00143170(mStream194, 4);
        mStream194 = 0;
        mPlayingIdx188 = -1;
    }
    int btns = gFEPad2659B0->mPressed20;
    if (btns & 0x50000000)
    {
        PlaySoundCRC141520(HashStringCRC32("mnu_p1select"));
        if (btns & 0x40000000)
        {
            int c = mCount16C - 1;
            mSelected168 = (mSelected168 + c) % mCount16C;
        }
        else if (btns & 0x10000000)
            mSelected168 = (mSelected168 + 1) % mCount16C;
    }
    else if (btns & 0x100000)
    {
        if (mField17C == 0)
        {
            mField17C = 1;
            PlaySoundCRC141520(HashStringCRC32("mnu_selectitem"));
        }
        for (int i = 0; i < gGameCtx262250->mNumTracks50; i++)
        {
            gGameCtx262250->mTracks54[i] = mEnabled170[i];
        }
    }
    else if (btns & (int)0xA0000000)
    {
        PlaySoundCRC141520(HashStringCRC32("mnu_p1select"));
        mEnabled170[mTracks174[mSelected168]] = !mEnabled170[mTracks174[mSelected168]];
    }
    else if (btns & 0x80000)
    {
        if (mStream194 != 0)
        {
            func_00143170(mStream194, 4);
            mStream194 = 0;
        }
        if (mPlayingIdx188 != mSelected168 &&
            (mStream194 = func_00143100(gGameCtx262250->mBGMTable384[mTracks174[mSelected168]].mName00 + 0x60, 4)) != 0)
        {
            mPlayingIdx188 = mSelected168;
        }
        else
        {
            mPlayingIdx188 = -1;
        }
    }
}

int FEPlaylistScreen::VirtSlot7()
{
    return mField178;
}

int FEPlaylistScreen::VirtSlot8()
{
    return mField17C;
}

// 4. FEChooseScreen
// Draws each player's character (mModels168) and, behind it, the two models of mPairs190 with the
// texture of the player's choice, through the screen's camera.
void FEChooseScreen::VirtSlot3()
{
    Mat4x4f view;
    Mat4x4f m40;
    Mat4x4f proj;

    FEScreen::VirtSlot3();
    func_00191F80(mCam208, &view, &m40);
    func_00191FD0(mCam208, &proj);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadMatrixf(&proj.row[0].x);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(&view.row[0].x);
    for (int i = 0; i < mCount164; i++)
    {
        f32 x;
        f32 z;
        if (mCount164 == 1)
        {
            x = 1.0f;
            z = -0.6f;
        }
        else
        {
            x = 1.9f;
            if (i == 0)
                x = 0.7f;
            z = -1.5f;
        }
        glPushMatrix();
        glTranslatef(x, -0.8f, z);
        glRotatef(-30.0f, 0.0f, 1.0f, 0.0f);
        if (mModels168[i] != 0 && mClosing20C == 0)
            func_00119560(mModels168[i], 0, 1);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(x - 0.1f, -0.8f, z - 0.7f);
        glRotatef(-70.0f, 0.0f, 1.0f, 0.0f);
        if (mPairs190[i].mModel00 != 0)
        {
            void *tex = func_00126280(mDefs1E0[i]->mTexIds1DC[gGameCtx262250->mArr2E4[i]]);
            if (tex != 0)
                func_00196430(mPairs190[i].mModel00, tex);
            DrawModel196110(mPairs190[i].mModel00);
        }
        if (mPairs190[i].mModel04 != 0)
        {
            void *tex = func_00126280(mDefs1E0[i]->mTexIds1DC[gGameCtx262250->mArr2E4[i]]);
            glTranslatef(0.0f, 0.46f, 0.3f);
            if (tex != 0)
                func_00196430(mPairs190[i].mModel04, tex);
            DrawModel196110(mPairs190[i].mModel04);
        }
        glPopMatrix();
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

FEChooseScreen::~FEChooseScreen()
{
    for (int i = 0; i < mCount164; i++)
    {
        if (mModels168[i] != 0)
            func_0011A820(mModels168[i]);
    }
    func_00191E40(mCam208);
}

void FEChooseScreen::VirtSlot2(f32 dt)
{
    FEScreen::VirtSlot2(dt);
    for (int i = 0; i < mCount164; i++)
    {
        if (mModels168[i] != 0)
        {
            if (func_0011A470(mModels168[i]) && !func_0011A570(mModels168[i]))
            {
                func_0011A3E0(mModels168[i], 0x13001);
                func_0011A3E0(mModels168[i], 0x11002);
                func_0011A3E0(mModels168[i], 0x14001);
                func_0011A3E0(mModels168[i], 0x11002);
            }
            func_00119210(mModels168[i], dt);
        }
    }
}

int FEChooseScreen::VirtSlot5()
{
    if (mClosing20C != 0)
        return mCloseTimer210-- <= 0;
    if (mState38 == 3)
    {
        mClosing20C = 1;
        mCloseTimer210 = 5;
    }
    return 0;
}

// 5. FEMovScreen
inline void FEMovSub198::Destroy114C88()
{
    func_00191E40(mCam54);
    PhysicsRelease1F3A70(mPhys5C);
    for (int i = 0; i < 10; i++)
    {
        if (mArr64[i] != 0)
            PhysicsRelease1F3A70(mArr64[i]);
    }
    MemFree1BD978(this);
}

FEMovScreen::FEMovScreen(FEOwner *owner, int a2, int a3, int a4)
    : FEScreen(0, 3, owner)
{
    mField164 = 0;
    mField168 = 0;
    mField170 = 0;
    mField16C = 0;
    mField184 = a4;
    mField188 = a3;
    mField18C = a2;
    mField178 = 0;
    mField17C = 1.0f;
    mField180 = 0;
    mCredits190 = 0;
    mSub198 = 0;
    mStream194 = 0;
    if (a2 == 2 && a3 == 5)
    {
        mCredits190 = func_00192130(0x19, 0x94, gMovCreditData282F68, FindFont1264A8("font_body"), 100.0f);
        mField170 = 10;
        mStream194 = func_00143100("BGM:pean_hip", 4);
        func_001432A0(mStream194, 1.0f);
        mSub198 = (FEMovSub198 *)func_00113FA0();
    }
}

// Draws the movie (and a line of text over it while mField188/18C/180 say so), the 3D part
// (mSub198), the credits, and a black fade whose alpha follows sin((1 - mField17C) * pi).
void FEMovScreen::VirtSlot3()
{
    if (mField164 != 0 && mField16C != 0)
    {
        func_00196E38(mField164);
        if (mField188 != 0 && mField18C == 1 && mField180 != 0)
        {
            DrawBegin19A640();
            TEXT_ADD_ALIGN(mText14, 2);
            TEXT_SET_POS(mText14, 500.0f, 100.0f, 0.0f);
            TEXT_SET_STRING(mText14, func_00151D40(3));
            mText14->mScale1C.Set(0.5f, 0.5f, 1.0f);
            TEXT_SET_RGBA(mText14, 0x80808080);
            DrawText19B758(mText14);
            DrawEnd19A6B0();
        }
    }
    if (mSub198 != 0)
        mSub198->Draw114178();
    if (mCredits190 != 0)
    {
        DrawBegin19A640();
        func_00192350(mCredits190);
        DrawEnd19A6B0();
    }
    if (mField17C > 0.0f)
    {
        f32 alpha = Sin1B1910((1.0f - mField17C) * 3.1415927f);
        DrawBegin19A640();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_TRIANGLE_STRIP);
        glColor4f(0.0f, 0.0f, 0.0f, alpha);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1000.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1000.0f, 0.0f);
        glVertex3f(1000.0f, 1000.0f, 0.0f);
        glEnd();
        glDisable(GL_BLEND);
        DrawEnd19A6B0();
    }
}

FEMovScreen::~FEMovScreen()
{
    if (mField164 != 0)
    {
        func_00197200(mField164);
        mField164 = 0;
    }
    if (mCredits190 != 0)
        func_00192248(mCredits190);
    if (mSub198 != 0)
        mSub198->Destroy114C88();
    if (mStream194 != 0)
    {
        func_00143270(mStream194);
        func_00143170(mStream194, 4);
    }
}

int FEMovScreen::VirtSlot7()
{
    return mField168;
}

// 6. FELoadStateScreen
FELoadStateScreen::FELoadStateScreen(FEOwner *owner, void *mc, int mode)
    : FEScreen(0x20, 1, owner)
{
    mText168 = CreateTextObj198E48(FindFont1264A8("font_body"), 0, 0.0f, 0.0f, 0.0f);
    mTimer16C = 0.0f;
    mMode164 = mode;
    mField170 = 0;
    mField174 = 0;
    if (mode == 0)
        mTitleId28 = 0x22;
    for (u32 i = 0; i < 8; i++)
        mSlots17C[i].mState00 = 0;
    mMc3BC = mc;
    mState178 = 1;
    mDialog3C0 = 0;
}

FELoadStateScreen::~FELoadStateScreen()
{
    Release198F38(mText168);
    if (mDialog3C0 != 0)
        CleanupDialog1309E0(mDialog3C0);
}

void FELoadStateScreen::VirtSlot3()
{
    FEScreen::VirtSlot3();
    DrawBegin19A640();
    switch (mState178)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    case 6:
        if (mDialog3C0 != 0)
            func_00158140(mDialog3C0, mText168, 0, 0, 400.0f, 600.0f);
        break;
    }
    DrawEnd19A6B0();
    func_00158330(mMc3BC, 1);
}

int FELoadStateScreen::VirtSlot7()
{
    return mField174;
}

int FELoadStateScreen::VirtSlot8()
{
    return mField170;
}

void FELoadStateScreen::VirtSlot4()
{
}

// 7. FELevelScreen
// Draws the selected level's information: the goals done there (string 0x42; each level has 7), how many
// more unlock the next level (0x43, when any), the "Scooters" collectibles found there (0x44, of 20),
// and the key (GetLevelKey155310) and race (mRaceOpen4D4, a checkered flag in the game) icons while
// mArr174[1] / mArr174[2] are set; both are drawn with the glyph "\x80\x18" here.
void FELevelScreen::VirtSlot3()
{
    char line[0x40];
    char line2[0x80];

    FEScreen::VirtSlot3();
    DrawBegin19A640();
    if (mMenu0C->mSelected0C != 7)
    {
        sprintf(line, func_00151D40(0x42), GetLevelGoals1550D8(mMenu0C->mSelected0C));
        mText164->mPos04.Set(570.0f, 710.0f, 0.0f);
        mText164->mScale1C.Set(0.6f, 0.6f, 1.0f);
        TEXT_SET_RGBA(mText164, 0x80808080);
        TEXT_SET_STRING(mText164, line);
        DrawText19B758(mText164);
        int count = GetGoalsToUnlock155130();
        if (count > 0)
        {
            sprintf(line, func_00151D40(0x43), count);
            mText164->mPos04.Set(570.0f, 290.0f, 0.0f);
            TEXT_SET_STRING(mText164, line);
            DrawText19B758(mText164);
        }
    }
    sprintf(line2, func_00151D40(0x44), GetLevelScooters156118(mMenu0C->mSelected0C));
    mText164->mPos04.Set(570.0f, 660.0f, 0.0f);
    mText164->mScale1C.Set(0.6f, 0.6f, 1.0f);
    TEXT_SET_RGBA(mText164, 0x80808080);
    TEXT_SET_STRING(mText164, line2);
    DrawText19B758(mText164);
    mText164->mScale1C.Set(1.0f, 1.0f, 1.0f);
    TEXT_SET_RGBA(mText164, 0x80808080);
    TEXT_SET_STRING(mText164, "\x80\x18");
    if (mArr174[1] != 0 && GetLevelKey155310(mMenu0C->mSelected0C) != 0)
    {
        mText164->mPos04.Set(700.0f, 400.0f, 0.0f);
        DrawText19B758(mText164);
    }
    if (mArr174[2] != 0 && gGameCtx262250->mRaceOpen4D4[mMenu0C->mSelected0C] != 0)
    {
        mText164->mPos04.Set(820.0f, 430.0f, 0.0f);
        DrawText19B758(mText164);
    }
    DrawEnd19A6B0();
}

FELevelScreen::FELevelScreen(FEOwner *owner)
    : FEScreen(0x40, 2, owner)
{
    CreateMenuA(GetLevelMenuIds155228(), 8);
    mField16C = -1;
    mField170 = -1;
    mText164 = CreateTextObj198E48(FindFont1264A8("font_body"), 0, 0.0f, 0.0f, 0.0f);
    mField168 = 0;
    for (int i = 0; i < 3; i++)
        mArr174[i] = 1;
}

FELevelScreen::~FELevelScreen()
{
    Release198F38(mText164);
}

void FELevelScreen::UpdateLevels16A920()
{
    for (int i = 0; i <= gGameCtx262250->mMaxLevel39C; i++)
        mMenu0C->EnableItem(i);
    for (int i = gGameCtx262250->mMaxLevel39C + 1; i < 8; i++)
        mMenu0C->DisableItem(i);
}

#ifdef NON_MATCHING
void FELevelScreen::VirtSlot4()
{
    gGameCtx262250->mField18 = mField168;
    gGameCtx262250->mField14 = mMenu0C->mSelected0C;
}
#endif

// FEMenu (0x0016AFB8..0x0016BC90, between FELoadStateScreen and FENameSelectScreen)
void FEMenu::Init()
{
    mSelected0C = 0;
    mField10 = 0;
    mField14 = 0;
    mAlt24 = 0;
    mField18 = 0;
    mState1C = 0;
    mField30 = 0;
    mField20 = -1;
    mField28 = 1;
    mSelectSound34 = HashStringCRC32("mnu_selectitem");
    mCancelSound38 = HashStringCRC32("mnu_cancel");
    mText2C = CreateTextObj198E48(FindFont1264A8("font_body"), 0, 0.0f, 0.0f, 0.0f);
    for (int i = 0; i < mCount04; i++)
    {
        mItems08[i].mDisabled100 = 0;
        mItems08[i].mModel104 = 0;
        mItems08[i].mModel10C = 0;
        mItems08[i].mModel108 = 0;
        mItems08[i].mSub110 = 0;
        mItems08[i].mTextWidth114 = 100.0f;
        if (i < mOwner00->mCount44)
        {
            mItems08[i].mModel104 = func_001262E0(mOwner00->mEntries48[i].mField00);
            mItems08[i].mModel108 = func_001262E0(mOwner00->mEntries48[i].mField04);
            mItems08[i].mModel10C = func_001262E0(mOwner00->mEntries48[i].mField08);
            UnkRes126250 *res = func_00126250(mOwner00->mEntries48[i].mField0C);
            if (res != 0)
                mItems08[i].mSub110 = new FESub08(mOwner00->mEntries48[i].mField0C, &res->mVec18, &res->mVec24);
            else
                mItems08[i].mSub110 = new FESub08(mOwner00->mEntries48[i].mField0C, 0, 0);
            if (mItems08[i].mSub110 != 0)
            {
                f32 v = mItems08[i].mSub110->Method1304E8(0xFFFF);
                mItems08[i].mSub110->Method130720(v);
            }
        }
    }
}

// Reads the pads (the first one, or all four), moves the selection (playing "mnu_p1select") and
// sets the confirm/cancel state; then updates each item's FESub08.
void FEMenu::Update(int allPads, int active, f32 dt)
{
    u32 held = gFEPads2659A0[0]->mButtons1C;
    u32 pressed = gFEPads2659A0[0]->mPressed20;
    if (allPads)
    {
        for (int p = 0; p < 4; p++)
        {
            held |= gFEPads2659A0[p]->mButtons1C;
            pressed |= gFEPads2659A0[p]->mPressed20;
        }
    }
    if (mState1C != 0 && held != 0)
        mField18 = 1;
    if (active)
    {
        if (pressed & 0x40000000)
        {
            PlaySoundCRC141520(HashStringCRC32("mnu_p1select"));
            mSelected0C = (mSelected0C + mCount04 - 1) % mCount04;
            SkipDisabledBackward();
        }
        if (pressed & 0x10000000)
        {
            PlaySoundCRC141520(HashStringCRC32("mnu_p1select"));
            mSelected0C = (mSelected0C + 1) % mCount04;
            SkipDisabledForward();
        }
        for (int p = 0; allPads ? p < 4 : p < 1; p++)
        {
            if ((gFEPads2659A0[p]->mButtons1C & 0x80000) && mItems08[mSelected0C].mDisabled100 == 0 &&
                mState1C == 0 && mField28 != 0)
            {
                if (mSelectSound34 != 0)
                    PlaySoundCRC141520(mSelectSound34);
                mState1C = 1;
                mField20 = p;
            }
        }
        if (held & 0x100000)
        {
            if (mCancelSound38 != 0)
                PlaySoundCRC141520(mCancelSound38);
            mAlt24 = 1;
        }
        else
        {
            mAlt24 = 0;
        }
        if ((int)pressed < 0)
            mField10 = 1;
        else
            mField10 = 0;
        if (pressed & 0x20000000)
            mField14 = 1;
        else
            mField14 = 0;
    }
    for (int i = 0; i < mCount04; i++)
    {
        if (mItems08[i].mSub110 != 0)
        {
            mItems08[i].mSub110->Update130348(dt);
            if (mItems08[i].mSub110->mFlags80 & 0x100)
                PlaySoundCRC141520(mItems08[i].mSub110->mSound84);
        }
    }
}

// Draws each item's models at its FESub08's matrix, then its text (turned to face the camera) in the
// owner's normal, selected or disabled colour.
#ifdef NON_MATCHING
// 7 of 175 instructions differ: the text pointer of the string and flag statements gets $v1/$a0 where
// the game has $a0/$v1. TEXT_SET_SCALE and TEXT_SET_COLOR (FEScreen.h) took it from 55 to 7; wrapping
// the string or the flag, or reordering them, did not help.
void FEMenu::Draw()
{
    for (int i = 0; i < mCount04; i++)
    {
        glPushMatrix();
        if (mItems08[i].mSub110 != 0)
            glMultMatrixf(&mItems08[i].mSub110->mMatrix40.row[0].x);
        if (mItems08[i].mDisabled100 != 0)
        {
            if (mItems08[i].mModel10C != 0)
                DrawModel196110(mItems08[i].mModel10C);
        }
        else
        {
            if (mItems08[i].mModel104 != 0)
                DrawModel196110(mItems08[i].mModel104);
            if (i == mSelected0C && mItems08[i].mModel108 != 0)
                DrawModel196110(mItems08[i].mModel108);
        }
        glPopMatrix();
    }
    for (int i = 0; i < mCount04; i++)
    {
        glPushMatrix();
        if (mItems08[i].mSub110 != 0)
            glMultMatrixf(&mItems08[i].mSub110->mMatrix40.row[0].x);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        TEXT_SET_POS(mText2C, 0.0f, 0.0f, 0.0f);
        TEXT_SET_SCALE(mText2C, mOwner00->mTextScaleE8, mOwner00->mTextScaleEC, 1.0f);
        mText2C->mString30 = mItems08[i].mText00;
        mText2C->mAlign00 |= 0x20;
        if (i == mSelected0C)
            TEXT_SET_COLOR(mText2C, mOwner00->mColourFC.x, mOwner00->mColourFC.y, mOwner00->mColourFC.z);
        else if (mItems08[i].mDisabled100 != 0)
            TEXT_SET_COLOR(mText2C, mOwner00->mColour108.x, mOwner00->mColour108.y, mOwner00->mColour108.z);
        else
            TEXT_SET_COLOR(mText2C, mOwner00->mColourF0.x, mOwner00->mColourF0.y, mOwner00->mColourF0.z);
        DrawText19B758(mText2C);
        mItems08[i].mTextWidth114 = mText2C->mWidth34;
        glPopMatrix();
    }
}
#endif

FEMenu::FEMenu(const char **strings, int count, FEOwner *owner)
{
    mCount04 = count;
    mItems08 = new FEMenuItem[count];
    for (int i = 0; i < mCount04; i++)
        strcpy(mItems08[i].mText00, strings[i]);
    mOwner00 = owner;
    Init();
}

FEMenu::FEMenu(const int *ids, int count, FEOwner *owner)
{
    mCount04 = count;
    mItems08 = new FEMenuItem[count];
    for (int i = 0; i < mCount04; i++)
        strcpy(mItems08[i].mText00, func_00151D40(ids[i]));
    mOwner00 = owner;
    Init();
}

FEMenu::~FEMenu()
{
    for (int i = 0; i < mCount04; i++)
    {
        if (mItems08[i].mSub110 != 0)
            delete mItems08[i].mSub110;
    }
    if (mItems08 != 0)
        delete[] mItems08;
    Release198F38(mText2C);
}

void FEMenu::DisableItem(int idx)
{
    mItems08[idx].mDisabled100 = 1;
    if (idx == mSelected0C)
        SkipDisabledForward();
}

void FEMenu::EnableItem(int idx)
{
    mItems08[idx].mDisabled100 = 0;
}

// Moves the selection to the next item that is not disabled, wrapping around (at most once round).
void FEMenu::SkipDisabledForward()
{
    int sel = mSelected0C;
    FEMenuItem *items = mItems08;
    int n = 0;
    if (items[sel].mDisabled100 != 0)
    {
        if (mCount04 > 0)
        {
            do
            {
                sel = mSelected0C = (sel + 1) % mCount04;
                if (items[sel].mDisabled100 == 0)
                    break;
            } while (++n < mCount04);
        }
    }
}

void FEMenu::SkipDisabledBackward()
{
    int sel = mSelected0C;
    FEMenuItem *items = mItems08;
    int n = 0;
    if (items[sel].mDisabled100 != 0)
    {
        if (mCount04 > 0)
        {
            do
            {
                sel = mSelected0C = (sel - 1 + mCount04) % mCount04;
                if (items[sel].mDisabled100 == 0)
                    break;
            } while (++n < mCount04);
        }
    }
}

void FEMenu::Action16BAD8()
{
    for (int i = 0; i < mCount04; i++)
    {
        if (mItems08[i].mSub110 != 0)
            mItems08[i].mSub110->Method1306B0();
    }
    mField30 = 1;
}

Mat4x4f *FEMenu::GetItemMatrix(int idx)
{
    return &mItems08[idx].mSub110->mMatrix40;
}

f32 FEMenu::GetItemTextWidth(int idx)
{
    return mItems08[idx].mTextWidth114;
}

void FEMenu::SetTextIds(const int *ids)
{
    for (int i = 0; i < mCount04; i++)
        strcpy(mItems08[i].mText00, func_00151D40(ids[i]));
}

void FEMenu::SetTexts(const char **strings)
{
    for (int i = 0; i < mCount04; i++)
        strcpy(mItems08[i].mText00, strings[i]);
}

// 8. FENameSelectScreen
FENameSelectScreen::~FENameSelectScreen()
{
    Release198F38(mText164);
}

int FENameSelectScreen::VirtSlot7()
{
    return mField388;
}

int FENameSelectScreen::VirtSlot8()
{
    return mField38C;
}

// 9. FEOptionsScreen
#ifdef NON_MATCHING
// 166 of 186 instructions differ: the game's frame has 0x100 bytes of locals (as here) but one more
// saved register ($fp), so its register allocation differs throughout; the text macros did not help.
// Draws each option's value right of its menu item: on/off (strings 0x27/0x28), a time as m:ss, a
// fixed string, or the option's bar (FESlider).
void FEOptionsScreen::VirtSlot3()
{
    char value[0x100];

    FEScreen::VirtSlot3();
    mText168->mScale1C.Set(mOwner00->mTextScaleE8, mOwner00->mTextScaleEC, 1.0f);
    mText168->mAlign00 |= 0x20;
    for (int i = 0; i < mCount16C; i++)
    {
        glPushMatrix();
        glMultMatrixf(&mMenu0C->GetItemMatrix(i)->row[0].x);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        if (i == mMenu0C->mSelected0C)
            mText168->SetColor(mOwner00->mColourFC.x, mOwner00->mColourFC.y, mOwner00->mColourFC.z);
        else
            mText168->SetColor(mOwner00->mColourF0.x, mOwner00->mColourF0.y, mOwner00->mColourF0.z);
        mText168->mPos04.Set(mMenu0C->GetItemTextWidth(i) + 0.1f, 0.0f, 0.0f);
        switch (mKinds170[i])
        {
        case 1:
            sprintf(value, "%s", func_00151D40(mValues1C0[i] == 0 ? 0x28 : 0x27));
            mText168->mString30 = value;
            DrawText19B758(mText168);
            break;
        case 3:
        {
            int t = (int)GetVersusTime154EA8(mValues1C0[i]);
            sprintf(value, "%d:%02d", t / 60, t % 60);
            mText168->mString30 = value;
            DrawText19B758(mText168);
            break;
        }
        case 4:
            sprintf(value, "%s", func_00151D40(1));
            mText168->mString30 = value;
            DrawText19B758(mText168);
            break;
        case 2:
            mSliders210[i]->Draw187AB8(mMenu0C->GetItemTextWidth(i) + 0.1f, 0.1f);
            break;
        }
        glPopMatrix();
    }
}
#endif

// Builds the options menu (mode 0), Audio options (1) or 2 player options (2): the items' string ids
// and kinds come from tables, the bars are made anew, and the values are read from the game context.
void FEOptionsScreen::InitMenu16C6D8(int mode)
{
    const int *kinds;
    const int *ids;

    mMode164 = mode;
    switch (mode)
    {
    case 0:
    default:
        mCount16C = 8;
        kinds = gOptionsMenuKinds2627C8;
        ids = gOptionsMenuIds2627A8;
        break;
    case 1:
        mCount16C = 5;
        kinds = gAudioMenuKinds262800;
        ids = gAudioMenuIds2627E8;
        break;
    case 2:
        mCount16C = 4;
        kinds = gTwoPlayerMenuKinds262828;
        ids = gTwoPlayerMenuIds262818;
        break;
    }
    CreateMenuA(ids, mCount16C);
    mMenu0C->mSelectSound34 = 0;
    mMenu0C->mCancelSound38 = 0;
    for (int i = 0; i < mCount16C; i++)
    {
        mKinds170[i] = kinds[i];
        mValues1C0[i] = 0;
        if (mSliders210[i] != 0)
        {
            delete mSliders210[i];
            mSliders210[i] = 0;
        }
        if (mKinds170[i] == 2)
            mSliders210[i] = new FESlider(0.0f, 1.4f, 0.25f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
    }
    switch (mode)
    {
    case 0:
    default:
        mValues1C0[0] = gGameCtx262250->mActionCameras;
        mValues1C0[1] = gGameCtx262250->mVibration;
        mValues1C0[2] = gGameCtx262250->mBalanceMeter;
        break;
    case 1:
        mValues1C0[0] = gGameCtx262250->mInGameMusic;
        mSliders210[2]->mValue10 = gGameCtx262250->mFxVolume;
        mSliders210[1]->mValue10 = gGameCtx262250->mMusicVolume;
        mFxVolume26C = gGameCtx262250->mFxVolume;
        break;
    case 2:
        mValues1C0[0] = gGameCtx262250->mVersusTime;
        mValues1C0[1] = gGameCtx262250->mVersusDegradation;
        break;
    }
}

FEOptionsScreen::FEOptionsScreen(FEOwner *owner, int a2, int a3)
    : FEScreen(0x29, 1, owner)
{
    mField264 = 0;
    mField268 = 0;
    for (int i = 0; i < 20; i++)
    {
        mKinds170[i] = 0;
        mValues1C0[i] = 0;
        mSliders210[i] = 0;
    }
    if (a3 != 0)
        func_00156200();
    InitMenu16C6D8(0);
    mText168 = CreateTextObj198E48(FindFont1264A8("font_body"), 0, 0.0f, 0.0f, 0.0f);
    mField260 = a2;
}

FEOptionsScreen::~FEOptionsScreen()
{
    Release198F38(mText168);
    for (int i = 0; i < mCount16C; i++)
    {
        if (mSliders210[i] != 0)
            delete mSliders210[i];
    }
}

int FEOptionsScreen::VirtSlot8()
{
    return mField264;
}

int FEOptionsScreen::VirtSlot7()
{
    return mField268;
}

// 10. FEScooterScreen
// Draws each player's scooter (two models, with the texture of the player's choice, turned by
// mSpin1BC) and its name, then the scooter's stats panel, through the screen's camera.
void FEScooterScreen::VirtSlot3()
{
    Mat4x4f view;
    Mat4x4f m60;
    Mat4x4f proj;

    FEScreen::VirtSlot3();
    func_00191F80(mCam1B8, &view, &m60);
    func_00191FD0(mCam1B8, &proj);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadMatrixf(&proj.row[0].x);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(&view.row[0].x);
    for (int i = 0; i < mCount164; i++)
    {
        int side;
        f32 x0;
        f32 panelX;
        if (mCount164 >= 2)
        {
            x0 = 0.0f;
            panelX = 400.0f;
            side = i * 2 - 1;
        }
        else
        {
            x0 = -1.0f;
            panelX = 200.0f;
            side = 1;
        }
        glPushMatrix();
        glTranslatef(x0 + side * 0.7f, -0.9f, 0.0f);
        int sel = mArr260[i];
        mText2B4->mPos04.Set(0.0f, -0.2f, 0.0f);
        mText2B4->mScale1C.Set(0.003f, 0.003f, 1.0f);
        TEXT_SET_STRING(mText2B4, func_00151D40(func_001561C8()[sel]));
        TEXT_ADD_ALIGN(mText2B4, 2);
        DrawText19B758(mText2B4);
        f32 angle = side * 40.0f;
        glRotatef(-mSpin1BC * angle, 0.0f, 1.0f, 0.0f);
        if (mPairs1E8[sel].mModel00 != 0)
        {
            void *tex = func_00126280(mDefs1C0[sel]->mTexIds1DC[mArr238[i]]);
            if (tex != 0)
                func_00196430(mPairs1E8[sel].mModel00, tex);
            DrawModel196110(mPairs1E8[sel].mModel00);
        }
        if (mPairs1E8[sel].mModel04 != 0)
        {
            void *tex = func_00126280(mDefs1C0[sel]->mTexIds1DC[mArr238[i]]);
            glTranslatef(0.0f, 0.46f, 0.3f);
            if (tex != 0)
                func_00196430(mPairs1E8[sel].mModel04, tex);
            DrawModel196110(mPairs1E8[sel].mModel04);
        }
        glPopMatrix();
        func_00121428(mDefs1C0[sel], mText2B4, 0, panelX + side * 350.0f, 750.0f, 4.0f, 8.0f, 0.5f, 2.0f, 1.0f,
                      2.0f, 3.0f, 17.0f, 0.5f, 2.0f);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

FEScooterScreen::~FEScooterScreen()
{
    func_00191E40(mCam1B8);
    Release198F38(mText2B4);
}

void FEScooterScreen::VirtSlot4()
{
    for (int i = 0; i < mCount164; i++)
        func_00155F40(mArr168[i], mArr260[i], mArr238[i]);
}

int FEScooterScreen::VirtSlot7()
{
    int ok = 1;
    for (int i = 0; i < mCount164; i++)
    {
        if (mReady288[i] == 0)
            ok = 0;
    }
    return ok;
}

int FEScooterScreen::VirtSlot8()
{
    return mField2B0;
}

// 11. FECharacterScreen
// Draws each player's character and name, then the stats panel (func_00121428) of the character the
// player has chosen, through the screen's camera.
void FECharacterScreen::VirtSlot3()
{
    Mat4x4f view;
    Mat4x4f m60;
    Mat4x4f proj;
    char line[0x80];

    FEScreen::VirtSlot3();
    func_00191F80(mCam314, &view, &m60);
    func_00191FD0(mCam314, &proj);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadMatrixf(&proj.row[0].x);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadMatrixf(&view.row[0].x);
    for (int i = 0; i < mCount164; i++)
    {
        glPushMatrix();
        int side;
        f32 x0;
        f32 panelX;
        if (mCount164 >= 2)
        {
            x0 = 0.0f;
            panelX = 400.0f;
            side = i * 2 - 1;
        }
        else
        {
            x0 = -1.0f;
            panelX = 200.0f;
            side = 1;
        }
        glTranslatef(x0 + side * 0.8f, -0.85f, 0.0f);
        glRotatef(side * -30.0f, 0.0f, 1.0f, 0.0f);
        if (mModels1D4[i] != 0 && mClosing34C == 0 && mArr24C[i] == 0)
            func_00119560(mModels1D4[i], 0, 1);
        mText320->mPos04.Set(0.0f, 0.0f, 0.0f);
        mText320->mScale1C.Set(0.003f, 0.003f, 1.0f);
        TEXT_SET_STRING(mText320, func_00151D40(func_00155F30()[mArr2C4[i]]));
        TEXT_ADD_ALIGN(mText320, 2);
        DrawText19B758(mText320);
        glPopMatrix();
        sprintf(line, func_00151D40(0x4F), mArr29C[i] + 1);
        func_00121428(mStats1FC[mArr29C[i]], mText320, line, panelX + side * 340.0f, 550.0f, -12.0f, 3.0f, -5.0f,
                      7.0f, 4.5f, 2.0f, -7.0f, 5.0f, 0.55f, 0.4f);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

FECharacterScreen::~FECharacterScreen()
{
    int i;
    for (i = 0; i < mCount164; i++)
    {
        if (mModels1D4[i] != 0)
            func_0011A820(mModels1D4[i]);
    }
    func_00191E40(mCam314);
    for (i = 0; i < 10; i++)
    {
        if (mSounds324[i] != 0)
            func_00141950(mSounds324[i], 3);
    }
    Release198F38(mText320);
}

void FECharacterScreen::VirtSlot4()
{
    for (int i = 0; i < mCount164; i++)
    {
        func_00155ED0(mArr168[i], mArr2C4[i], mArr274[i]);
        gGameCtx262250->mArr30C[mArr168[i]] = mArr29C[i];
    }
}

int FECharacterScreen::Helper16A030()
{
    int ok = 1;
    for (int i = 0; i < mCount164; i++)
    {
        if (mReady2EC[i] == 0)
            ok = 0;
    }
    return ok;
}

int FECharacterScreen::VirtSlot5()
{
    if (mClosing34C != 0)
        return mCloseTimer350-- <= 0;
    if (mState38 == 3)
    {
        mClosing34C = 1;
        mCloseTimer350 = 5;
    }
    return 0;
}

int FECharacterScreen::VirtSlot6()
{
    if (mField318 != 0)
        return 1;
    int allLoaded = 1;
    for (int i = 0; i < mCount164; i++)
    {
        if (mModels1D4[i] != 0 && !func_0011A470(mModels1D4[i]))
            allLoaded = 0;
    }
    return allLoaded || mField31C != 0;
}

int FECharacterScreen::VirtSlot7()
{
    int ok = 1;
    for (int i = 0; i < mCount164; i++)
    {
        if (mReady2EC[i] == 0)
            ok = 0;
    }
    return ok;
}

int FECharacterScreen::VirtSlot8()
{
    return mField318;
}
