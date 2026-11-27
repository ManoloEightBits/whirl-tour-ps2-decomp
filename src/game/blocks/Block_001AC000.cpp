#include "common/types.h"

// Functions of 0x001AC000..0x001AFFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void MemFree1BD978(void *); // 0x001BD978

int func_001ACC08()
{
    return 1;
}

void func_001AF330(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001AFBF8(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001BFB00(int); // 0x001BFB00
void func_0023CCF8(int); // 0x0023CCF8
void func_00244948();    // 0x00244948

// UnkObj1ACD40 (0x001ACD40): no RTTI; its layout is the fields these methods use.
struct UnkObj1ACD40
{
    char field_0x0[0x48];
    int mField48;         // 0x48
    char field_0x4C[0x8];
    int mField54;         // 0x54

    int Method1ACD40();   // 0x001ACD40
};

int UnkObj1ACD40::Method1ACD40()
{
    return mField54 >= mField48;
}

// UnkObj1AD5F8 (0x001AD5F8): no RTTI; its layout is the fields these methods use.
struct UnkObj1AD5F8
{
    char field_0x0[0x4];
    int mField4;         // 0x4
    char field_0x8[0x8];
    int mField10;        // 0x10
    int mField14;        // 0x14

    void Method1AD5F8(); // 0x001AD5F8
};

void UnkObj1AD5F8::Method1AD5F8()
{
    if (mField4 != 0)
    {
        func_00244948();
        func_001BFB00(mField10);
    }
    else
    {
        func_0023CCF8(mField14);
    }
    MemFree1BD978(this);
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_001AF590(f32 *arg0, f32 *arg1)
{
    return (int) (*arg0 - *arg1);
}

void MemFree1BD978(void *); // 0x001BD978
extern "C" void func_001ACDC0(void *); // 0x001ACDC0
extern "C" void func_0023F9C8(int);    // 0x0023F9C8
extern "C" void func_0024BDA0(void *); // 0x0024BDA0
extern "C" void func_0024BF18(void *); // 0x0024BF18

struct UnkObj1AC2F8
{
    char pad00[0x10];
    void *mField10; // 0x10
    int mField14;   // 0x14
    void *mField18; // 0x18
    int mField1C;   // 0x1C
    void *mField20; // 0x20
    void *mField24; // 0x24
    int mField28;   // 0x28
    void *mField2C; // 0x2C
    int mField30;   // 0x30
    int mField34;   // 0x34
    void *mField38; // 0x38
    int mField3C;   // 0x3C
    char pad40[0x08];
    char mField48[0x48]; // 0x48
    char mField90[0x6C]; // 0x90
    UnkObj1AD5F8 *mFieldFC; // 0xFC
};

void func_001AC2F8(UnkObj1AC2F8 *arg0)
{
    func_001ACDC0(arg0->mField90);
    func_0024BF18(arg0->mField48);
    func_0024BDA0(arg0->mField48);
    MemFree1BD978(arg0->mField18);
    MemFree1BD978(arg0->mField10);
    MemFree1BD978(arg0->mField20);
    MemFree1BD978(arg0->mField24);
    MemFree1BD978(arg0->mField2C);
    func_0023F9C8(arg0->mField34);
    MemFree1BD978(arg0->mField38);
    func_0023F9C8(arg0->mField3C);
    if (arg0->mFieldFC != 0)
        arg0->mFieldFC->Method1AD5F8();
    MemFree1BD978(arg0);
}

typedef void (*UnkCurveFn)(int, int, int, f32);
UnkCurveFn func_001C47B8(int);                               // 0x001C47B8
u16 func_001AD8E8(u8 *, u16, int, f32 *, int *, int *);      // 0x001AD8E8

f32 func_001AF368(u8 *arg0, u16 *arg1, int arg2, int arg3)
{
    f32 sp0;
    int sp4;
    int sp8;
    UnkCurveFn fn = func_001C47B8(*arg0);
    *arg1 = func_001AD8E8(arg0, *arg1, arg2, &sp0, &sp4, &sp8);
    fn(sp4, sp8, arg3, sp0);
    return sp0;
}

int func_001AF590(f32 *, f32 *); // 0x001AF590
extern "C" void qsort(void *, unsigned int, unsigned int, int (*)(const void *, const void *));

struct UnkObj1AF5B0
{
    char pad00[0x01];
    u8 mField01;  // 0x01
    char pad02[0x0A];
    u16 mField0C; // 0x0C
};

void func_001AF5B0(void *arg0)
{
    UnkObj1AF5B0 *obj = (UnkObj1AF5B0 *)arg0;
    qsort((char *)arg0 + 0x10, obj->mField0C, obj->mField01 * 4, (int (*)(const void *, const void *))func_001AF590);
}
