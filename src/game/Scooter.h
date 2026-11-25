#ifndef GAME_SCOOTER_H
#define GAME_SCOOTER_H

#include "common/types.h"

// The scooter state pointed to by Player at +0x2C (health, adrenaline, boosts). No vtable, so no
// RTTI name: "Scooter" is ours. Earlier versions called it ScootCtrl, which is a different,
// small class (the scooter's IVP controller, see Controllers.h).
// Method and field names are ours (hypotheses from usage in Player and Pickup subclasses);
// offsets and instruction shapes are proven by the binary.
class Scooter
{
public:
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
    void func_0017EAA0(f32 amount);          // 0x0017EAA0 (boss attacks pass the attack's +0x10)
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
    void *GetPtr78();                        // 0x0017EC68
    void *GetField1A0();                     // 0x0017EC70
    int IsGrounded();                        // 0x0017EC78
    int HasAdrenaline();                     // 0x0017ECA0
    void func_0017ECC8(void *arg);           // 0x0017ECC8
    f32 ConsumeAdrenaline(f32 amount);       // 0x0017ED28
    void func_0017ED58(int arg);              // 0x0017ED58
    void func_0017ED78(const int *list);  // 0x0017ED78
    void func_0017EDD0();                     // 0x0017EDD0
    void func_0017EDF0(int flag);             // 0x0017EDF0
    void func_0017EE28(int flag);             // 0x0017EE28

    char field_0x000[0x18];
    u32 mFlags18;              // 0x018
    char field_0x01C[0x4C];
    void *mGround68;           // 0x068: non-null while touching the ground (IsGrounded)
    int mField6C;              // 0x06C
    f32 mHealth;               // 0x070 (capped at 100.0f in AddHealth)
    f32 mAdrenaline;           // 0x074
    char mBlock78[0x0C];       // 0x078
    char mBlock84[0x0C];       // 0x084
    f32 mField90;              // 0x090
    f32 mField94;              // 0x094
    f32 mField98;              // 0x098
    char field_0x09C[0x44];
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
    char field_0x1AC[0x20];
    int mField1CC;             // 0x1CC
    int mField1D0;             // 0x1D0
    int mField1D4;             // 0x1D4
    struct IVP_Real_Object_Stub *mPhysObj1D8; // 0x1D8
    char field_0x1DC[0x324];
    int mField500;             // 0x500
    char field_0x504[0x124];
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
