#include "common/types.h"

// Functions of 0x00134000..0x00137FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001562E8();    // 0x001562E8
void func_00136FB8();    // 0x00136FB8
void func_001BDCF8(void *, f32); // 0x001BDCF8
void func_001BDE60(int); // 0x001BDE60

void func_00135B58()
{
    func_001562E8();
}

void func_00136C50(int arg0, f32 dt)
{
    func_001BDCF8((void *)(arg0 + 0xC), dt);
}

struct UnkObj136FD8
{
    char pad00[0x70];
    int mField70; // 0x70
};

void func_001BCAC0(int); // 0x001BCAC0

void func_00136FD8(int unused, UnkObj136FD8 *arg1)
{
    int p = arg1->mField70;
    if (p != 0)
        func_001BCAC0(p);
}

void func_00136C70(int arg0)
{
    func_001BDE60(arg0 + 0xC);
}

void func_00136FB8()
{
}

void func_00136FD0()
{
}

void func_001BCAC0(int); // 0x001BCAC0

// UnkObj135A50 (0x00135A50..0x00135B48): no RTTI; its layout is the fields these methods use.
struct UnkObj135A50
{
    char field_0x0[0xC4];
    int mFieldC4;          // 0xC4
    int mFieldC8;          // 0xC8
    int mFieldCC;          // 0xCC
    char field_0xD0[0x44];
    int mField114;         // 0x114

    void Method135A50();   // 0x00135A50
    void Method135A60();   // 0x00135A60
    void Method135AD8();   // 0x00135AD8
    void Method135B48();   // 0x00135B48
};

void UnkObj135A50::Method135A50()
{
    mFieldC4 = 1;
}

void UnkObj135A50::Method135A60()
{
    mFieldC8 = 1;
}

void UnkObj135A50::Method135AD8()
{
    mFieldCC = 1;
}

void UnkObj135A50::Method135B48()
{
    mField114 = 1;
}

// UnkObj136B90 (0x00136B90): no RTTI; its layout is the fields these methods use.
struct UnkObj136B90
{
    f32 mField0;                                           // 0x0
    f32 mField4;                                           // 0x4
    f32 mField8;                                           // 0x8
    f32 mFieldC;                                           // 0xC
    f32 mField10;                                          // 0x10
    f32 mField14;                                          // 0x14

    void Method136B90(f32 fparg0, f32 fparg1, f32 fparg2); // 0x00136B90
};

void UnkObj136B90::Method136B90(f32 fparg0, f32 fparg1, f32 fparg2)
{
    mField10 = 0.0f;
    mField0 = fparg0;
    mField4 = fparg1;
    mField8 = fparg2;
    mField14 = fparg0;
    if (fparg2 != mField10)
    {
        mFieldC = (f32) ((fparg1 - fparg0) / fparg2);
        return;
    }
    mField14 = fparg1;
    mFieldC = (f32) (fparg1 - fparg0);
}

// UnkObj136D78 (0x00136D78): no RTTI; its layout is the fields these methods use.
struct UnkObj136D78
{
    char field_0x0[0x6C];
    int mField6C;         // 0x6C

    void Method136D78();  // 0x00136D78
};

void UnkObj136D78::Method136D78()
{
    func_001BCAC0(mField6C);
}

struct UnkObj136FC0
{
    char pad00[0x08];
    void *mField08; // 0x08
};

void func_00136FC0(UnkObj136FC0 *arg0)
{
    arg0->mField08 = (void *)func_00136FB8;
}

struct UnkSub137818
{
    char pad00[0x28];
    u32 mField28; // 0x28
};

struct UnkObj137818
{
    char pad00[0x1C];
    UnkSub137818 *mField1C; // 0x1C
};

void func_00137818(UnkObj137818 *arg0)
{
    arg0->mField1C->mField28 &= 0xFFFFFFFE;
}

struct UnkObj136E80;
typedef void (*UnkCb136E80)(int, UnkObj136E80 *);

struct UnkSub136E80
{
    char pad00[0x18E0];
    UnkCb136E80 mCb18E0; // 0x18E0
};

struct UnkObj136E80
{
    UnkSub136E80 *mSub00; // 0x00
    char pad04[0x68];
    int mField6C;          // 0x6C
};

void func_00141470();   // 0x00141470
void func_00126138(int); // 0x00126138

void func_00136E80(UnkObj136E80 *arg0)
{
    UnkCb136E80 cb = arg0->mSub00->mCb18E0;
    if (cb != 0)
        cb(arg0->mField6C, arg0);
    func_00141470();
    func_00126138(0);
}

// Synthesized from m2c (0x00136D98)
struct UnkObj136D98
{
    char pad00[0x24];
    u32 mField24; // 0x24
    int mArr28[1]; // 0x28
    void Method136D98(int arg1);
};

void UnkObj136D98::Method136D98(int arg1)
{
    u32 temp_v1;

    temp_v1 = this->mField24;
    if (temp_v1 < 3U)
    {
        this->mArr28[temp_v1] = arg1;
        this->mField24 = (u32) (temp_v1 + 1);
    }
}

void func_0012EAF8();             // 0x0012EAF8
void func_00168D28();             // 0x00168D28
void Release198F38(void *);       // 0x00198F38
void func_00143170(void *, int);  // 0x00143170
void func_0012F470(void *);       // 0x0012F470
struct UnkObj12E7D8 { void Method12E7D8(); }; // 0x0012E7D8
void func_0013C000(void *);       // 0x0013C000
void func_00198210(int);          // 0x00198210
void func_00101E58(void *, int);  // 0x00101E58
void func_00139730(void *, int);  // 0x00139730
void func_00139FB8(void *, int);  // 0x00139FB8
void func_0013FC20(void *, int);  // 0x0013FC20
void func_00187A00(void *, int);  // 0x00187A00

struct UnkObj134530
{
    char pad00[0xC];
    void *mField0C;           // 0x0C
    UnkObj12E7D8 *mField10;   // 0x10
    void *mField14;           // 0x14
    int mField18;             // 0x18
    int mField1C;             // 0x1C
    char pad20[0xC];
    void *mField2C;           // 0x2C
    char pad30[0x34];
    void *mField64;           // 0x64
    char pad68[0x4];
    void *mField6C;           // 0x6C
    char pad70[0x8];
    void *mField78;           // 0x78
    char pad7C[0x40];
    void *mFieldBC;           // 0xBC
    char padC0[0x48];
    void *mField108;          // 0x108
    void *mField10C;          // 0x10C
    void *mField110;          // 0x110
    char pad114[0xC];
    void *mField120;          // 0x120
};

void func_00134530(int unused, UnkObj134530 *arg1)
{
    func_0012EAF8();
    func_00168D28();
    if (arg1->mField6C != 0)
        Release198F38(arg1->mField6C);
    if (arg1->mField2C != 0)
        func_00143170(arg1->mField2C, 4);
    if (arg1->mField14 != 0)
        func_0012F470(arg1->mField14);
    if (arg1->mField10 != 0)
        arg1->mField10->Method12E7D8();
    if (arg1->mField64 != 0)
        func_0013C000(arg1->mField64);
    if (arg1->mField18 != 0)
        func_00198210(arg1->mField18);
    if (arg1->mField1C != 0)
        func_00198210(arg1->mField1C);
    if (arg1->mField0C != 0)
        func_00101E58(arg1->mField0C, 3);
    if (arg1->mField78 != 0)
        func_00139730(arg1->mField78, 3);
    if (arg1->mFieldBC != 0)
        func_00139FB8(arg1->mFieldBC, 3);
    if (arg1->mField120 != 0)
        func_0013FC20(arg1->mField120, 3);
    if (arg1->mField108 != 0)
        func_00187A00(arg1->mField108, 3);
    if (arg1->mField10C != 0)
        func_00187A00(arg1->mField10C, 3);
    if (arg1->mField110 != 0)
        func_00187A00(arg1->mField110, 3);
}

