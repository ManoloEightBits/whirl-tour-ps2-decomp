#ifndef GAME_PARSER_H
#define GAME_PARSER_H

#include "common/types.h"

// A keyword of UnkParser::func_001C1D28's table; the parser sets mToken14 to the matching mId00.
struct UnkKeyword
{
    int mId00;
    const char *mName04;
};

// Script parser used by many loaders (no RTTI; name unknown).
struct UnkParser
{
    char field_0x0000[0x14];
    int mToken14;               // 0x14: id of the last keyword read
    char field_0x0018[0x1014];
    int mEof102C;               // 0x102C: nonzero at the end of the input
    char field_0x1030[0x1000];
    char mPairs2030[0x1000];    // 0x2030: "key value" pairs func_001C3270 searches
    char mValue3030[0x400];     // 0x3030: the text of the last value read (length unknown)

    void func_001C1D28(const UnkKeyword *keywords); // 0x001C1D28: reads the next keyword
    void func_001C2C10();                           // 0x001C2C10: skips an unknown keyword
    // 0x001C2C78: reads a string value. It returns something: with void, PickupDef::func_0011AD28
    // gets $v0 instead of $v1 for a value it loads right after the call.
    int func_001C2C78(const char *key, char *out);
    void func_001C3270(const char *key, f32 *out);  // 0x001C3270: reads a float value

    // Parse mValue3030 with sscanf ("%f %f %f" ... "%d") or as a boolean ("yes", "on", "true", "1").
    void ParseFloat3_1C37B0(f32 *x, f32 *y, f32 *z); // 0x001C37B0
    void ParseFloat2_1C37E8(f32 *x, f32 *y);         // 0x001C37E8
    void ParseFloat1C3818(f32 *x);                   // 0x001C3818
    void ParseInt3_1C3840(int *x, int *y, int *z);   // 0x001C3840
    void ParseInt2_1C3878(int *x, int *y);           // 0x001C3878
    void ParseInt1C38A8(int *x);                     // 0x001C38A8
    void ParseBool1C38F8(int *out);                  // 0x001C38F8
    int IsValueTrue1C3988();                         // 0x001C3988
};

#endif
