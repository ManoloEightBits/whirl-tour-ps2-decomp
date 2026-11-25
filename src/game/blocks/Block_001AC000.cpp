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
