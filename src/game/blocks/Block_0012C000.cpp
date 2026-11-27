#include "common/types.h"

// Functions of 0x0012C000..0x0012FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_0012E5F8()
{
}

int func_0012ECB8(int arg0)
{
    return arg0 + 0x10;
}

void func_001BB128(int);    // 0x001BB128
void ArrayDestroy1BB168(int);    // 0x001BB168
void func_001BCAC0(int);    // 0x001BCAC0
void MemFree1BD978(void *); // 0x001BD978

// UnkObj12D0F0 (0x0012D0F0..0x0012D178): no RTTI; its layout is the fields these methods use.
struct UnkObj12D0F0
{
    int mField0;         // 0x0
    int mField4;         // 0x4

    void Method12D0F0(); // 0x0012D0F0
    void Method12D178(); // 0x0012D178
};

void UnkObj12D0F0::Method12D0F0()
{
    func_001BB128(mField0);
    func_001BB128(mField4);
}

void UnkObj12D0F0::Method12D178()
{
    func_001BB128(mField0);
    func_001BB128(mField4);
    ArrayDestroy1BB168(mField0);
    ArrayDestroy1BB168(mField4);
    MemFree1BD978(this);
}

// UnkObj12E408 (0x0012E408..0x0012E428): no RTTI; its layout is the fields these methods use.
struct UnkObj12E408
{
    char field_0x0[0xD0];
    int mFieldD0;         // 0xD0
    char field_0xD4[0x4];
    int mFieldD8;         // 0xD8
    int mFieldDC;         // 0xDC

    int Method12E408();   // 0x0012E408
    int Method12E428();   // 0x0012E428
};

int UnkObj12E408::Method12E408()
{
    if (mFieldD0 & 2)
    {
        return mFieldDC;
    }
    return 0;
}

int UnkObj12E408::Method12E428()
{
    if (mFieldD0 & 1)
    {
        return mFieldD8;
    }
    return 0;
}

// UnkObj12E7D8 (0x0012E7D8): no RTTI; its layout is the fields these methods use.
struct UnkObj12E7D8
{
    char field_0x0[0x14];
    int mField14;         // 0x14

    void Method12E7D8();  // 0x0012E7D8
};

void UnkObj12E7D8::Method12E7D8()
{
    func_001BCAC0(mField14);
}

// UnkObj12F188 (0x0012F188..0x0012F1A0): no RTTI; its layout is the fields these methods use.
struct UnkObj12F188
{
    char field_0x0[0x94];
    int mField94;                // 0x94
    int mField98;                // 0x98

    int GetField98();            // 0x0012F188
    void Method12F190(int arg1); // 0x0012F190
    void Method12F1A0(int arg1); // 0x0012F1A0
};

int UnkObj12F188::GetField98()
{
    return mField98;
}

void UnkObj12F188::Method12F190(int arg1)
{
    mField94 |= arg1;
}

void UnkObj12F188::Method12F1A0(int arg1)
{
    mField94 &= ~arg1;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_001BB250(int, int *); // 0x001BB250
extern int data_0025E19C;

int func_0012ECC0()
{
    return data_0025E19C + 0x10;
}

void func_0012EEB8(int *arg0, int arg1)
{
    int sp0;

    sp0 = arg1;
    func_001BB250(*arg0, &sp0);
}

void *MemAlloc1BD958(int);          // 0x001BD958
void *ArrayCreate1BB0E0(int);       // 0x001BB0E0
void func_0012D1C0(UnkObj12D0F0 *); // 0x0012D1C0

UnkObj12D0F0 *func_0012D120()
{
    UnkObj12D0F0 *p = (UnkObj12D0F0 *)MemAlloc1BD958(8);
    if (p != 0)
    {
        p->mField0 = (int)ArrayCreate1BB0E0(0x10);
        p->mField4 = (int)ArrayCreate1BB0E0(0xC);
        func_0012D1C0(p);
    }
    return p;
}

struct UnkObj12EAA0
{
    void *mField00; // 0x00
    char pad04[0x0C];
    u8 mSub10[0x40]; // 0x10
    int mField50;    // 0x50
    char pad54[0x0C];
};

void *__builtin_new(u32); // 0x00100BE8
void func_001B38D0(void *); // 0x001B38D0

void func_0012EAA0()
{
    if (data_0025E19C == 0)
    {
        UnkObj12EAA0 *p = (UnkObj12EAA0 *)__builtin_new(0x60);
        p->mField00 = ArrayCreate1BB0E0(4);
        func_001B38D0(p->mSub10);
        data_0025E19C = (int)p;
        p->mField50 = 0;
    }
}

struct UnkObj12E280
{
    char pad00[0x40];
    u8 mSub40[0x80]; // 0x40
    u8 *mFieldC0;    // 0xC0
};

f32 func_001AF368(u8 *, u16 *, int, int); // 0x001AF368
void func_001B3928(void *, f32 *, int);   // 0x001B3928

void func_0012E280(UnkObj12E280 *arg0, int arg1, u16 *arg2, int arg3)
{
    f32 sp0;
    func_001AF368(arg0->mFieldC0, arg2, arg1, (int)&sp0);
    func_001B3928(arg0->mSub40, &sp0, arg3);
}

struct UnkObj12FE80
{
    char pad00[0x2C];
    void *mField2C; // 0x2C
};

void __builtin_delete(void *); // 0x00100C08

void func_0012FE80(UnkObj12FE80 *arg0, int arg1)
{
    MemFree1BD978(arg0->mField2C);
    if (arg1 & 1)
        __builtin_delete(arg0);
}

struct UnkObj12D0B8
{
    const char *mStr00;
    u32 mCrc04;
    int mField08;
};

u32 HashStringCRC32(const char *); // 0x001B1CD0

void func_0012D0B8(UnkObj12D0B8 *arg0, const char *arg1)
{
    arg0->mStr00 = arg1;
    arg0->mCrc04 = HashStringCRC32(arg1);
    arg0->mField08 = 0;
}

struct UnkObj1BD870
{
    void *GetField8(); // 0x001BD8C8
};

struct UnkObj12CBA0
{
    char pad00[0x94];
    UnkObj1BD870 *mField94; // 0x94
};

void func_0012CBA0(UnkObj12CBA0 *arg0)
{
    MemFree1BD978(arg0->mField94->GetField8());
    MemFree1BD978(arg0);
}

struct UnkObj1BEAD0
{
    int GetField8(); // 0x001BEAD0
};

struct UnkObj12CE38
{
    char pad00[8];
    UnkObj1BEAD0 *mArr08[1];
};

int func_0012CE38(UnkObj12CE38 *arg0, int arg1)
{
    UnkObj1BEAD0 *obj = arg0->mArr08[arg1];
    int ret = 0;
    if (obj != 0)
        ret = obj->GetField8();
    return ret;
}

// Synthesized from m2c (0x0012F1E0)
struct UnkObj12F1E0
{
    char pad00[0xC4];
    int mArrC4[1]; // 0xC4
    int Method12F1E0(int arg1);
};

int UnkObj12F1E0::Method12F1E0(int arg1)
{
    return this->mArrC4[arg1];
}

// Synthesized from m2c (0x0012F248)
struct UnkObj12F248
{
    char pad00[0x9C];
    int mArr9C[1]; // 0x9C
    int Method12F248(int arg1);
};

int UnkObj12F248::Method12F248(int arg1)
{
    return this->mArr9C[arg1];
}

