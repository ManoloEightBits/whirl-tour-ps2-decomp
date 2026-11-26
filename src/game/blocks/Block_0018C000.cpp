#include "common/types.h"

// Functions of 0x0018C000..0x0018FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_0018CC70();       // 0x0018CC70
void func_0018D600();       // 0x0018D600
void func_0018E678();       // 0x0018E678
void func_0018EFD8();       // 0x0018EFD8
void MemFree1BD978(void *); // 0x001BD978

void func_0018D1E8()
{
    func_0018CC70();
}

void func_0018D990()
{
    func_0018D600();
}

void func_0018E658()
{
    func_0018E678();
}

void func_0018F980()
{
    func_0018EFD8();
}

void func_0018FA18(void *arg0)
{
    MemFree1BD978(arg0);
}

// UnkObj18C018 (0x0018C018): no RTTI; its layout is the fields these methods use.
struct UnkObj18C018
{
    char field_0x0[0x3C];
    u16 mField3C;         // 0x3C

    int Method18C018();   // 0x0018C018
};

int UnkObj18C018::Method18C018()
{
    return mField3C & 1;
}

// UnkObj18D1D8 (0x0018D1D8): no RTTI; its layout is the fields these methods use.
struct UnkObj18D1D8
{
    char field_0x0[0x18];
    int mField18;         // 0x18

    void Method18D1D8();  // 0x0018D1D8
};

void UnkObj18D1D8::Method18D1D8()
{
    mField18 |= 0x100;
}

extern "C" int rand(); // 0x00230700

struct UnkSub18E758
{
    char field_0x0;
    u8 mField01; // 0x01
};

struct UnkObj18E758
{
    char field_0x0[0x18];
    int mField18;             // 0x18
    char field_0x1C[0x10];
    UnkSub18E758 *mField2C;   // 0x2C
    char field_0x30[0x28];
    s8 mField58;              // 0x58

    void Method18E758();      // 0x0018E758
};

void UnkObj18E758::Method18E758()
{
    mField18 = (mField18 | 0x30) & ~1;
    mField58 = rand() % mField2C->mField01;
}

void func_0018D270()
{
}
