#ifndef GAME_UNKARRAY_H
#define GAME_UNKARRAY_H

#include "common/types.h"

// A dynamic array (no RTTI; 0x10 bytes, made by ArrayCreate1BB0E0(stride)). ArrayGetElement1BB098(array, i)
// returns mData0C + i * mStride00 when 0 <= i < mCount08, else null; Clear empties it and Destroy frees
// the data and the array. mField4 is zeroed with the data (probably the capacity).
struct UnkArray1BB0D0
{
    int mStride00;  // 0x0
    int mField4;    // 0x4
    int mCount08;   // 0x8
    void *mData0C;  // 0xC

    int GetCount(); // 0x001BB0D0
    void Clear();   // 0x001BB120
    void Destroy(); // 0x001BB168
};

UnkArray1BB0D0 *ArrayCreate1BB0E0(int stride); // 0x001BB0E0

#endif
