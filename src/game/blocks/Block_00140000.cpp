#include "common/types.h"

// Functions of 0x00140000..0x00143FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00142400();         // 0x00142400
void func_001A6368();         // 0x001A6368
void func_001A6458();         // 0x001A6458
int func_001A87E8();          // 0x001A87E8
void func_001A8950();         // 0x001A8950
void func_001A89F0();         // 0x001A89F0
void func_001A8C10(int, int); // 0x001A8C10
void func_001A8D50();         // 0x001A8D50
void MemFree1BD978(void *);   // 0x001BD978

void func_00140A88()
{
}

void func_001416A0(void *arg0)
{
}

void func_001416A8()
{
}

void func_001416B0()
{
}

void func_001416B8()
{
}

void func_00141A18()
{
    func_00142400();
}

void func_001425E0()
{
}

void func_00142D70()
{
    func_001A8C10(1, 5);
}

void func_00142D90()
{
    func_001A8C10(0x18, 0x2F);
}

void func_001430E0(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001436B0()
{
}

void func_001436B8()
{
    func_001A89F0();
}

void func_001436D8()
{
    func_001A8950();
}

int func_001436F8()
{
    return func_001A87E8() == 0;
}

void func_00143718()
{
    func_001A6368();
}

void func_00143738()
{
    func_001A6458();
}

void func_00143758()
{
    func_001A8D50();
}

void func_001AB828(int); // 0x001AB828

// UnkObj140FF8 (0x00140FF8): no RTTI; its layout is the fields these methods use.
struct UnkObj140FF8
{
    char field_0x0[0x10];
    f32 mField10;                  // 0x10

    void Method140FF8(f32 fparg0); // 0x00140FF8
};

void UnkObj140FF8::Method140FF8(f32 fparg0)
{
    mField10 = (f32) (mField10 + fparg0);
}

// UnkObj141140 (0x00141140): no RTTI; its layout is the fields these methods use.
struct UnkObj141140
{
    char field_0x0[0x8];
    int mField8;         // 0x8

    int GetField8();     // 0x00141140
};

int UnkObj141140::GetField8()
{
    return mField8;
}

// UnkObj141A38 (0x00141A38..0x00141AD0): no RTTI; its layout is the fields these methods use.
struct UnkObj141A38
{
    char field_0x0[0x24];
    int mField24;                // 0x24
    int mField28;                // 0x28
    int mField2C;                // 0x2C

    void Method141A38(int arg1); // 0x00141A38
    void SetField28(int v);   // 0x00141AD0
};

void UnkObj141A38::Method141A38(int arg1)
{
    mField24 = arg1;
    mField2C |= 0x20;
}

void UnkObj141A38::SetField28(int v)
{
    mField28 = v;
}

// UnkObj143538 (0x00143538): no RTTI; its layout is the fields these methods use.
struct UnkObj143538
{
    char field_0x0[0x4];
    u16 mField4;         // 0x4

    void Method143538(); // 0x00143538
};

void UnkObj143538::Method143538()
{
    func_001AB828(mField4);
    MemFree1BD978(this);
}

// UnkObj143870 (0x00143870): no RTTI; its layout is the fields these methods use.
struct UnkObj143870
{
    f32 mField0;         // 0x0
    f32 mField4;         // 0x4

    void Method143870(); // 0x00143870
};

void UnkObj143870::Method143870()
{
    mField0 = 0.5f;
    mField4 = 0.01f;
}
