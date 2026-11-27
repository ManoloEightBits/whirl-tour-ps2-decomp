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
    void func_00141A18();                                    // 0x00141A18
    void Method141A38(int arg1);                             // 0x00141A38
    void SetField28(int v);                                  // 0x00141AD0

    Vec3f mPos00;   // 0x00
    char pad_0x0C[0x10];
    f32 field_0x1C; // func_00116B00 sets it to min(0.1 * (sum of both objects' field_0x150), 1)
    f32 mField20;   // 0x20
    int mField24;   // 0x24
    int mField28;   // 0x28
    int mField2C;   // 0x2C
};

#endif
