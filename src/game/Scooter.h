#ifndef GAME_SCOOTER_H
#define GAME_SCOOTER_H

#include "common/types.h"

// The scooter state pointed to by Player at +0x2C (health, adrenaline, boosts). No vtable, so no
// RTTI name: "Scooter" is ours. Earlier versions called it ScootCtrl, which is a different,
// small class (the scooter's IVP controller, see Controllers.h).
// Method and field names are ours (hypotheses from usage in Player and Pickup subclasses);
// offsets and instruction shapes are proven by the binary.
// Pointed to by Scooter+0x208.
struct UnkScooterState
{
    int mState00;  // 0x00: TakeDamage does nothing in states 4 and 6
    u32 mFlags04;  // 0x04: TakeDamage does nothing with 0x02400000 set, and sets 0x02000000
    char field_0x08[0x1C];
    int mField24;  // 0x24: cleared by TakeDamage
};

struct UnkScooterParams1C0
{
    char field_0x000[0x68];
    f32 mField68;           // 0x068
    char field_0x06C[0x10];
    f32 mField7C;           // 0x07C
    char field_0x080[0x80];
    f32 mStartAcc100;       // 0x100
    char field_0x104[0x14];
    f32 mSpeedMin118;       // 0x118
    char field_0x11C[0x08];
    f32 mStartAcc124;       // 0x124
    char field_0x128[0x14];
    f32 mStartAcc13C;       // 0x13C
    char field_0x140[0x18];
    f32 mAdrenaline158;     // 0x158
    f32 mRampLaunch15C;     // 0x15C
    f32 mWedgeLaunch160;    // 0x160
};

struct UnkScooterSub1CC_24
{
    char field_0x00[0x90];
    f32 mField90;  // 0x90
    f32 mField94;  // 0x94
    f32 mField98;  // 0x98
};

struct UnkScooterSub1CC
{
    char field_0x00[0x24];
    UnkScooterSub1CC_24 *mSub24; // 0x24
};

struct UnkScooterSub500
{
    char field_0x000[4];
    int mField04;  // 0x004
    char field_0x008[0x290];
    int mField298; // 0x298
};

struct UnkScooterArgC
{
    char field_0x00[0x0C];
    int mField0C;  // 0x0C
};

class Scooter
{
public:
    void Method17E298();                     // 0x0017E298
    int GetField18();                        // 0x0017E438
    f32 GetField70();                        // 0x0017E440
    int GetField6C();                        // 0x0017E448
    void func_0017E450();                    // 0x0017E450
    void func_0017E468();                    // 0x0017E468
    int func_0017E478();                     // 0x0017E478
    void func_0017E490();                    // 0x0017E490
    void func_0017E4A0();                    // 0x0017E4A0
    int func_0017E4B8();                     // 0x0017E4B8
    void ClearField9C();                     // 0x0017E4C8
    int func_0017E4D0();                     // 0x0017E4D0
    void SetField544(f32 v);                 // 0x0017E4E0
    void SetField558(f32 v);                 // 0x0017E4E8
    void SetField5BC(f32 v);                 // 0x0017E4F0
    void SetFieldCC(int v);                  // 0x0017E4F8
    void SetFieldC8(f32 v);                  // 0x0017E500
    f32 func_0017E508();                     // 0x0017E508
    f32 func_0017E558();                     // 0x0017E558
    f32 func_0017E588();                     // 0x0017E588
    f32 func_0017E5B8();                     // 0x0017E5B8
    f32 func_0017E5E8();                     // 0x0017E5E8
    f32 func_0017E640();                     // 0x0017E640
    f32 func_0017E698();                     // 0x0017E698
    int GetField504();                       // 0x0017E6F0
    int GetField508();                       // 0x0017E6F8
    int GetField50C();                       // 0x0017E700
    void ClearFields50C_508();               // 0x0017E708
    f32 ScaleRampLaunch(f32 v);              // 0x0017E718
    f32 ScaleWedgeLaunch(f32 v);             // 0x0017E758
    f32 RandomStartAcc124();                 // 0x0017E798
    f32 RandomStartAcc100();                 // 0x0017E810
    f32 RandomStartAcc13C();                 // 0x0017E888
    Vec3f *GetPtr194();                      // 0x0017E900
    void SetVec194(Vec3f *v);                // 0x0017E908
    int GetField500();                       // 0x0017E928
    void SetActorAndClear1D8(void *actor);   // 0x0017E930
    f32 GetStatFactor();                     // 0x0017E958
    int IsBoostInactive();                   // 0x0017EA08
    int IsBoostUnavailable();                // 0x0017EA18
    void SetBoostField62C(f32 val);          // 0x0017EA28
    void SetBoostField630(f32 val);          // 0x0017EA30
    void ApplySpecialAction(int mode);       // 0x0017EA38
    void TakeDamage(f32 amount);             // 0x0017EAA0: mHealth -= amount * 100 (boss attacks pass the attack's +0x10)
    void func_0017EB48();                    // 0x0017EB48
    void AddHealth(f32 percent);             // 0x0017EB90
    void AddSpeedBoost(f32 amount, f32 dur); // 0x0017EBC0
    void AddSpinBoost(f32 amount, f32 dur);  // 0x0017EBD0
    void AddJumpBoost(f32 amount, f32 dur);  // 0x0017EBE0
    void AddBalanceBoost(f32 amount, f32 dur); // 0x0017EBF0
    int GetField1D0();                       // 0x0017EC00
    int GetField1CC();                       // 0x0017EC08
    f32 GetField90();                        // 0x0017EC10
    void *GetPtr84();                        // 0x0017EC18
    void *GetPtr130();                       // 0x0017EC20
    void *GetPtrE0();                        // 0x0017EC28
    f32 GetField98();                        // 0x0017EC30
    void SetField180(f32 val);               // 0x0017EC38
    void EnableField170();                   // 0x0017EC40
    void DisableField170();                  // 0x0017EC50
    void SetVec174(f32 x, f32 y, f32 z);     // 0x0017EC58
    Vec3f *GetPtr78();                       // 0x0017EC68
    void *GetField1A0();                     // 0x0017EC70
    int IsGrounded();                        // 0x0017EC78
    int HasAdrenaline();                     // 0x0017ECA0
    f32 AddAdrenaline(f32 amount);           // 0x0017ECC8: capped at func_001255C8(), returns the excess
    f32 ConsumeAdrenaline(f32 amount);       // 0x0017ED28
    void func_0017ED58(int arg);              // 0x0017ED58
    void func_0017ED78(const int *list);  // 0x0017ED78
    void func_0017EDD0();                     // 0x0017EDD0
    void func_0017EDF0(int flag);             // 0x0017EDF0
    void func_0017EE28(int flag);             // 0x0017EE28
    void Action1850D0(int seq);              // 0x0017F4C8: hands trick sequence seq to mField20C
    void func_0017F500(int a, int b);        // 0x0017F500
    void func_0017F568();                    // 0x0017F568
    void func_0017F690(int arg);             // 0x0017F690
    int func_0017F718();                     // 0x0017F718
    void func_0017F790(UnkScooterArgC *arg); // 0x0017F790
    f32 func_0017F820();                     // 0x0017F820
    void func_0017F898(f32 x, f32 y, f32 z); // 0x0017F898
    int Method17F8F0(f32 v);                 // 0x0017F8F0: 0x4F or 0x50 when v < mField90 and mField20C accepts trick sequence 0x27 or 0x26, else -1

    char field_0x000[0x18];
    u32 mFlags18;              // 0x018
    char field_0x01C[0x4C];
    void *mGround68;           // 0x068: non-null while touching the ground (IsGrounded)
    int mField6C;              // 0x06C
    f32 mHealth;               // 0x070 (capped at 100.0f in AddHealth)
    f32 mAdrenaline;           // 0x074
    Vec3f mPos78;              // 0x078: a position (Player::func_00123488 subtracts it)
    char mBlock84[0x0C];       // 0x084
    f32 mField90;              // 0x090
    f32 mField94;              // 0x094
    f32 mField98;              // 0x098
    f32 mField9C;              // 0x09C
    char field_0x0A0[0x28];
    f32 mFieldC8;              // 0x0C8
    int mFieldCC;              // 0x0CC
    char field_0x0D0[0x10];
    char mBlockE0[0x50];       // 0x0E0
    char mBlock130[0x40];      // 0x130
    int mField170;             // 0x170
    f32 mVec174X;              // 0x174
    f32 mVec174Y;              // 0x178
    f32 mVec174Z;              // 0x17C
    f32 mField180;             // 0x180
    char field_0x184[0x10];
    Vec3f mVec194;             // 0x194
    void *mField1A0;           // 0x1A0
    char field_0x1A4[4];
    void *mField1A8;           // 0x1A8: passed to func_001BC438 with 0.1f, 1.0f
    char field_0x1AC[0x14];
    UnkScooterParams1C0 *mParams1C0; // 0x1C0
    char field_0x1C4[8];
    int mField1CC;             // 0x1CC
    int mField1D0;             // 0x1D0
    int mField1D4;             // 0x1D4
    struct IVP_Real_Object_Stub *mPhysObj1D8; // 0x1D8
    char field_0x1DC[0x2C];
    UnkScooterState *mState208; // 0x208
    void *mField20C;           // 0x20C: Action1850D0 hands it a trick sequence
    int mField210;             // 0x210: GetStatFactor passes it to func_00125968 (3 or 4 gives 1.0)
    char field_0x214[0x68];
    int mField27C;             // 0x27C
    int mField280;             // 0x280
    char field_0x284[0xE8];
    int mField36C;             // 0x36C: set to 1 by TakeDamage
    char field_0x370[0x190];
    int mField500;             // 0x500
    int mField504;             // 0x504
    int mField508;             // 0x508
    int mField50C;             // 0x50C
    f32 mField510;             // 0x510
    int mField514;             // 0x514
    int mField518;             // 0x518
    char field_0x51C[0x10];
    int mField52C;             // 0x52C
    char field_0x530[0x14];
    f32 mField544;             // 0x544
    char field_0x548[0x10];
    f32 mField558;             // 0x558
    char field_0x55C[0x60];
    f32 mField5BC;             // 0x5BC
    char field_0x5C0[0x68];
    int mBoostState;           // 0x628
    f32 mField62C;             // 0x62C
    f32 mField630;             // 0x630
    f32 mField634;             // 0x634
    f32 mField638;             // 0x638
    f32 mSpeedBoostAmount;     // 0x63C
    f32 mSpinBoostAmount;      // 0x640
    f32 mJumpBoostAmount;      // 0x644
    f32 mBalanceBoostAmount;   // 0x648
    f32 mSpeedBoostDuration;   // 0x64C
    f32 mSpinBoostDuration;    // 0x650
    f32 mJumpBoostDuration;    // 0x654
    f32 mBalanceBoostDuration; // 0x658
};

#endif
