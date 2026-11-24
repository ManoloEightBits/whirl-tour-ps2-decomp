#include "game/FEScreen.h"

void Release198F38(void *);                         // 0x00198F38
void CleanupDialog1309E0(void *);                   // 0x001309E0
void DrawBegin19A640();                             // 0x0019A640
void DrawDialog114F10(void *, void *, f32, f32);    // 0x00114F10
void DrawEnd19A6B0();                               // 0x0019A6B0

FEQuitScreen::~FEQuitScreen()
{
    CleanupDialog1309E0(mDialog16C);
    Release198F38(mFont170);
}

void FEQuitScreen::VirtSlot3()
{
    FEScreen::VirtSlot3();
    DrawBegin19A640();
    DrawDialog114F10(mDialog16C, mFont170, 350.0f, 650.0f);
    DrawEnd19A6B0();
}

int FEQuitScreen::VirtSlot7()
{
    return mField164;
}

int FEQuitScreen::VirtSlot8()
{
    return mField168;
}
