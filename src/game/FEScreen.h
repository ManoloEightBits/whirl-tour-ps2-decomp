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

struct FEPad
{
    char field_0x00[0x1C];
    u32 mButtons1C; // 0x1C
};

extern FEPad *gFEPad2659B0; // 0x002659B0
extern FEPad *gFEPad2659B4; // 0x002659B4

class FEScreen
{
public:
    FEScreen();
    FEScreen(int a, int b, void *c); // 0x0016E458
    virtual ~FEScreen();             // slot 1: 0x0016E5B0
    virtual void VirtSlot2(f32 dt);  // slot 2: 0x0016DF98
    virtual void VirtSlot3();        // slot 3: 0x0016E180
    virtual void VirtSlot4();        // slot 4: 0x0016E450
    virtual int VirtSlot5();         // slot 5: 0x0016E860
    virtual int VirtSlot6();         // slot 6: 0x0016E878
    virtual int VirtSlot7();         // slot 7: 0x0016E880
    virtual int VirtSlot8();         // slot 8: 0x0016E888

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
    FEQuitScreen(void *owner);      // 0x001150B8
    virtual ~FEQuitScreen();        // 0x00115148
    virtual void VirtSlot2(f32 dt); // 0x001151A0
    virtual void VirtSlot3();       // 0x00115260
    virtual int VirtSlot7();        // 0x001152B8
    virtual int VirtSlot8();        // 0x001152C0

    int mField164;    // 0x164
    int mField168;    // 0x168
    void *mDialog16C; // 0x16C
    void *mFont170;   // 0x170
};

class FEStartScreen : public FEScreen
{
public:
    FEStartScreen(void *owner);     // 0x0016EC80
    virtual ~FEStartScreen();       // 0x0016ECD0
    virtual void VirtSlot2(f32 dt); // 0x0016ECF8
    virtual void VirtSlot3();       // 0x0016E9D8
    virtual int VirtSlot7();        // 0x0016ED88
    virtual int VirtSlot8();        // 0x0016ED90

    int mField164;  // 0x164
    int mField168;  // 0x168
    f32 mTimer16C;  // 0x16C
};

struct FETrickSub164
{
    char field_0x00[0x248];
    FETrickSub164(int a, int *b, FEPad **c, int d); // 0x00188088
    ~FETrickSub164();                               // 0x00188FC0
    void Update188390(f32 dt);                      // 0x00188390
    void Draw188930();                              // 0x00188930
    int GetStatus189090();                          // 0x00189090
};

class FETrickScreen : public FEScreen
{
public:
    FETrickScreen(void *owner);     // 0x0016EDE8
    virtual ~FETrickScreen();       // 0x0016EE78
    virtual void VirtSlot2(f32 dt); // 0x0016EED0
    virtual void VirtSlot3();       // 0x0016EF10
    virtual int VirtSlot7();        // 0x0016EF40

    FETrickSub164 *mSub164; // 0x164
    int mField168;          // 0x168
    int mField16C;          // 0x16C
    FEPad *mPad170;         // 0x170
    FEPad *mPad174;         // 0x174
};

#endif
