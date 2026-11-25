#include "game/FEScreen.h"
#include "game/GL.h"

extern FEPad *gGameCtx262250; // 0x00262250

void DrawBegin19A640();            // 0x0019A640
void DrawEnd19A6B0();              // 0x0019A6B0
const char *func_00151D40(u16 id); // 0x00151D40

// The title screen: the background picture (texture 0x2B165FC1, a CRC of its name) over the whole
// screen, string 3 at (500, 150), and the black fade while mField34 == 3.
void FEStartScreen::VirtSlot3()
{
    DrawBegin19A640();
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0x2B165FC1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0.0f, 1000.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1000.0f, 1000.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    DrawEnd19A6B0();
    DrawBegin19A640();
    TEXT_ADD_ALIGN(mText14, 2);
    TEXT_SET_POS(mText14, 500.0f, 150.0f, 0.0f);
    TEXT_SET_STRING(mText14, func_00151D40(3));
    mText14->mScale1C.Set(0.5f, 0.5f, 1.0f);
    TEXT_SET_RGBA(mText14, 0x80808080);
    DrawText19B758(mText14);
    if (mField34 == 3)
    {
        glEnable(GL_BLEND);
        glColor4f(0.0f, 0.0f, 0.0f, mField2C);
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1000.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1000.0f, 0.0f);
        glVertex3f(1000.0f, 1000.0f, 0.0f);
        glEnd();
        glDisable(GL_BLEND);
    }
    DrawEnd19A6B0();
}

FEStartScreen::FEStartScreen(FEOwner *owner)
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

FETrickScreen::FETrickScreen(FEOwner *owner)
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
