#include "game/FEScreen.h"

u32 HashStringCRC32(const char *str);                        // 0x001B1CD0
void PlaySoundCRC141520(u32 crc);                            // 0x00141520
void *CreateDialog130960(int, int, int, void *, int);        // 0x00130960
int UpdateDialog130760(void *dlg, FEPad *pad, int mask);     // 0x00130760
void *FindFont1264A8(const char *name);                      // 0x001264A8
void Release198F38(void *);                                  // 0x00198F38
void CleanupDialog1309E0(void *);                            // 0x001309E0
void DrawBegin19A640();                                      // 0x0019A640
void DrawDialog114F10(void *, void *, f32, f32);             // 0x00114F10
void DrawEnd19A6B0();                                        // 0x0019A6B0

extern int gDialogData259EF0[]; // 0x00259EF0

FEQuitScreen::FEQuitScreen(void *owner)
    : FEScreen(0x13, 1, owner)
{
    mField164 = 0;
    mField168 = 0;
    mDialog16C = CreateDialog130960(0x14, 0, 2, gDialogData259EF0, 0);
    mFont170 = CreateTextObj198E48(FindFont1264A8("font_body"), 0, 0.0f, 0.0f, 0.0f);
}

FEQuitScreen::~FEQuitScreen()
{
    CleanupDialog1309E0(mDialog16C);
    Release198F38(mFont170);
}

void FEQuitScreen::VirtSlot2(f32 dt)
{
    FEScreen::VirtSlot2(dt);
    int res = UpdateDialog130760(mDialog16C, gFEPad2659B0, 0x80000);
    u32 btns = gFEPad2659B0->mButtons1C;
    if (btns & 0x100000)
        res = 0;
    if (btns & 0x50000000)
        PlaySoundCRC141520(HashStringCRC32("mnu_p1select"));
    if (res != 1)
    {
        if (res == 0)
        {
            mField168 = 1;
            PlaySoundCRC141520(HashStringCRC32("mnu_cancel"));
        }
    }
    else
    {
        mField164 = 1;
        PlaySoundCRC141520(HashStringCRC32("mnu_selectitem"));
    }
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
