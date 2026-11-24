#ifndef GAME_FESCREEN_H
#define GAME_FESCREEN_H

#include "common/types.h"

// Whirl Tour: FEScreen (front-end screen base class, RTTI name "8FEScreen").
// Vtable at 0x002A4270 (_vt$8FEScreen), stored at offset +0x160.
struct FEMenu
{
    char field_0x00[0x0C];
    int mSelected0C;       // 0x0C
    char field_0x10[0x0C];
    int mState1C;          // 0x1C
    int mField20;          // 0x20
    int mAlt24;            // 0x24
    char field_0x28[0x14];

    FEMenu(const int *ids, int count, void *owner);         // 0x0016B810
    FEMenu(const char **strings, int count, void *owner);   // 0x0016B768
    ~FEMenu();                                              // 0x0016B8D0
    void Action16B9C8();                                    // 0x0016B9C8
    void Action16B980();                                    // 0x0016B980
};

struct FESub08
{
    ~FESub08(); // 0x001305E0
};

class FEScreen
{
public:
    FEScreen();
    FEScreen(int a, int b, void *c); // 0x0016E458
    virtual ~FEScreen();       // slot 1: 0x0016E5B0
    virtual void VirtSlot2();  // slot 2: 0x0016DF98
    virtual void VirtSlot3();  // slot 3: 0x0016E180
    virtual void VirtSlot4();  // slot 4: 0x0016E450
    virtual int VirtSlot5();   // slot 5: 0x0016E860
    virtual int VirtSlot6();   // slot 6: 0x0016E878
    virtual int VirtSlot7();   // slot 7: 0x0016E880
    virtual int VirtSlot8();   // slot 8: 0x0016E888

    void CreateMenuA(const int *ids, int count);       // 0x0016E628
    void CreateMenuB(const char **strings, int count); // 0x0016E690
    void DestroyMenu();                                // 0x0016E6F8
    int GetMenuSelection();                            // 0x0016E730
    void MenuAction16B9C8();                           // 0x0016E7B8
    void MenuAction16B980();                           // 0x0016E7E0
    int IsSlot5AndState3();                            // 0x0016E808
    void SetField3C_1();                               // 0x0016E868
    void AddItem48(int item);                          // 0x0016E890

    void *mField00;        // 0x00
    int mField04;          // 0x04
    FESub08 *mSub08;       // 0x08
    FEMenu *mMenu0C;       // 0x0C
    int mField10;          // 0x10
    void *mObj14;          // 0x14
    char field_0x18[0x20];
    int mState38;          // 0x38
    int mField3C;          // 0x3C
    int mField40;          // 0x40
    int mCount44;          // 0x44
    int mItems48[0x46];    // 0x48..0x15F (70 * 4 = 0x118 bytes -> ends at 0x160!)
};

class FEQuitScreen : public FEScreen
{
public:
    FEQuitScreen(void *owner); // 0x001150B8
    virtual ~FEQuitScreen();   // 0x00115148
    virtual void VirtSlot2();  // 0x001151A0
    virtual void VirtSlot3();  // 0x00115260
    virtual int VirtSlot7();   // 0x001152B8
    virtual int VirtSlot8();   // 0x001152C0

    int mField164;   // 0x164
    int mField168;   // 0x168
    void *mDialog16C; // 0x16C
    void *mFont170;  // 0x170
};

#endif
