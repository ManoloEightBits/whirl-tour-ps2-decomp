#include "common/types.h"

// Functions of 0x00144000..0x00147FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8(); // 0x001974D8
void func_00197510(); // 0x00197510
void func_0019A6F0(void *); // 0x0019A6F0

void func_00144F18()
{
}

void func_00145010()
{
}

void func_00145018()
{
}

void func_001456E8()
{
    func_001974D8();
}

void func_00145B20()
{
    func_001974D8();
}

void func_00145B40()
{
    func_00197510();
}

void func_00145B60(void *arg0)
{
    func_0019A6F0(arg0);
}

void func_001461C0()
{
    func_001974D8();
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_00197AB8(int); // 0x00197AB8
void func_00145B20();    // 0x00145B20

struct UnkPad145930
{
    char pad00[0x1C];
    int mField1C; // 0x1C
    int mField20; // 0x20
};
extern UnkPad145930 *gFEPad2659B0;

struct UnkObj145930
{
    char pad00[0x94];
    int mField94; // 0x94
    char pad98[0x10];
    int mFieldA8; // 0xA8
};

void func_00144F20(int arg0, int arg1)
{
    func_00197AB8(arg1 + 4);
}

void func_00145930(UnkObj145930 *arg0)
{
    switch (arg0->mFieldA8)
    {
    case 0x100:
        arg0->mFieldA8 = 0x200;
        return;
    case 0x200:
        if (gFEPad2659B0->mField20 & 0x10000000)
            arg0->mField94++;
        if (gFEPad2659B0->mField20 & 0x40000000)
            arg0->mField94--;
        if (gFEPad2659B0->mField1C & 0x80000)
            arg0->mFieldA8 = 0xF000;
        break;
    case 0xF000:
        ((void (*)(void *, void *))func_00145B20)(arg0, arg0);
        break;
    }
}

struct UnkObj145618
{
    char pad00[0x9C];
    void *mField9C; // 0x9C
};

void CleanupDialog1309E0(void *); // 0x001309E0
void MemFree1BD978(void *);       // 0x001BD978

void func_00145618(UnkObj145618 *arg0)
{
    CleanupDialog1309E0(arg0->mField9C);
    MemFree1BD978(arg0);
}

void Release198F38(void *); // 0x00198F38

struct UnkObj145A00
{
    char pad00[0xA4];
    void *mFieldA4; // 0xA4
};

void func_00145A00(UnkObj145A00 *arg0)
{
    Release198F38(arg0->mFieldA4);
    MemFree1BD978(arg0);
}

void func_00191E40(void *);  // 0x00191E40
void func_0011A820(void *);  // 0x0011A820
void func_00126138(int);     // 0x00126138

struct UnkObj146148
{
    char pad00[0x94];
    void *mField94;     // 0x94
    char pad98[0x20];
    void *mArrB8[7];    // 0xB8
    void *mFieldD4;     // 0xD4
};

void func_00146148(UnkObj146148 *arg0)
{
    func_00191E40(arg0->mField94);
    for (u32 i = 0; i < 7; i++)
    {
        if (arg0->mArrB8[i] != 0)
            func_0011A820(arg0->mArrB8[i]);
    }
    CleanupDialog1309E0(arg0->mFieldD4);
    MemFree1BD978(arg0);
    func_00126138(0);
}
