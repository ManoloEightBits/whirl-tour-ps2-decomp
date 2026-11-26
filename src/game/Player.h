#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "common/types.h"
#include "game/Scooter.h"

struct IVP_Real_Object_Stub;
struct DD_ActorInfo;

// Passed to Player::func_001237E8. Its +0x18 is compared with Player+0xB8 to pick one of two position
// pairs; "checkpoint" is a guess.
struct UnkCheckpoint
{
    char field_0x00[0x18];
    int mOrder18;  // 0x18
    Vec3f mVec1C;  // 0x1C
    Vec3f mVec28;  // 0x28
    Vec3f mVec34;  // 0x34
    Vec3f mVec40;  // 0x40
};

// Whirl Tour: the object a pickup is handed when collected. The class name is ours (hypothesis);
// offsets and method shapes are proven by 0x00123438..0x001238B8, the player_* collision callbacks
// that follow them (0x001238C0..0x00123AE8) and the Pickup subclasses.
class Player
{
public:
    Mat4x4f *GetScooterPtr130();                 // 0x00122D08
    void SetScooterField180(f32 val);            // 0x00122D28
    void EnableScooterField170();                // 0x00122D48
    void DisableScooterField170();               // 0x00122D68
    void SetScooterVec174(f32 x, f32 y, f32 z);  // 0x00122D88
    void *GetScooterPtr84();                     // 0x00122DA8
    Vec3f *GetScooterPtr78();                    // 0x00122DC8
    void *GetScooterField1A0();                  // 0x00122DE8
    DD_ActorInfo *GetFieldA0();                  // 0x00122E08
    int TestAmbientStateD2(u8 mask);             // 0x00122E10
    void SetAmbientStateD2(u8 mask);             // 0x00122E20
    void ClearAmbientStateD2(u8 mask);           // 0x00122E30
    f32 GetScooterField70();                     // 0x00122E48
    int GetScooterField6C();                     // 0x00122E68
    f32 Action17F728();                          // 0x00122E88
    void Action17E468();                         // 0x00122EA8
    void Action17E450();                         // 0x00122EC8
    int Action17E478();                          // 0x00122EE8
    int IsScooterState4();                       // 0x00122F08
    void Action17E4A0();                         // 0x00122F30
    void Action17E490();                         // 0x00122F50
    void Action17E2A0(f32 val);                  // 0x00122F70
    void Action172060();                         // 0x00122F90
    void Action17ED58_100FA();                   // 0x00122FB0
    int Action17E4B8();                          // 0x00122FD8
    void ClearScooterField9C();                  // 0x00122FF8
    f32 GetScooterField98();                     // 0x00123018
    int Action17E4D0();                          // 0x00123038
    void SetScooterField544(f32 val);            // 0x00123058
    void SetScooterField558(f32 val);            // 0x00123078
    void SetScooterField5BC(f32 val);            // 0x00123098
    void SetScooterFieldCC(int val);             // 0x001230B8
    int GetFieldB8();                            // 0x001230D8
    u8 GetFieldD3();                             // 0x001230E0
    void Action17EDF0(int flag);                 // 0x001230E8
    void Action17EE28(int flag);                 // 0x00123108
    void SetScooterFieldC8(f32 val);             // 0x00123128
    int Action17F718();                          // 0x00123148
    int GetScooterField504();                    // 0x00123168
    int GetScooterField508();                    // 0x00123188
    int GetScooterField50C();                    // 0x001231A8
    void ClearScooterFields50C_508();            // 0x001231C8
    void SetFieldD4(int v);                      // 0x001231E8
    int GetFieldD4();                            // 0x001231F0
    int GetField30();                            // 0x001231F8
    int GetField34();                            // 0x00123200
    int func_00123208();                         // 0x00123208
    void *GetField28();                          // 0x00123230
    void Action17F288(void *a, void *b);         // 0x00123238
    void Destroy123258();                        // 0x00123258
    void Action17F328();                         // 0x00123438
    void Action17F500();                         // 0x00123458
    void *GetPtr40();                            // 0x00123478
    void *GetPtr58();                            // 0x00123480
    int func_00123488(int id, f32 value);        // 0x00123488
    void AddKey();                               // 0x00123548
    int GetKeys();                               // 0x00123558
    void AddSpeedBoost(f32 amount, f32 dur);     // 0x00123560
    void AddSpinBoost(f32 amount, f32 dur);      // 0x00123580
    void AddJumpBoost(f32 amount, f32 dur);      // 0x001235A0
    void AddBalanceBoost(f32 amount, f32 dur);   // 0x001235C0
    void AddHealth(f32 percent);                 // 0x001235E0
    void AddScooter(int scooterId);              // 0x00123600
    void AddBGM(int bgmId);                      // 0x00123620
    int GetNumBGMs();                            // 0x00123640
    int GetBGM(int index);                       // 0x00123648
    f32 GetStatFactor();                         // 0x00123658
    int IsBoostInactive();                       // 0x00123678
    int IsBoostUnavailable();                    // 0x00123698
    void SetBoostField62C(f32 val);              // 0x001236B8
    void SetBoostField630(f32 val);              // 0x001236D8
    void ApplySpecialAction(int mode);           // 0x001236F8
    void Action1722B0(Vec3f *pos, f32 amount);   // 0x00123718
    void Action1723F0();                         // 0x00123738
    f32 GetMaxConstant1000();                    // 0x00123758
    int HasAdrenaline();                         // 0x00123768
    f32 ConsumeAdrenaline(f32 amount);           // 0x00123788
    f32 AddAdrenaline(f32 amount);               // 0x001237A8
    void Action174198(void *arg);                // 0x001237C8
    void func_001237E8(UnkCheckpoint *cp);       // 0x001237E8
    void EnableFieldD3();                        // 0x00123890
    int GetScooterField500();                    // 0x001238A0

    char field_0x00[0x24];
    int mField24;           // 0x24: cleared by func_00123488
    void *mField28;         // 0x28
    Scooter *mScooter;      // 0x2C
    int mField30;           // 0x30
    int mField34;           // 0x34
    Player *mOtherPlayer38;              // 0x38: set by player_enter_player, cleared on leaving
    IVP_Real_Object_Stub *mVehicle3C;    // 0x3C: set by player_enter_vehicle, cleared on leaving
    char mBlock40[0x18];    // 0x40
    char mBlock58[0x48];    // 0x58
    DD_ActorInfo *mAmbientAreaA0;        // 0xA0: actor of the ambient area the player is in
    int mKeys;              // 0xA4
    int mNumBGMs;           // 0xA8
    int mBGMs[3];           // 0xAC (0xB8 onwards is read by 0x001237E8 as separate fields)
    int mFieldB8;           // 0xB8
    int mFieldBC;           // 0xBC
    Vec3f mVecC0;           // 0xC0..0xCB
    char field_0xCC[6];     // 0xCC..0xD1
    u8 mAmbientStateD2;     // 0xD2: 9 on entering an ambient area, 10 on leaving; 0x10 = entered again
    u8 mFieldD3;            // 0xD3
    int mFieldD4;           // 0xD4
    char field_0xD8[4];     // 0xD8
    void *mFieldDC;         // 0xDC
    void *mFieldE0;         // 0xE0
};

Vec3f *func_00122DC8(Player *player);   // 0x00122DC8: the player's position
Mat4x4f *func_00122D08(Player *player); // 0x00122D08: the player's matrix (row 2 is used)
void func_00122EA8(Player *player);     // 0x00122EA8
void func_00122EC8(Player *player);     // 0x00122EC8

#endif
