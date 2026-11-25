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

    void func_001C1D28(const UnkKeyword *keywords); // 0x001C1D28: reads the next keyword
    void func_001C2C10();                           // 0x001C2C10: skips an unknown keyword
    // 0x001C2C78: reads a string value. It returns something: with void, PickupDef::func_0011AD28
    // gets $v0 instead of $v1 for a value it loads right after the call.
    int func_001C2C78(const char *key, char *out);
    void func_001C3270(const char *key, f32 *out);  // 0x001C3270: reads a float value
};

#endif
