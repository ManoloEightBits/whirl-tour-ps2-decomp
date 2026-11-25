#include "common/types.h"

// Functions of 0x00184000..0x00187FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

int func_00125630(int);     // 0x00125630
void func_00187750(int);    // 0x00187750
void func_001BD978(void *); // 0x001BD978

// UnkObj185760 (0x00185760): no RTTI; its layout is the fields these methods use.
struct UnkObj185760
{
    char field_0x0[0x14];
    void *mField14;       // 0x14
    void *mField18;       // 0x18
    void *mField1C;       // 0x1C
    void *mField20;       // 0x20

    void Method185760();  // 0x00185760
};

void UnkObj185760::Method185760()
{
    func_001BD978(mField14);
    func_001BD978(mField18);
    func_001BD978(mField1C);
    func_001BD978(mField20);
    func_001BD978(this);
}

// UnkObj186040 (0x00186040): no RTTI; its layout is the fields these methods use.
struct UnkObj186040
{
    int mField0;           // 0x0
    char field_0x4[0x298];
    int mField29C;         // 0x29C

    void Method186040();   // 0x00186040
};

void UnkObj186040::Method186040()
{
    mField29C = (int) (mField29C + func_00125630(1));
    func_00187750(mField0);
}

// UnkObj187700 (0x00187700..0x00187768): no RTTI; its layout is the fields these methods use.
struct UnkObj187700
{
    char field_0x0[0x34];
    int mField34;                // 0x34
    f32 mField38;                // 0x38
    int mField3C;                // 0x3C
    f32 mField40;                // 0x40
    int mField44;                // 0x44
    f32 mField48;                // 0x48
    int mField4C;                // 0x4C
    int mField50;                // 0x50
    f32 mField54;                // 0x54

    void Method187700(int arg1); // 0x00187700
    void Method187728(int arg1); // 0x00187728
    void Method187750();         // 0x00187750
    void Method187768(int arg1); // 0x00187768
};

void UnkObj187700::Method187700(int arg1)
{
    if (arg1 != mField34)
    {
        mField34 = arg1;
        mField38 = 2.0f;
    }
}

void UnkObj187700::Method187728(int arg1)
{
    if (arg1 != mField3C)
    {
        mField3C = arg1;
        mField40 = 2.0f;
    }
}

void UnkObj187700::Method187750()
{
    mField44 = 1;
    mField48 = 2.0f;
}

void UnkObj187700::Method187768(int arg1)
{
    if (arg1 != 0)
    {
        mField50 = 1;
    }
    else
    {
        mField4C = 1;
    }
    mField54 = 2.0f;
}

// UnkObj1879D0 (0x001879D0..0x00187AA0): no RTTI; its layout is the fields these methods use.
struct UnkObj1879D0
{
    int mField0;                                                                  // 0x0
    int mField4;                                                                  // 0x4
    int mField8;                                                                  // 0x8
    int mFieldC;                                                                  // 0xC
    f32 mField10;                                                                 // 0x10
    f32 mField14;                                                                 // 0x14
    f32 mField18;                                                                 // 0x18
    f32 mField1C;                                                                 // 0x1C
    int mField20;                                                                 // 0x20

    void *Method1879D0(int arg1, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3); // 0x001879D0
    void Method187AA0(int arg1);                                                  // 0x00187AA0
};

void *UnkObj1879D0::Method1879D0(int arg1, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3)
{
    mField4 = arg1;
    mField10 = fparg0;
    mField14 = fparg1;
    mField18 = fparg2;
    mField1C = fparg3;
    mField0 = 0;
    mField8 = 0;
    mFieldC = 0;
    mField20 = 0;
    return this;
}

void UnkObj1879D0::Method187AA0(int arg1)
{
    if (mField0 == 0)
    {
        mField0 = 1;
    }
    mField8 = arg1;
}

// UnkObj187FD0 (0x00187FD0): no RTTI; its layout is the fields these methods use.
struct UnkObj187FD0
{
    int mField0;        // 0x0
    int mField4;        // 0x4

    int Method187FD0(); // 0x00187FD0
};

int UnkObj187FD0::Method187FD0()
{
    int tmp;

    tmp = mField0;
    if (tmp < (mField4 - 1))
    {
        mField0 = (int) (tmp + 1);
    }
    else
    {
        mField0 = 0;
    }
    return mField0;
}
