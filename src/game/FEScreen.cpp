#include "game/FEScreen.h"
#include "game/GL.h"

void Release198F38(void *);           // 0x00198F38
void *FindFont1264A8(const char *name); // 0x001264A8
void *func_001262E0(int);               // 0x001262E0
UnkRes126250 *func_00126250(int);       // 0x00126250
const char *func_00151D40(u16 id);      // 0x00151D40
void DrawBegin19A640();                 // 0x0019A640
void DrawEnd19A6B0();                   // 0x0019A6B0
void DrawModel196110(void *model);      // 0x00196110

// Draws the menu, the screen's model where its FESub08 places it, the title (string id mTitleId28,
// shrunk to fit a width of 4.0) and, while fading (mField34 == 3), a black quad with alpha mField2C.

void FEScreen::VirtSlot3()
{
    if (mMenu0C != 0)
        mMenu0C->Draw();
    if (mModel04 != 0 && mSub08 != 0)
    {
        glPushMatrix();
        glMultMatrixf(&mSub08->mMatrix40.row[0].x);
        DrawModel196110(mModel04);
        glPopMatrix();
        glPushMatrix();
        Vec3f *p = mSub08->GetPosition();
        Vec3f pos;
        pos.x = p->x;
        pos.y = p->y;
        pos.z = p->z;
        glTranslatef(pos.x, pos.y, pos.z);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        mText14->mString30 = func_00151D40(mTitleId28);
        TEXT_SET_POS(mText14, 0.0f, 0.0f, 0.0f);
        TEXT_SET_SCALE(mText14, mOwner00->mTitleScale28, mOwner00->mTitleScale2C, 1.0f);
        TEXT_SET_COLOR(mText14, mOwner00->mTitleColour30.x, mOwner00->mTitleColour30.y, mOwner00->mTitleColour30.z);
        mText14->mAlign00 |= 0x12;
        MeasureText19B138(mText14);
        if (mText14->mWidth34 > 4.0f)
            mText14->mScale1C.Set(mOwner00->mTitleScale28 * 4.0f / mText14->mWidth34, mOwner00->mTitleScale2C,
                                  1.0f);
        DrawText19B758(mText14);
        glPopMatrix();
    }
    if (mField34 == 3 && mState38 != 1)
    {
        DrawBegin19A640();
        glEnable(GL_BLEND);
        glColor4f(0.0f, 0.0f, 0.0f, mField2C);
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1000.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1000.0f, 0.0f);
        glVertex3f(1000.0f, 1000.0f, 0.0f);
        glEnd();
        glDisable(GL_BLEND);
        DrawEnd19A6B0();
    }
}

void FEScreen::VirtSlot4()
{
}

#ifdef NON_MATCHING
// 7 of 85 instructions differ: the constants 1, 8 and 9 of mField18..mField24 get $v1/$a3/$t0 where the
// game has $a3/$t0/$v1. The member initializer list (or assignments in declaration order) gets every
// store and the vtable pointer in place; 24 orders of the four constant assignments in the body got 5.
FEScreen::FEScreen(int titleId, int state, FEOwner *owner)
    : mOwner00(owner), mMenu0C(0), mPad10(gFEPad2659B0), mField18(1), mField1C(1), mField20(8), mField24(9),
      mTitleId28(titleId), mField30(0), mField34(state), mState38(0), mField3C(0), mField40(0)
{
    mText14 = CreateTextObj198E48(FindFont1264A8("font_header"), 0, 0.0f, 0.0f, 0.0f);
    mField2C = 1.0f;
    mModel04 = 0;
    mSub08 = 0;
    mModel04 = func_001262E0(owner->mField3C);
    UnkRes126250 *res = func_00126250(owner->mField3C);
    if (res != 0)
        mSub08 = new FESub08(owner->mField40, &res->mVec18, &res->mVec24);
    else
        mSub08 = new FESub08(owner->mField40, 0, 0);
    if (mSub08 != 0)
    {
        f32 v = mSub08->Method1304E8(0xFFFF);
        mSub08->Method130720(v);
    }
    mCount44 = 0;
    AddOwnerRecords();
}
#endif

FEScreen::~FEScreen()
{
    if (mMenu0C != 0)
        delete mMenu0C;
    Release198F38(mText14);
    if (mSub08 != 0)
        delete mSub08;
}

void FEScreen::CreateMenuA(const int *ids, int count)
{
    if (mMenu0C != 0)
        delete mMenu0C;
    mMenu0C = new FEMenu(ids, count, mOwner00);
}

void FEScreen::CreateMenuB(const char **strings, int count)
{
    if (mMenu0C != 0)
        delete mMenu0C;
    mMenu0C = new FEMenu(strings, count, mOwner00);
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

void FEScreen::EnableMenuItem(int idx)
{
    if (mMenu0C != 0)
        mMenu0C->EnableItem(idx);
}

void FEScreen::DisableMenuItem(int idx)
{
    if (mMenu0C != 0)
        mMenu0C->DisableItem(idx);
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

// Also inlined into AddOwnerRecords (inline here, with its copy emitted as for DD_Collision_Listener).
inline void FEScreen::AddItem48(FEOwnerRec *item)
{
    if (mCount44 < 0x46)
    {
        mItems48[mCount44++] = item;
    }
}

// Lists the owner's records whose first halfword is set (AddItem48 keeps up to 0x46).
void FEScreen::AddOwnerRecords()
{
    if (mOwner00 != 0)
    {
        for (int i = 0; i < mOwner00->mCount114; i++)
        {
            if (mOwner00->mRecs118[i].mField00 != 0)
                AddItem48(&mOwner00->mRecs118[i]);
        }
    }
}

int FEScreen::GetCount44()
{
    return mCount44;
}

void FEScreen::ClearCount44()
{
    mCount44 = 0;
}

FEOwnerRec *FEScreen::GetItem48(int idx)
{
    return mItems48[idx];
}

int FEScreen::GetMenuField20()
{
    return mMenu0C->mField20;
}
