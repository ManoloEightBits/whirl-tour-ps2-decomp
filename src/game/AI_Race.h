#ifndef GAME_AI_RACE_H
#define GAME_AI_RACE_H

#include "common/types.h"
#include "game/AI_Agent.h"
#include "game/Player.h"

// RTTI: AI_Race : AI_Agent (_vptr at +0x9C). Its __tf is still the generated stub in src/rtti/; this
// file has the non-virtual accessors after it (0x0010B970..0x0010BB87). Names are offset-based.
class AI_Race : public AI_Agent
{
public:
    int GetFieldA0();                 // 0x0010B970
    void SetFieldA0(int v);           // 0x0010B978
    int GetFieldD0();                 // 0x0010B980
    int GetFieldB0();                 // 0x0010B988
    f32 GetFieldA4();                 // 0x0010B990
    void SetFieldA4(f32 v);           // 0x0010B998
    f32 GetFieldA8();                 // 0x0010B9A0
    void AddFieldA8(f32 v);           // 0x0010B9A8
    void SetFieldA8(f32 v);           // 0x0010B9B8
    int GetFieldC4();                 // 0x0010B9C0
    u8 GetStateC8();                  // 0x0010B9C8
    void NextStateC8();               // 0x0010B9D0
    void SetStateC8(u8 s);            // 0x0010B9E8
    u8 GetStateCA();                  // 0x0010B9F8
    void SetStateCA(u8 s);            // 0x0010BA00
    int GetFieldCC();                 // 0x0010BA10
    void SetFieldCC(int v);           // 0x0010BA18
    Vec4f *GetPlayerRow1();           // 0x0010BA68
    Vec4f *GetPlayerRow0();           // 0x0010BA88
    Player *GetPlayer110();           // 0x0010BAA8
    f32 GetField13C();                // 0x0010BAB0
    f32 GetField134();                // 0x0010BAB8
    f32 GetField138();                // 0x0010BAC0
    Vec3f *GetPtr11C();               // 0x0010BAC8
    f32 *GetPtrE0();                  // 0x0010BAD0
    void SetFieldE0(int i, f32 v);    // 0x0010BAD8
    int GetFieldDC();                 // 0x0010BAE8
    int GetFieldF4();                 // 0x0010BAF0
    int GetField148();                // 0x0010BAF8
    void *GetPtrF8();                 // 0x0010BB00
    f32 GetFieldAC();                 // 0x0010BB08
    void SetFieldAC(f32 v);           // 0x0010BB10
    void AddFieldAC(f32 v);           // 0x0010BB18
    f32 GetFieldF0();                 // 0x0010BB28
    void SetFieldF0(f32 v);           // 0x0010BB30
    void AddFieldF0(f32 v);           // 0x0010BB38
    f32 GetFieldB4();                 // 0x0010BB48
    void SetFieldB4(f32 v);           // 0x0010BB50
    f32 GetFieldB8();                 // 0x0010BB58
    void SetFieldB8(f32 v);           // 0x0010BB60
    f32 GetFieldD8();                 // 0x0010BB68
    void SetFieldD8(f32 v);           // 0x0010BB70
    void SubFieldD8(f32 v);           // 0x0010BB78
    int mFieldA0;              // 0xA0
    f32 mFieldA4;              // 0xA4
    f32 mFieldA8;              // 0xA8
    f32 mFieldAC;              // 0xAC
    int mFieldB0;              // 0xB0
    f32 mFieldB4;              // 0xB4
    f32 mFieldB8;              // 0xB8
    char field_0xBC[8];
    int mFieldC4;              // 0xC4
    u8 mStateC8;               // 0xC8
    u8 mPrevStateC9;           // 0xC9: mStateC8 before its last change
    u8 mStateCA;               // 0xCA
    u8 mPrevStateCB;           // 0xCB: mStateCA before its last change
    int mFieldCC;              // 0xCC
    int mFieldD0;              // 0xD0
    char field_0xD4[4];
    f32 mFieldD8;              // 0xD8
    int mFieldDC;              // 0xDC
    f32 mFieldE0[4];           // 0xE0
    f32 mFieldF0;              // 0xF0
    int mFieldF4;              // 0xF4
    char mBlockF8[0x18];       // 0xF8
    Player *mPlayer110;        // 0x110: its matrix rows are returned by GetPlayerRow*
    char field_0x114[8];
    Vec3f mField11C;           // 0x11C
    Vec3f mPos128;             // 0x128: returned by vtable slot 5
    f32 mField134;             // 0x134
    f32 mField138;             // 0x138
    f32 mField13C;             // 0x13C
    char field_0x140[8];
    int mField148;             // 0x148
};

#endif
