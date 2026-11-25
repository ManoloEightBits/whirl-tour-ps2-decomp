#ifndef GAME_FESCREEN_H
#define GAME_FESCREEN_H

#include "common/types.h"

// A line of text on screen (0x3C bytes): CreateTextObj198E48(font, ...) allocates one, the screens set
// where it goes, its scale, colour and string, and draw it with DrawText19B758 between DrawBegin19A640
// and DrawEnd19A6B0. Colours are RGBA bytes with 0x80 as full intensity (the GS range).
struct TextObj
{
    int mField00;          // 0x00
    Vec3f mPos04;          // 0x04
    Vec3f mField10;        // 0x10
    Vec3f mScale1C;        // 0x1C
    u32 mColor28;          // 0x28
    void *mFont2C;         // 0x2C
    const char *mString30; // 0x30
    f32 mField34;          // 0x34: read back after drawing (FEMenu::Draw)
    int mField38;          // 0x38

    void SetColor(f32 r, f32 g, f32 b)
    {
        mColor28 = 0x80 << 24 | (int)(b * 128.0f) << 16 | (int)(g * 128.0f) << 8 | (int)(r * 128.0f);
    }
};

TextObj *CreateTextObj198E48(void *font, int, f32, f32, f32); // 0x00198E48
void DrawText19B758(TextObj *text);                          // 0x0019B758

// The object a screen's mSub08 and each menu item's mSub110 point to (0xB0 bytes). It is built from an
// id and two optional vectors of the record func_00126250 returns for that id.
struct UnkRes126250
{
    char field_0x00[0x18];
    Vec3f mVec18; // 0x18
    Vec3f mVec24; // 0x24
};

struct FESub08
{
    char field_0x00[0x40];
    Mat4x4f mMatrix40;                      // 0x40: where its menu item is drawn
    u32 mFlags80;                           // 0x80: 0x100 plays mSound84 (FEMenu::Update)
    u32 mSound84;                           // 0x84
    char field_0x88[0x28];

    FESub08(int id, Vec3f *a, Vec3f *b);    // 0x00130138
    ~FESub08();                             // 0x001305E0
    f32 Method1304E8(int);                  // 0x001304E8
    void Method1306B0();                    // 0x001306B0
    void Update130348(f32 dt);              // 0x00130348
    void Method130720(f32);                 // 0x00130720
};

// What FEScreen::mField00 and FEMenu::mOwner00 point to: an id at +0x3C, from +0x48 one 16-byte
// record per menu item (mCount44 of them: the ids of its three models and of its FESub08), and how
// FEMenu::Draw draws the items' text: scale, and colours (0..1) for normal, selected and disabled.
struct FEOwnerEntry
{
    int mField00; // 0x00
    int mField04; // 0x04
    int mField08; // 0x08
    int mField0C; // 0x0C
};

struct FEOwner
{
    char field_0x00[0x3C];
    int mField3C;                // 0x3C
    int mField40;                // 0x40
    int mCount44;                // 0x44
    FEOwnerEntry mEntries48[10]; // 0x48
    f32 mTextScaleE8;            // 0xE8
    f32 mTextScaleEC;            // 0xEC
    Vec3f mColourF0;             // 0xF0: normal
    Vec3f mColourFC;             // 0xFC: selected
    Vec3f mColour108;            // 0x108: disabled
};

// One line of a menu (0x118 bytes): its text, whether it can be selected, its models (drawn with
// DrawModel196110: normal, extra when selected, disabled), and an FESub08 that places it.
struct FEMenuItem
{
    char mText00[0x100]; // 0x000
    int mDisabled100;    // 0x100: skipped when moving the selection
    void *mModel104;     // 0x104
    void *mModel108;     // 0x108
    void *mModel10C;     // 0x10C
    FESub08 *mSub110;    // 0x110
    f32 mField114;       // 0x114: the text's mField34 after drawing
};

// A screen's menu (0x3C bytes, no RTTI): FEScreen::CreateMenuA/B build it from string ids or strings.
struct FEMenu
{
    FEOwner *mOwner00;     // 0x00
    int mCount04;          // 0x04
    FEMenuItem *mItems08;  // 0x08
    int mSelected0C;       // 0x0C
    int mField10;          // 0x10
    int mField14;          // 0x14
    int mField18;          // 0x18
    int mState1C;          // 0x1C
    int mField20;          // 0x20
    int mAlt24;            // 0x24
    int mField28;          // 0x28
    TextObj *mText2C;      // 0x2C
    int mField30;          // 0x30
    u32 mSelectSound34;    // 0x34: HashStringCRC32("mnu_selectitem")
    u32 mCancelSound38;    // 0x38: HashStringCRC32("mnu_cancel")

    void Init();                                            // 0x0016AFB8
    void Update(int allPads, int active, f32 dt);           // 0x0016B1E8
    void Draw();                                            // 0x0016B4A8
    FEMenu(const char **strings, int count, void *owner);   // 0x0016B768
    FEMenu(const int *ids, int count, void *owner);         // 0x0016B810
    ~FEMenu();                                              // 0x0016B8D0
    void DisableItem(int idx);                              // 0x0016B980
    void EnableItem(int idx);                               // 0x0016B9C8
    void SkipDisabledForward();                             // 0x0016B9E0
    void SkipDisabledBackward();                            // 0x0016BA58
    void Action16BAD8();                                    // 0x0016BAD8
    Mat4x4f *GetItemMatrix(int idx);                        // 0x0016BB50
    f32 GetItemField114(int idx);                           // 0x0016BB70
    void SetTextIds(const int *ids);                        // 0x0016BB88
    void SetTexts(const char **strings);                    // 0x0016BC18
};

// Whirl Tour: FEScreen (front-end screen base class, RTTI name "8FEScreen").
// Vtable at 0x002A4270 (_vt$8FEScreen), stored at offset +0x160.
struct FEPad
{
    char field_0x00[0x1C];
    u32 mButtons1C; // 0x1C
    int mPressed20; // 0x20
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
    void EnableMenuItem(int idx);                      // 0x0016E7B8
    void DisableMenuItem(int idx);                     // 0x0016E7E0
    int IsSlot5AndState3();                            // 0x0016E808
    void SetField3C_1();                               // 0x0016E868
    void AddItem48(int item);                          // 0x0016E890
    int GetCount44();                                  // 0x0016E9A8
    void ClearCount44();                               // 0x0016E9B0
    int GetItem48(int idx);                            // 0x0016E9B8
    int GetMenuField20();                              // 0x0016E9C8

    void *mField00;        // 0x00
    int mField04;          // 0x04
    FESub08 *mSub08;       // 0x08
    FEMenu *mMenu0C;       // 0x0C
    int mField10;          // 0x10
    void *mObj14;          // 0x14
    char field_0x18[0x10];
    int mField28;          // 0x28
    char field_0x2C[0x0C];
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

class FEPlaylistScreen : public FEScreen
{
public:
    FEPlaylistScreen(void *owner, int arg2); // 0x001121C8
    virtual ~FEPlaylistScreen();             // 0x001129F0
    virtual void VirtSlot2(f32 dt);          // 0x001122F0
    virtual void VirtSlot3();                // 0x00112578
    virtual int VirtSlot7();                 // 0x00112AF8
    virtual int VirtSlot8();                 // 0x00112B00

    void InitTracks112A78();                 // 0x00112A78

    int mField164;      // 0x164
    int mSelected168;   // 0x168
    int mCount16C;      // 0x16C
    int *mEnabled170;   // 0x170
    int *mTracks174;    // 0x174
    int mField178;      // 0x178
    int mField17C;      // 0x17C
    int mField180;      // 0x180
    void *mText184;     // 0x184
    int mPlayingIdx188; // 0x188
    f32 mTimer18C;      // 0x18C
    int mBlink190;      // 0x190
    void *mStream194;   // 0x194
};

class FEChooseScreen : public FEScreen
{
public:
    FEChooseScreen(void *owner);    // 0x00112B08
    virtual ~FEChooseScreen();      // 0x00113078
    virtual void VirtSlot2(f32 dt); // 0x00113110
    virtual void VirtSlot3();       // 0x00112D30
    virtual int VirtSlot5();        // 0x001131F0

    int mCount164;        // 0x164
    void *mModels168[10]; // 0x168..0x18F
    void *mSub190[20];    // 0x190..0x1DF
    void *mDefs1E0[10];   // 0x1E0..0x207
    void *mCam208;        // 0x208
    int mClosing20C;      // 0x20C
    int mCloseTimer210;   // 0x210
};

class FEMcScreen : public FEScreen
{
public:
    FEMcScreen(void *owner, int mode, void *mc); // 0x00113D90
    virtual ~FEMcScreen();                       // 0x00113E18
    virtual void VirtSlot2(f32 dt);              // 0x00113E50
    virtual void VirtSlot3();                    // 0x00113F28
    virtual int VirtSlot7();                     // 0x00113F98

    inline void AdvanceState168() { mState168++; } // 0x00113E40

    int mField164; // 0x164
    int mState168; // 0x168
    void *mMc16C;  // 0x16C
    int mMode170;  // 0x170
};

struct FEMovSub198
{
    char pad00[0x54];
    void *mCam54;      // 0x54
    int pad58;         // 0x58
    void *mPhys5C;     // 0x5C
    int pad60;         // 0x60
    void *mArr64[10];  // 0x64..0x8B

    inline void Destroy114C88(); // 0x00114C88
};

class FEMovScreen : public FEScreen
{
public:
    FEMovScreen(void *owner, int a2, int a3, int a4); // 0x00114CF8
    virtual ~FEMovScreen();                           // 0x00114E20
    virtual void VirtSlot2(f32 dt);                   // 0x001145F8
    virtual void VirtSlot3();                         // 0x00114A18
    virtual int VirtSlot7();                          // 0x00114F08

    void *mField164;      // 0x164
    int mField168;        // 0x168
    int mField16C;        // 0x16C
    int mField170;        // 0x170
    int mField174;        // 0x174
    int mField178;        // 0x178
    f32 mField17C;        // 0x17C
    int mField180;        // 0x180
    int mField184;        // 0x184
    int mField188;        // 0x188
    int mField18C;        // 0x18C
    void *mCredits190;    // 0x190
    void *mStream194;     // 0x194
    FEMovSub198 *mSub198; // 0x198
};

class FEMonsterScreen : public FEScreen
{
public:
    FEMonsterScreen(void *owner);   // 0x00115628
    virtual ~FEMonsterScreen();     // 0x001156B0
    virtual void VirtSlot2(f32 dt); // 0x001152C8
    virtual void VirtSlot3();       // 0x001153B8

    void *mText164; // 0x164
};

class FECharacterScreen : public FEScreen
{
public:
    FECharacterScreen(void *owner); // 0x00168F98
    virtual ~FECharacterScreen();   // 0x00169E30
    virtual void VirtSlot2(f32 dt); // 0x00169670
    virtual void VirtSlot3();       // 0x00169348
    virtual void VirtSlot4();       // 0x00169FA8
    virtual int VirtSlot5();        // 0x0016A060
    virtual int VirtSlot6();        // 0x0016A0A8
    virtual int VirtSlot7();        // 0x0016A150
    virtual int VirtSlot8();        // 0x0016A180

    void Helper169EF8(int idx);     // 0x00169EF8
    void Helper169F50(int idx);     // 0x00169F50
    int Helper16A030();             // 0x0016A030

    int mCount164;          // 0x164
    int mArr168[10];        // 0x168..0x18F
    char pad190[0x44];      // 0x190..0x1D3
    void *mModels1D4[10];   // 0x1D4..0x1FB
    char pad1FC[0x78];      // 0x1FC..0x273
    int mArr274[10];        // 0x274..0x29B
    int mArr29C[10];        // 0x29C..0x2C3
    int mArr2C4[10];        // 0x2C4..0x2EB
    int mReady2EC[10];      // 0x2EC..0x313
    void *mCam314;          // 0x314
    int mField318;          // 0x318
    int mField31C;          // 0x31C
    void *mText320;         // 0x320
    void *mSounds324[10];   // 0x324..0x34B
    int mClosing34C;        // 0x34C
    int mCloseTimer350;     // 0x350
};

class FELevelScreen : public FEScreen
{
public:
    FELevelScreen(void *owner);     // 0x0016A820
    virtual ~FELevelScreen();       // 0x0016A8D0
    virtual void VirtSlot2(f32 dt); // 0x0016A450
    virtual void VirtSlot3();       // 0x0016A188
    virtual void VirtSlot4();       // 0x0016A9C8

    void UpdateLevels16A920();      // 0x0016A920

    TextObj *mText164; // 0x164
    int mField168;  // 0x168
    int mField16C;  // 0x16C
    int mField170;  // 0x170
    int mArr174[3]; // 0x174..0x17F
};

struct FELoadSlot
{
    int mState00;
    char pad04[0x44];
};

class FELoadStateScreen : public FEScreen
{
public:
    FELoadStateScreen(void *owner, void *mc, int mode); // 0x0016ADE0
    virtual ~FELoadStateScreen();                       // 0x0016AEB8
    virtual void VirtSlot2(f32 dt);                     // 0x0016A9E8
    virtual void VirtSlot3();                           // 0x0016AF18
    virtual void VirtSlot4();                           // 0x0016AFB0
    virtual int VirtSlot7();                            // 0x0016AFA0
    virtual int VirtSlot8();                            // 0x0016AFA8

    int mMode164;           // 0x164
    void *mText168;         // 0x168
    f32 mTimer16C;          // 0x16C
    int mField170;          // 0x170
    int mField174;          // 0x174
    int mState178;          // 0x178
    FELoadSlot mSlots17C[8];// 0x17C..0x3BB
    void *mMc3BC;           // 0x3BC
    void *mDialog3C0;       // 0x3C0
};

class FENameSelectScreen : public FEScreen
{
public:
    FENameSelectScreen(void *owner, int arg2); // 0x0016C530
    virtual ~FENameSelectScreen();             // 0x0016C678
    virtual void VirtSlot2(f32 dt);            // 0x0016BC90
    virtual void VirtSlot3();                  // 0x0016C0D8
    virtual int VirtSlot7();                   // 0x0016C6C8
    virtual int VirtSlot8();                   // 0x0016C6D0

    void *mText164;     // 0x164
    char pad168[0x220]; // 0x168..0x387
    int mField388;      // 0x388
    int mField38C;      // 0x38C
    int mField390;      // 0x390
    f32 mField394;      // 0x394
    f32 mField398;      // 0x398
    int mField39C;      // 0x39C
};

class FEOptionsScreen : public FEScreen
{
public:
    FEOptionsScreen(void *owner, int a2, int a3); // 0x0016D210
    virtual ~FEOptionsScreen();                   // 0x0016D2E0
    virtual void VirtSlot2(f32 dt);               // 0x0016C900
    virtual void VirtSlot3();                     // 0x0016CED0
    virtual int VirtSlot7();                      // 0x0016D380
    virtual int VirtSlot8();                      // 0x0016D378

    void InitMenu16C6D8(int mode);                // 0x0016C6D8

    int mField164;       // 0x164
    void *mText168;      // 0x168
    int mCount16C;       // 0x16C
    int mArr170[20];     // 0x170..0x1BF
    int mArr1C0[20];     // 0x1C0..0x20F
    void *mArr210[20];   // 0x210..0x25F
    int mField260;       // 0x260
    int mField264;       // 0x264
    int mField268;       // 0x268
};

class FEScooterScreen : public FEScreen
{
public:
    FEScooterScreen(void *owner);   // 0x0016D388
    virtual ~FEScooterScreen();     // 0x0016DE98
    virtual void VirtSlot2(f32 dt); // 0x0016DA30
    virtual void VirtSlot3();       // 0x0016D678
    virtual void VirtSlot4();       // 0x0016DEF0
    virtual int VirtSlot7();        // 0x0016DF60
    virtual int VirtSlot8();        // 0x0016DF90

    int mCount164;     // 0x164
    int mArr168[10];   // 0x168..0x18F
    char pad190[0x28]; // 0x190..0x1B7
    void *mCam1B8;     // 0x1B8
    char pad1BC[0x7C]; // 0x1BC..0x237
    int mArr238[10];   // 0x238..0x25F
    int mArr260[10];   // 0x260..0x287
    int mReady288[10]; // 0x288..0x2AF
    int mField2B0;     // 0x2B0
    void *mText2B4;    // 0x2B4
};

#endif
