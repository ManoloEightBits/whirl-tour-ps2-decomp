#ifndef GAME_UNK_EFFECT_H
#define GAME_UNK_EFFECT_H

#include "common/types.h"

// 0x30-byte object spawned at a position (constructor 0x001418E0). Probably a positional sound:
// Pickup passes the CRC32 of its "sound" name as the id. Also used by func_00116B00.
class UnkEffect
{
public:
    UnkEffect(int id, const Vec3f *pos, int, f32, f32, f32); // 0x001418E0
    void func_001419A0(int);                                 // 0x001419A0

    char pad_0x00[0x1C];
    f32 field_0x1C; // func_00116B00 sets it to min(0.1 * (sum of both objects' field_0x150), 1)
    char pad_0x20[0x10];
};

#endif
