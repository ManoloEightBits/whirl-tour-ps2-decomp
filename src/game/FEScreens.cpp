#include "game/FEScreen.h"

struct BGMInfo
{
    char *mName00;
    u8 mFlag04;
    s8 mUnlocked05;
    char pad06[2];
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
    int mTracks54[64];
    char pad154[0x1B8];
    int mArr30C[10];
    char pad334[0x50];
    BGMInfo *mBGMTable384;
    char pad388[0x14];
    int mMaxLevel39C;

    static inline GameCtxFE *Get()
    {
        extern GameCtxFE *gGameCtx262250;
        return gGameCtx262250;
    }
};
extern GameCtxFE *gGameCtx262250;

extern const int gMonsterMenuIds259F10[];
extern int gMovCreditData282F68[];

void *FindFont1264A8(const char *name);
void *CreateTextObj198E48(void *font, int, f32, f32, f32);
void Release198F38(void *);
void CleanupDialog1309E0(void *);
u32 HashStringCRC32(const char *str);
void PlaySoundCRC141520(u32 crc);
void DrawBegin19A640();
void DrawEnd19A6B0();
void func_001A2FB8(int);
void func_001A2DB8(int);
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
void func_001BD978(void *);
void *func_00192130(int, int, void *, void *, f32);
void *func_00113FA0();
void func_00197200(void *);
void func_00192248(void *);
const int *func_00155228();
void func_00158140(void *, void *, int, int, f32, f32);
void func_00156200();
void func_00187DD0(void *, int);
void func_00155F40(int, int, int);
void func_00141950(void *, int);
void func_00155ED0(int, int, int);

// 1. FEMcScreen
FEMcScreen::FEMcScreen(void *owner, int mode, void *mc)
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
    func_001A2FB8(0xB44);
    func_001A2FB8(0xB71);
    if (mMode170 != 200)
        func_00113BD0();
    func_00158330(mMc16C, 1);
    func_001A2DB8(0xB71);
    func_001A2DB8(0xB44);
    DrawEnd19A6B0();
}

int FEMcScreen::VirtSlot7()
{
    return mField164;
}

// 2. FEMonsterScreen
FEMonsterScreen::FEMonsterScreen(void *owner)
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
        mMenu0C->Action16B9C8(0);
    else
        mMenu0C->Action16B980(0);
    if (gGameCtx262250->mCount1C < 10)
        mMenu0C->Action16B9C8(1);
    else
        mMenu0C->Action16B980(1);
    if (gGameCtx262250->mCount1C > 0)
        mMenu0C->Action16B9C8(2);
    else
        mMenu0C->Action16B980(2);
    if (mMenu0C->mState1C != 0 && mMenu0C->mSelected0C == 2)
    {
        gGameCtx262250->mCount1C--;
        mMenu0C->mState1C = 0;
    }
}

// 3. FEPlaylistScreen
FEPlaylistScreen::FEPlaylistScreen(void *owner, int arg2)
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
    func_001BD978(this);
}

FEMovScreen::FEMovScreen(void *owner, int a2, int a3, int a4)
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
FELoadStateScreen::FELoadStateScreen(void *owner, void *mc, int mode)
    : FEScreen(0x20, 1, owner)
{
    mText168 = CreateTextObj198E48(FindFont1264A8("font_body"), 0, 0.0f, 0.0f, 0.0f);
    mTimer16C = 0.0f;
    mMode164 = mode;
    mField170 = 0;
    mField174 = 0;
    if (mode == 0)
        mField28 = 0x22;
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
FELevelScreen::FELevelScreen(void *owner)
    : FEScreen(0x40, 2, owner)
{
    CreateMenuA(func_00155228(), 8);
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
        mMenu0C->Action16B9C8(i);
    for (int i = gGameCtx262250->mMaxLevel39C + 1; i < 8; i++)
        mMenu0C->Action16B980(i);
}

#ifdef NON_MATCHING
void FELevelScreen::VirtSlot4()
{
    gGameCtx262250->mField18 = mField168;
    gGameCtx262250->mField14 = mMenu0C->mSelected0C;
}
#endif

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
FEOptionsScreen::FEOptionsScreen(void *owner, int a2, int a3)
    : FEScreen(0x29, 1, owner)
{
    mField264 = 0;
    mField268 = 0;
    for (int i = 0; i < 20; i++)
    {
        mArr170[i] = 0;
        mArr1C0[i] = 0;
        mArr210[i] = 0;
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
        if (mArr210[i] != 0)
            func_00187DD0(mArr210[i], 3);
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
