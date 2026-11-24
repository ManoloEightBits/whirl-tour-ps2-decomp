#include "game/FEScreen.h"

void Release198F38(void *); // 0x00198F38

void FEScreen::VirtSlot4()
{
}

FEScreen::~FEScreen()
{
    if (mMenu0C != 0)
        delete mMenu0C;
    Release198F38(mObj14);
    if (mSub08 != 0)
        delete mSub08;
}

void FEScreen::CreateMenuA(const int *ids, int count)
{
    if (mMenu0C != 0)
        delete mMenu0C;
    mMenu0C = new FEMenu(ids, count, mField00);
}

void FEScreen::CreateMenuB(const char **strings, int count)
{
    if (mMenu0C != 0)
        delete mMenu0C;
    mMenu0C = new FEMenu(strings, count, mField00);
}

void FEScreen::DestroyMenu()
{
    if (mMenu0C != 0)
    {
        delete mMenu0C;
        mMenu0C = 0;
    }
}

int FEScreen::GetMenuSelection()
{
    if (VirtSlot7())
        return 0;
    if (VirtSlot8())
        return 999;
    if (mMenu0C != 0)
    {
        if (mMenu0C->mState1C != 0)
            return mMenu0C->mSelected0C;
        return mMenu0C->mAlt24 == 0 ? -1 : 999;
    }
    return -1;
}

void FEScreen::MenuAction16B9C8()
{
    if (mMenu0C != 0)
        mMenu0C->Action16B9C8();
}

void FEScreen::MenuAction16B980()
{
    if (mMenu0C != 0)
        mMenu0C->Action16B980();
}

int FEScreen::IsSlot5AndState3()
{
    int res = 0;
    if (VirtSlot5())
        res = (mState38 == 3);
    return res;
}

int FEScreen::VirtSlot5()
{
    return 1;
}

void FEScreen::SetField3C_1()
{
    mField3C = 1;
}

int FEScreen::VirtSlot6()
{
    return 1;
}

int FEScreen::VirtSlot7()
{
    return 0;
}

int FEScreen::VirtSlot8()
{
    return 0;
}

void FEScreen::AddItem48(int item)
{
    if (mCount44 < 0x46)
    {
        mItems48[mCount44++] = item;
    }
}
