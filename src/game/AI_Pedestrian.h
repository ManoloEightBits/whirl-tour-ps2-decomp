#ifndef GAME_AI_PEDESTRIAN_H
#define GAME_AI_PEDESTRIAN_H

#include "common/types.h"
#include "game/AI_Agent.h"

// Pointed to by AI_Pedestrian+0x17C (floats read by the GetParam* accessors).
struct UnkPedParams
{
    char field_0x00[4];
    f32 mSpeed04;         // 0x04
    char field_0x08[0xC];
    f32 mProbability14;   // 0x14
    f32 mTimeIn18;        // 0x18
    f32 mTimeOut1C;       // 0x1C
    f32 mProbability20;   // 0x20
    f32 mStopRange24;     // 0x24
    f32 mTime28;          // 0x28
    f32 mSpeed2C;         // 0x2C
    f32 mLookAtRange30;   // 0x30
};

// RTTI: AI_Pedestrian : AI_Agent (_vptr at +0x9C). Its __tf is the generated stub in src/rtti/;
// this file has the accessors that follow it (0x001065C8..0x0010679F). Names are offset-based.
class AI_Pedestrian : public AI_Agent
{
public:
    f32 GetField128();                // 0x001065C8
    void SetField128(f32 v);          // 0x001065D0
    void AddField128(f32 v);          // 0x001065D8
    void SubField128(f32 v);          // 0x001065E8
    UnkPedParams *GetParams17C();     // 0x001065F8
    int GetField180();                // 0x00106600
    int GetField160();                // 0x00106608
    int GetField154();                // 0x00106610
    int GetField158();                // 0x00106618
    int GetField164();                // 0x00106620
    int *GetPtr168();                 // 0x00106628
    f32 *GetPtr16C();                 // 0x00106630
    void SetField16C(f32 v);          // 0x00106638
    void AddField16C(f32 v);          // 0x00106640
    f32 GetField170();                // 0x00106650
    void SetField170(f32 v);          // 0x00106658
    int GetField13C();                // 0x00106660
    int GetField144();                // 0x00106668
    int GetField140();                // 0x00106670
    int GetField148();                // 0x00106678
    f32 GetField14C();                // 0x00106680
    Vec4f *GetPtr100();               // 0x00106688
    Vec4f *GetPtrF0();                // 0x00106690
    Vec4f *GetPtrD0();                // 0x00106698
    Vec4f *GetPtrE0();                // 0x001066A0
    Vec4f *GetPtrD0b();               // 0x001066A8
    Vec3f *GetPtr110();               // 0x001066B0
    Vec3f *GetPtr11C();               // 0x001066B8
    f32 GetField138();                // 0x001066C0
    void SetField138Ratio(f32 v);     // 0x001066C8
    void ResetField138();             // 0x001066E8
    f32 GetSpeed04();                 // 0x001066F8
    f32 GetField130();                // 0x00106708
    void SetField130(f32 v);          // 0x00106710
    f32 GetProbability14();           // 0x00106718
    f32 GetTimeIn18();                // 0x00106728
    f32 GetTimeOut1C();               // 0x00106738
    f32 GetProbability20();           // 0x00106748
    f32 GetStopRange24();             // 0x00106758
    f32 GetTime28();                  // 0x00106768
    f32 GetSpeed2C();                 // 0x00106778
    f32 GetLookAtRange30();           // 0x00106788
    int GetField184();                // 0x00106798
    char field_0xA0[0x30];
    Vec4f mFieldD0;            // 0xD0
    Vec4f mFieldE0;            // 0xE0
    Vec4f mFieldF0;            // 0xF0
    Vec4f mField100;           // 0x100
    Vec3f mField110;           // 0x110
    Vec3f mField11C;           // 0x11C
    f32 mField128;             // 0x128
    char field_0x12C[4];
    f32 mField130;             // 0x130
    f32 mField134;             // 0x134
    f32 mField138;             // 0x138: min(mField134 / v, 1) or 1
    int mField13C;             // 0x13C
    int mField140;             // 0x140
    int mField144;             // 0x144
    int mField148;             // 0x148
    f32 mField14C;             // 0x14C
    char field_0x150[4];
    int mField154;             // 0x154
    int mField158;             // 0x158
    char field_0x15C[4];
    int mField160;             // 0x160
    int mField164;             // 0x164
    int mField168;             // 0x168
    f32 mField16C;             // 0x16C
    f32 mField170;             // 0x170
    char field_0x174[8];
    UnkPedParams *mParams17C;  // 0x17C
    int mField180;             // 0x180
    int mField184;             // 0x184
};

#endif
