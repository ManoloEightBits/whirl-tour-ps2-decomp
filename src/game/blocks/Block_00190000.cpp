#include "common/types.h"
#include "common/libc.h"

// Functions of 0x00190000..0x00193FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

int func_00190D88();        // 0x00190D88
void MemFree1BD978(void *); // 0x001BD978

int func_00190BB8(int arg0)
{
    return arg0 + 0x1900;
}

int func_00190D90()
{
    return func_00190D88() == 0;
}

int func_00190DB8(int arg0)
{
    return arg0 + 0xC;
}

int func_00190DC0(int arg0)
{
    return arg0 + 4;
}

void func_00191768(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_00191E40(void *arg0)
{
    MemFree1BD978(arg0);
}

// UnkObj190B68 (0x00190B68..0x00190BA0): no RTTI; its layout is the fields these methods use.
struct UnkObj190B68
{
    char field_0x0[0x8];
    int mField8;          // 0x8
    int mFieldC;          // 0xC
    char field_0x10[0x4];
    int mField14;         // 0x14

    int GetField8();      // 0x00190B68
    int Method190B70();   // 0x00190B70
    int GetField14();     // 0x00190BA0
};

int UnkObj190B68::GetField8()
{
    return mField8;
}

int UnkObj190B68::Method190B70()
{
    return mFieldC != 0;
}

int UnkObj190B68::GetField14()
{
    return mField14;
}

// UnkObj190D70 (0x00190D70..0x00190D88): no RTTI; its layout is the fields these methods use.
struct UnkObj190D70
{
    char field_0x0[0x30];
    int mField30;         // 0x30
    char field_0x34[0xC];
    int mField40;         // 0x40
    int mField44;         // 0x44
    int mField48;         // 0x48

    int GetField48();     // 0x00190D70
    int GetField44();     // 0x00190D78
    int GetField40();     // 0x00190D80
    int GetField30();     // 0x00190D88
};

int UnkObj190D70::GetField48()
{
    return mField48;
}

int UnkObj190D70::GetField44()
{
    return mField44;
}

int UnkObj190D70::GetField40()
{
    return mField40;
}

int UnkObj190D70::GetField30()
{
    return mField30;
}

// UnkObj190DB0 (0x00190DB0): no RTTI; its layout is the fields these methods use.
struct UnkObj190DB0
{
    char field_0x0[0x2C];
    int mField2C;         // 0x2C

    int GetField2C();     // 0x00190DB0
};

int UnkObj190DB0::GetField2C()
{
    return mField2C;
}

// UnkObj191320 (0x00191320): no RTTI; its layout is the fields these methods use.
struct UnkObj191320
{
    char field_0x0[0x3480];
    int mField3480;         // 0x3480

    int Method191320();     // 0x00191320
};

int UnkObj191320::Method191320()
{
    if (func_00190D88() == 0)
    {
        mField3480 = 0;
    }
    return 1;
}

// UnkObj1914A0 (0x001914A0..0x00191568): no RTTI; its layout is the fields these methods use.
struct UnkObj1914A0
{
    char field_0x0[0x4];
    int mField4;             // 0x4
    char field_0x8[0x2C];
    int mField34;            // 0x34
    char field_0x38[0x3448];
    int mField3480;          // 0x3480

    int GetField3480();      // 0x001914A0
    int GetField4();         // 0x00191558
    void Method191568();     // 0x00191568
};

int UnkObj1914A0::GetField3480()
{
    return mField3480;
}

int UnkObj1914A0::GetField4()
{
    return mField4;
}

void UnkObj1914A0::Method191568()
{
    mField34 += 1;
}

// UnkObj192470 (0x00192470): no RTTI; its layout is the fields these methods use.
struct UnkObj192470
{
    char field_0x0[0x20];
    int mField20;         // 0x20

    int GetField20();     // 0x00192470
};

int UnkObj192470::GetField20()
{
    return mField20;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_00191E60(int, f32, f32, f32); // 0x00191E60
int MemAlloc1BD958(int);                // 0x001BD958

int func_00190B80(int *arg0)
{
    return *arg0;
}

int func_00191560(int *arg0)
{
    return *arg0;
}

int func_00191DD8(f32 fparg0, f32 fparg1, f32 fparg2)
{
    int temp_v0;

    temp_v0 = MemAlloc1BD958(0x3C);
    if (temp_v0 != 0)
    {
        func_00191E60(temp_v0, fparg0, fparg1, fparg2);
    }
    return temp_v0;
}

int *func_00190E80();    // 0x00190E80
void func_00191510(int, int); // 0x00191510

struct UnkObj190BC0
{
    char pad0000[0x1900];
    char mPath1900[0x100]; // 0x1900: length unknown
};

// Whether the path at +0x1900 is the root, "/".
int func_00190BC0(UnkObj190BC0 *obj)
{
    return strcmp(obj->mPath1900, "/") == 0;
}

void func_00190D50(int arg0)
{
    func_00191510(arg0, 0x1F);
}

int func_00190E98()
{
    return *func_00190E80();
}

void func_00191550(int *arg0, int arg1)
{
    *arg0 = arg1;
}

struct UnkElem190B88
{
    char field_0x0[0x40];
};

struct UnkObj190B88
{
    char field_0x0[0x54];
    u16 mField54; // 0x54
};

int func_00190B88(int arg0, int arg1)
{
    return ((UnkObj190B88 *)(arg0 + (arg1 << 6)))->mField54 & 0x20;
}

struct UnkElem190EB8
{
    char field_0x0[0x84];
    int mField84; // 0x84
    int mField88; // 0x88
    int mField8C; // 0x8C
    int mField90; // 0x90
    char field_0x94[0x1A00 - 0x94];
};

int func_00190EB8(int arg0, int arg1)
{
    return ((UnkElem190EB8 *)((char *)arg0 + arg1 * 0x1A00))->mField84;
}

int func_00190ED0(int arg0, int arg1)
{
    return ((UnkElem190EB8 *)((char *)arg0 + arg1 * 0x1A00))->mField90;
}

int func_001911B0(int arg0, int arg1)
{
    return ((UnkElem190EB8 *)((char *)arg0 + arg1 * 0x1A00))->mField88;
}

struct UnkSub190C88;
void func_00190DC8(UnkSub190C88 *, const char *, const char *, int); // 0x00190DC8
void func_00191510(int, int);                                        // 0x00191510
void *func_001BC9D0(void *, int);                                    // 0x001BC9D0
extern "C" void func_001914A8();                                     // 0x001914A8
extern u16 data_002A55B0;

struct UnkSub190C88
{
    int mField00;          // 0x00
    char pad04[0x3C];
    int mField40;          // 0x40
    int mField44;          // 0x44
    int mField48;          // 0x48
    char pad4C[0x34];
    u8 mItems80[2][0x1A00]; // 0x80
    int mField3480;        // 0x3480
};

struct UnkAlloc190C88
{
    char pad00[0x14];
    UnkSub190C88 *mPtr14; // 0x14
};

void *func_00190C88()
{
    UnkAlloc190C88 *alloc = (UnkAlloc190C88 *)func_001BC9D0((void *)&func_001914A8, 0x3A80);
    if (alloc != 0)
    {
        UnkSub190C88 *sub = alloc->mPtr14;
        sub->mField00 = 0;
        sub->mField48 = 0;
        sub->mField3480 = 0;
        sub->mField44 = 0;
        sub->mField40 = 1;
        func_00191510((int)sub, 0);
        func_00190DC8(sub, "short", "long", 0);
        u8 *item = sub->mItems80[0];
        int i = 1;
        do
        {
            *(int *)(item + 0x00) = 1;
            i--;
            *(int *)(item + 0x04) = 0;
            *(int *)(item + 0x08) = 0;
            *(int *)(item + 0x0C) = 0;
            *(int *)(item + 0x10) = 0;
            *(int *)(item + 0x14) = 0;
            *(u16 *)(item + 0x1900) = data_002A55B0;
            item += 0x1A00;
        } while (i >= 0);
    }
    return alloc->mPtr14;
}

void func_00191520(u8 *arg0)
{
    *(int *)(arg0 + 0x04) = 0;
    *(int *)(arg0 + 0x00) = 1;
    *(int *)(arg0 + 0x08) = 0;
    *(int *)(arg0 + 0x0C) = 0;
    *(int *)(arg0 + 0x10) = 0;
    *(int *)(arg0 + 0x14) = 0;
    *(u16 *)(arg0 + 0x1900) = data_002A55B0;
}

struct UnkObj1911C8
{
    char pad00[0xC];
    int mField0C; // 0x0C
};

int func_001911C8()
{
    return ((UnkObj1911C8 *)func_00190E80())->mField0C != 0;
}

void func_00191510(int arg0, int arg1)
{
    *(int *)(arg0 + 0x30) = arg1;
    *(int *)(arg0 + 0x3C) = 0;
    *(int *)(arg0 + 0x34) = 0;
}

struct UnkSub191350
{
    char pad00[0x4C];
};

struct UnkObj191350
{
    char pad00[0x3480];
    int mCount3480;              // 0x3480
    char pad3484[0x48];
    UnkSub191350 mItems34CC[1];  // 0x34CC (val at +0x4C -> +0x34CC)
};

int func_00191350(UnkObj191350 *arg0)
{
    int n = arg0->mCount3480;
    int sum = 0;
    if (n > 0)
    {
        int *p = (int *)arg0->mItems34CC;
        do
        {
            int v = *p;
            n--;
            p = (int *)((u8 *)p + 0x4C);
            sum += v;
        } while (n != 0);
    }
    return sum;
}
