#include "common/types.h"
#include "game/UnkArray.h"

// Functions of 0x00170000..0x00173FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void MemFree1BD978(void *); // 0x001BD978

// UnkObj170958 (0x00170958): no RTTI; its layout is the fields these methods use.
struct UnkObj170958
{
    char field_0x0[0x8];
    void *mField8;       // 0x8
    void *mFieldC;       // 0xC
    void *mField10;      // 0x10

    void Method170958(); // 0x00170958
};

void UnkObj170958::Method170958()
{
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a0_3;

    temp_a0 = mField8;
    if (temp_a0 != NULL)
    {
        MemFree1BD978(temp_a0);
    }
    temp_a0_2 = mFieldC;
    if (temp_a0_2 != NULL)
    {
        MemFree1BD978(temp_a0_2);
    }
    temp_a0_3 = mField10;
    if (temp_a0_3 != NULL)
    {
        MemFree1BD978(temp_a0_3);
    }
    MemFree1BD978(this);
}

// UnkObj170B00 (0x00170B00): no RTTI; its layout is the fields these methods use.
struct UnkObj170B00
{
    char field_0x0[0xC];
    int mFieldC;                   // 0xC
    f32 mField10;                  // 0x10
    char field_0x14[0x4];
    f32 mField18;                  // 0x18

    void Method170B00(f32 fparg0); // 0x00170B00
};

void UnkObj170B00::Method170B00(f32 fparg0)
{
    int tmp;

    tmp = mFieldC & 1;
    switch (tmp)                                /* irregular */
    {
    case 0:
        mField18 = fparg0;
        return;
    case 1:
        mField10 = fparg0;
        return;
    }
}

// UnkObj171050 (0x00171050): no RTTI; its layout is the fields these methods use.
struct UnkObj171050
{
    UnkArray1BB0D0 *mArray0; // 0x0: stride 0x1C
    UnkArray1BB0D0 *mArray4; // 0x4: stride 0x80

    void *Method171050(); // 0x00171050
};

void *UnkObj171050::Method171050()
{
    mArray0 = ArrayCreate1BB0E0(0x1C);
    mArray4 = ArrayCreate1BB0E0(0x80);
    return this;
}
