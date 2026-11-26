#include "common/types.h"
#include "game/FEScreen.h"

// Functions of 0x00184000..0x00187FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

int func_00125630(int);     // 0x00125630
void func_00187750(int);    // 0x00187750
void MemFree1BD978(void *); // 0x001BD978

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
    MemFree1BD978(mField14);
    MemFree1BD978(mField18);
    MemFree1BD978(mField1C);
    MemFree1BD978(mField20);
    MemFree1BD978(this);
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

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

struct EnvObj;
void EnvObjCleanup14FB70(EnvObj *); // 0x0014FB70
void func_00186680(int);            // 0x00186680

void func_00184480(EnvObj *obj)
{
    EnvObjCleanup14FB70(obj);
    MemFree1BD978(obj);
}

void func_00186208(int *arg0)
{
    func_00186680(*arg0);
}

FESlider::~FESlider()
{
}

void PlaySoundCRC141520(u32); // 0x00141520

struct UnkItem187500
{
    char pad00[0x14];
    f32 mField14; // 0x14
    char pad18[0x0C];
    int mField24; // 0x24
};

struct UnkSub187500
{
    f32 mField00; // 0x00
    f32 mField04; // 0x04
    f32 mField08; // 0x08
};

struct UnkObj187500
{
    UnkItem187500 *mItems00; // 0x00
    int mField04;            // 0x04
    int mCount08;            // 0x08
    int mField0C;            // 0x0C
    int mStart10;            // 0x10
    char pad14[0x7C];
    UnkSub187500 *mSub90;    // 0x90
};

void func_00187500(UnkObj187500 *arg0)
{
    for (int i = 0; i < arg0->mCount08; i++)
    {
        UnkItem187500 *item = &arg0->mItems00[(arg0->mStart10 + i) % 20];
        f32 t = item->mField14 + arg0->mSub90->mField08;
        item->mField14 = t;
        if (arg0->mSub90->mField00 < t && item->mField24 == 2)
            item->mField24 = 1;
    }
}

struct UnkObj187F30
{
    int mField00; // 0x00
    int mField04; // 0x04
    int mField08; // 0x08
    u32 mField0C; // 0x0C
};

struct UnkPad187F30
{
    char pad00[0x20];
    int mField20; // 0x20
};

int func_00187F30(UnkObj187F30 *arg0, UnkPad187F30 *arg1)
{
    int btns = arg1->mField20;
    if (btns < 0)
    {
        if (arg0->mField0C != 0)
            PlaySoundCRC141520(arg0->mField0C);
        int cur = arg0->mField00;
        if (cur <= 0)
            cur = arg0->mField04;
        arg0->mField00 = cur - 1;
    }
    else if (btns & 0x20000000)
    {
        if (arg0->mField0C != 0)
            PlaySoundCRC141520(arg0->mField0C);
        int cur = arg0->mField00;
        if (cur < arg0->mField04 - 1)
            arg0->mField00 = cur + 1;
        else
            arg0->mField00 = 0;
    }
    return arg0->mField00;
}

struct UnkObj185458
{
    char pad00[0x08];
    int mField08;   // 0x08
    int mField0C;   // 0x0C
    int mField10;   // 0x10
    int *mArr14;    // 0x14
    f32 *mArr18;    // 0x18
    int *mArr1C;    // 0x1C
    f32 *mArr20;    // 0x20
    int mField24;   // 0x24
};

void func_00185458(UnkObj185458 *arg0, int arg1, f32 arg2)
{
    int mask = arg0->mField24 & arg1;
    arg0->mField24 = mask;
    if (arg1 & mask)
        arg1 &= ~mask;
    int hi = arg1 & 0xF0000000;
    arg0->mArr18[arg0->mField0C] += arg2;
    arg0->mArr20[arg0->mField10] += arg2;
    int idx0 = arg0->mField0C;
    int *arr0 = arg0->mArr14;
    if (arr0[idx0] != hi)
    {
        int next = (idx0 + 1) % arg0->mField08;
        arg0->mField0C = next;
        arr0[next] = hi;
        arg0->mArr18[arg0->mField0C] = 0.0f;
    }
    int idx1 = arg0->mField10;
    int *arr1 = arg0->mArr1C;
    int lo = arg1 & 0x3C0000;
    if (arr1[idx1] != lo)
    {
        int next = (idx1 + 1) % arg0->mField08;
        arg0->mField10 = next;
        arr1[next] = lo;
        arg0->mArr20[arg0->mField10] = 0.0f;
    }
}
