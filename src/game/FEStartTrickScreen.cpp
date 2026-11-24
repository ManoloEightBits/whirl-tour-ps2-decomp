#include "game/FEScreen.h"

extern FEPad *gGameCtx262250; // 0x00262250

FEStartScreen::FEStartScreen(void *owner)
    : FEScreen(2, 3, owner)
{
    mField164 = 0;
    mField168 = 0;
    mTimer16C = 0.0f;
}

FEStartScreen::~FEStartScreen()
{
}

void FEStartScreen::VirtSlot2(f32 dt)
{
    FEScreen::VirtSlot2(dt);
    mTimer16C += dt;
    u32 btns = gFEPad2659B0->mButtons1C;
    if (btns & 0x08000000)
    {
        mField164 = 1;
    }
    else if ((btns & 0x100000) || mTimer16C > 30.0f)
    {
        mField168 = 1;
    }
}

int FEStartScreen::VirtSlot7()
{
    return mField164;
}

int FEStartScreen::VirtSlot8()
{
    return mField168;
}

FETrickScreen::FETrickScreen(void *owner)
    : FEScreen(0x5A, 2, owner)
{
    mField168 = 0;
    mField16C = 1;
    mPad170 = gFEPad2659B0;
    mPad174 = gFEPad2659B4;
    mSub164 = new FETrickSub164(gGameCtx262250->mButtons1C, &mField168, &mPad170, 1);
}

FETrickScreen::~FETrickScreen()
{
    if (mSub164 != 0)
        delete mSub164;
}

void FETrickScreen::VirtSlot2(f32 dt)
{
    FEScreen::VirtSlot2(dt);
    mSub164->Update188390(dt);
}

void FETrickScreen::VirtSlot3()
{
    FEScreen::VirtSlot3();
    mSub164->Draw188930();
}

int FETrickScreen::VirtSlot7()
{
    return mSub164->GetStatus189090();
}
