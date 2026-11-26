#include "common/types.h"

// Functions of 0x00164000..0x00167FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00164B40(); // 0x00164B40
void func_00164CC8(); // 0x00164CC8
void func_00165430(); // 0x00165430

int func_00164F88(int arg0)
{
    return arg0 + 0xB0;
}

void func_001650C0()
{
    func_00164CC8();
}

void func_001650E0()
{
    func_00164B40();
}

void func_00165E58()
{
    func_00165430();
}

void func_00167638()
{
}

struct UnkVec166368
{
    f32 x;
    f32 y;
    f32 z;
};

struct UnkArg166368
{
    UnkVec166368 mV00;
    f32 mPad0C;
    UnkVec166368 mV10;
    f32 mPad1C;
    UnkVec166368 mV20;
    f32 mPad2C;
    UnkVec166368 mV30;
};

struct UnkSub166368
{
    char pad00[0x28];
    f32 mField28; // 0x28
};

struct UnkObj166368
{
    u16 mFlags00;       // 0x00
    char pad02[0x02];
    u16 mField04;       // 0x04
    char pad06[0x02];
    u8 mField08;        // 0x08
    char pad09[0x01];
    u8 mField0A;        // 0x0A
    char pad0B[0x0D];
    f32 mField18;       // 0x18
    int mField1C;       // 0x1C
    int mField20;       // 0x20
    char pad24[0x04];
    UnkVec166368 mV28;  // 0x28
    UnkVec166368 mV34;  // 0x34
    UnkVec166368 mV40;  // 0x40
    UnkVec166368 mV4C;  // 0x4C
    UnkSub166368 *mSub58; // 0x58
};

inline void CopyVec166368(UnkVec166368 *dst, UnkVec166368 *src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

void func_00166368(UnkObj166368 *arg0, UnkArg166368 *arg1)
{
    CopyVec166368(&arg0->mV34, &arg1->mV30);
    CopyVec166368(&arg0->mV28, &arg1->mV20);
    CopyVec166368(&arg0->mV40, &arg1->mV00);
    CopyVec166368(&arg0->mV4C, &arg1->mV10);
    arg0->mField08 = 0;
    arg0->mField0A = 0;
    arg0->mField1C = 0;
    arg0->mField20 = 0;
    arg0->mField04 = 0;
    arg0->mField18 = arg0->mSub58->mField28;
    arg0->mFlags00 |= 0x80;
}

struct UnkObj1675D8
{
    char pad00[0x0C];
    void *mField0C; // 0x0C
    void *mField10; // 0x10
    void *mField14; // 0x14
    char pad18[0x0C];
    void *mField24; // 0x24
};

void MemFree1BD978(void *); // 0x001BD978
void __builtin_delete(void *); // 0x00100C08

void func_001675D8(UnkObj1675D8 *arg0, int arg1)
{
    MemFree1BD978(arg0->mField0C);
    MemFree1BD978(arg0->mField10);
    MemFree1BD978(arg0->mField14);
    MemFree1BD978(arg0->mField24);
    if (arg1 & 1)
        __builtin_delete(arg0);
}

struct UnkObj165D28
{
    char pad00[0x18];
    void *mField18; // 0x18
};

void func_00165D28(UnkObj165D28 *arg0, int arg1)
{
    __builtin_delete(arg0->mField18);
    if (arg1 & 1)
        __builtin_delete(arg0);
}
