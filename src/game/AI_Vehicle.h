#ifndef GAME_AI_VEHICLE_H
#define GAME_AI_VEHICLE_H

#include "common/types.h"
#include "game/AI_Agent.h"

// Pointed to by AI_Vehicle+0x11C (floats read by GetParam1C/GetParam6C).
struct UnkNode;

// Passed to AI_Vehicle::func_0010E558, which replaces its +0x58 with func_0012CCB0 of it.
struct UnkObj58
{
    char field_0x00[0x58];
    void *mField58; // 0x58
};

struct UnkVehicleParams
{
    char field_0x00[0x1C];
    f32 mField1C;  // 0x1C
    char field_0x20[0x4C];
    f32 mField6C;  // 0x6C
};

// RTTI: AI_Vehicle : AI_Agent (_vptr at +0x9C). Its __tf is still the generated stub in src/rtti/;
// this file has the non-virtual accessors after it (0x0010E298..0x0010E37F). Names are offset-based.
// Its vtable slots 5, 6 and 7 return &mMatrixA0.row[3], &mMatrixA0.row[2] and &mMatrixA0.
class AI_Vehicle : public AI_Agent
{
public:
    f32 GetFieldEC();                 // 0x0010E298
    void SetFieldEC(f32 v);           // 0x0010E2A0
    void AddFieldEC(f32 v);           // 0x0010E2A8
    void SubFieldEC(f32 v);           // 0x0010E2B8
    UnkVehicleParams *GetParams11C(); // 0x0010E2C8
    int GetFieldF0();                 // 0x0010E2D0
    int GetFieldF4();                 // 0x0010E2D8
    int GetField104();                // 0x0010E2E0
    int *GetPtr108();                 // 0x0010E2E8
    f32 *GetPtr10C();                 // 0x0010E2F0
    void SetField10C(f32 v);          // 0x0010E2F8
    void AddField10C(f32 v);          // 0x0010E300
    Vec3f *GetPtrE0();                // 0x0010E320
    Vec4f *GetRow1();                 // 0x0010E330
    Vec4f *GetRow0();                 // 0x0010E338
    f32 GetParam1C();                 // 0x0010E340
    f32 GetFieldF8();                 // 0x0010E350
    void SetFieldF8(f32 v);           // 0x0010E358
    f32 GetFieldFC();                 // 0x0010E360
    f32 GetField100();                // 0x0010E368
    f32 GetParam6C();                 // 0x0010E370
    void func_0010D1A0();             // 0x0010D1A0
    void Action10E468();              // 0x0010E448
    void func_0010E468();             // 0x0010E468: passes mNode138 to func_00193100
    void Action10D1A0();              // 0x0010E490
    f32 func_0010E4B0(f32 v);         // 0x0010E4B0: mFieldF8 += v, capped at mParams11C->mField1C
    f32 func_0010E508(f32 v);         // 0x0010E508: mFieldF8 -= v, floored at 0
    void func_0010E558(UnkObj58 *obj); // 0x0010E558
    void *func_0012CCB0(void *p);     // 0x0012CCB0 (called with this unchanged; may belong to a base)

    Mat4x4f mMatrixA0;             // 0xA0
    Vec3f mFieldE0;                // 0xE0
    f32 mFieldEC;                  // 0xEC
    int mFieldF0;                  // 0xF0
    int mFieldF4;                  // 0xF4
    f32 mFieldF8;                  // 0xF8
    f32 mFieldFC;                  // 0xFC
    f32 mField100;                 // 0x100
    int mField104;                 // 0x104
    int mField108;                 // 0x108
    f32 mField10C;                 // 0x10C
    char field_0x110[0xC];
    UnkVehicleParams *mParams11C;  // 0x11C
    char field_0x120[0x18];
    UnkNode *mNode138;             // 0x138
};

#endif
