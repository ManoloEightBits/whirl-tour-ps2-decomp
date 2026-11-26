#include "common/types.h"
#include "common/libc.h"

// Functions of 0x001BC000..0x001BFFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001BD4A0();           // 0x001BD4A0
void MemFree1BD978(void *arg0); // 0x001BD978
void func_00239BE0(int);        // 0x00239BE0
void func_0023CCF8(int);        // 0x0023CCF8

void func_001BC318(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001BC490(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001BC4F8()
{
}

void func_001BC500()
{
}

void func_001BCE28()
{
}

int func_001BCEF8(int arg0)
{
    return arg0 + 4;
}

void func_001BD810()
{
}

void MemFree1BD978(void *arg0)
{
    func_001BD4A0();
}

void func_001BDA00()
{
}

void func_001BDCA0(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001BDEA8()
{
}

void func_001BF600(void *dst, const void *src, unsigned int n)
{
    memcpy(dst, src, n);
}

int func_001BF620()
{
    return 1;
}

void func_001BF668(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001BFFA0(int arg0)
{
    func_00239BE0(0);
    func_0023CCF8(arg0 - 1);
    func_00239BE0(0);
}

int func_001BFFD8()
{
    return 0;
}

int func_001BFFE0()
{
    return 0;
}

int func_001BFFE8()
{
    return 0;
}

void MemFree1BD978(void *);      // 0x001BD978
int func_001C13A8(unsigned int); // 0x001C13A8

// UnkObj1BD3E8 (0x001BD3E8): no RTTI; its layout is the fields these methods use.
struct UnkObj1BD3E8
{
    char field_0x0[0x4];
    int mField4;         // 0x4

    int GetField4();     // 0x001BD3E8
};

int UnkObj1BD3E8::GetField4()
{
    return mField4;
}

// UnkObj1BD870 (0x001BD870..0x001BD8D8): no RTTI; its layout is the fields these methods use.
struct UnkObj1BD870
{
    char field_0x0[0x4];
    int mField4;               // 0x4
    int mField8;               // 0x8
    int mFieldC;               // 0xC
    int mField10;              // 0x10
    int mField14;              // 0x14

    void SetField14(int v); // 0x001BD870
    void Method1BD878();       // 0x001BD878
    void Method1BD888();       // 0x001BD888
    void Method1BD8A0();       // 0x001BD8A0
    void Method1BD8B8();       // 0x001BD8B8
    int GetField8();           // 0x001BD8C8
    int GetField10();          // 0x001BD8D0
    int GetFieldC();           // 0x001BD8D8
};

void UnkObj1BD870::SetField14(int v)
{
    mField14 = v;
}

void UnkObj1BD870::Method1BD878()
{
    mField4 |= 1;
}

void UnkObj1BD870::Method1BD888()
{
    mField4 &= 0xFFFFFFFE;
}

void UnkObj1BD870::Method1BD8A0()
{
    mField4 &= 0xFFFFFFFD;
}

void UnkObj1BD870::Method1BD8B8()
{
    mField4 |= 2;
}

int UnkObj1BD870::GetField8()
{
    return mField8;
}

int UnkObj1BD870::GetField10()
{
    return mField10;
}

int UnkObj1BD870::GetFieldC()
{
    return mFieldC;
}

// UnkObj1BD9F0 (0x001BD9F0): no RTTI; its layout is the fields these methods use.
struct UnkObj1BD9F0
{
    char field_0x0[0x4];
    int mField4;         // 0x4

    int Method1BD9F0();  // 0x001BD9F0
};

int UnkObj1BD9F0::Method1BD9F0()
{
    return mField4 & 1;
}

// UnkObj1BDCE8 (0x001BDCE8): no RTTI; its layout is the fields these methods use.
struct UnkObj1BDCE8
{
    f32 mField0;        // 0x0
    f32 mField4;        // 0x4

    f32 Method1BDCE8(); // 0x001BDCE8
};

f32 UnkObj1BDCE8::Method1BDCE8()
{
    return mField0 + mField4;
}

// UnkObj1BEAD0 (0x001BEAD0): no RTTI; its layout is the fields these methods use.
struct UnkObj1BEAD0
{
    char field_0x0[0x8];
    int mField8;         // 0x8

    int GetField8();     // 0x001BEAD0
};

int UnkObj1BEAD0::GetField8()
{
    return mField8;
}

// UnkObj1BEC48 (0x001BEC48): no RTTI; its layout is the fields these methods use.
struct UnkObj1BEC48
{
    char field_0x0[0x4];
    int mField4;          // 0x4
    int mField8;          // 0x8
    int mFieldC;          // 0xC
    int mField10;         // 0x10
    int mField14;         // 0x14
    char field_0x18[0x4];
    void *mField1C;       // 0x1C
    void *mField20;       // 0x20
    void *mField24;       // 0x24

    void Method1BEC48();  // 0x001BEC48
};

void UnkObj1BEC48::Method1BEC48()
{
    int temp_v1;
    void *temp_a0;
    void *temp_a0_2;

    temp_v1 = mField4;
    if (temp_v1 & 1)
    {
        if (temp_v1 & 2)
        {
            MemFree1BD978(mField24);
        }
    }
    else
    {
        temp_a0 = mField20;
        if (temp_a0 != NULL)
        {
            MemFree1BD978(temp_a0);
        }
        temp_a0_2 = mField1C;
        if (temp_a0_2 != NULL)
        {
            MemFree1BD978(temp_a0_2);
        }
    }
    mField20 = NULL;
    mField24 = NULL;
    mField8 = 0;
    mFieldC = 0;
    mField10 = 0;
    mField14 = 0;
    mField1C = NULL;
    MemFree1BD978(this);
}

// UnkObj1BF4E8 (0x001BF4E8): no RTTI; its layout is the fields these methods use.
struct UnkObj1BF4E8
{
    int mField0;         // 0x0
    int mField4;         // 0x4
    int mField8;         // 0x8

    void Method1BF4E8(); // 0x001BF4E8
};

void UnkObj1BF4E8::Method1BF4E8()
{
    mField0 = func_001C13A8(mField0);
    mField8 = func_001C13A8(mField8);
    mField4 = func_001C13A8(mField4);
}

// UnkObj1BF6C8 (0x001BF6C8): no RTTI; its layout is the fields these methods use.
struct UnkObj1BF6C8
{
    char field_0x0[0x8];
    int mField8;                 // 0x8
    int mFieldC;                 // 0xC

    void Method1BF6C8(int arg1); // 0x001BF6C8
};

void UnkObj1BF6C8::Method1BF6C8(int arg1)
{
    int tmp;

    tmp = mField8 - mFieldC;
    if (tmp == arg1)
    {
        mField8 = tmp;
    }
}

// UnkObj1BFAD0 (0x001BFAD0..0x001BFAE8): no RTTI; its layout is the fields these methods use.
struct UnkObj1BFAD0
{
    char field_0x0[0x8];
    u32 mField8;         // 0x8
    u32 mFieldC;         // 0xC
    int mField10;        // 0x10

    int Method1BFAD0();  // 0x001BFAD0
    int GetField10();    // 0x001BFAE8
};

int UnkObj1BFAD0::Method1BFAD0()
{
    return (u32) mFieldC >= (u32) mField8;
}

int UnkObj1BFAD0::GetField10()
{
    return mField10;
}

// UnkObj1BFAF0 (0x001BFAF0..0x001BFB60): no RTTI; its layout is the fields these methods use.
struct UnkObj1BFAF0
{
    int mField0;                 // 0x0
    char field_0x4[0x4];
    int mField8;                 // 0x8
    int mFieldC;                 // 0xC
    char field_0x10[0x4];
    int mField14;                // 0x14

    int GetFieldC();             // 0x001BFAF0
    int GetField8();             // 0x001BFAF8
    void Method1BFB60(int arg1); // 0x001BFB60
};

int UnkObj1BFAF0::GetFieldC()
{
    return mFieldC;
}

int UnkObj1BFAF0::GetField8()
{
    return mField8;
}

void UnkObj1BFAF0::Method1BFB60(int arg1)
{
    int tmp;

    tmp = mFieldC + arg1;
    mFieldC = tmp;
    mField14 += arg1;
    if (tmp == mField8)
    {
        mField0 = 3;
    }
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void *MemAlloc1BD958(int); // 0x001BD958
extern int data_0027B6BC;
extern int data_0027B6C4;

s8 *func_001BC448()
{
    s8 *temp_v0;

    temp_v0 = (s8 *)MemAlloc1BD958(0x101);
    if (temp_v0 != NULL)
    {
        *temp_v0 = 0;
        memset(temp_v0 + 1, 0, 0x100);
    }
    return temp_v0;
}

void func_001BC9A8()
{
    func_001BCEF8(data_0027B6BC);
}

void func_001BCF08(int *arg0, int arg1)
{
    *arg0 = arg1;
}

void func_001BD998(int arg0)
{
    data_0027B6C4 = arg0;
}

void func_001BDA08(int *arg0)
{
    int temp_v0;

    temp_v0 = data_0027B6C4 + 0x24;
    *arg0 = temp_v0;
    malloc(temp_v0);
}

int func_001BFAA8(int *arg0)
{
    return *arg0;
}

int func_001BFAB0(int *arg0)
{
    return *arg0 == 2;
}

int func_001BCF00(int *arg0)
{
    return *arg0;
}

void func_001BD0C0(int);           // 0x001BD0C0
void func_001BD228(void *);        // 0x001BD228
void *func_001BE268(int, int *);   // 0x001BE268
int func_001BFEE0(int);            // 0x001BFEE0
void func_001C00F8(int, void *, int); // 0x001C00F8
extern int data_0027B6C0;

// For entries 1..256 of a byte table: bit 0 is copied to bit 1, and bit 2 is set when bit 0 is set and
// bit 1 was clear.
void func_001BC4B0(u8 *table)
{
    u8 *p = table + 1;
    for (int i = 0; i < 256; i++)
    {
        u8 v = *p;
        int bit = v & 1;
        *p = bit | (bit * 2) | ((bit & ~((v >> 1) & 1)) * 4);
        p++;
    }
}

void func_001BC960()
{
    func_001BD0C0(data_0027B6BC);
    func_001BD0C0(data_0027B6C0);
    data_0027B6BC = 0;
    data_0027B6C0 = 0;
}

struct UnkObj1BD038
{
    int mField00;       // 0x00
    int mSub04[3];      // 0x04: set up by func_001BD228
};

// Allocates a UnkObj1BD038 and initializes it (as func_001BD120).
UnkObj1BD038 *func_001BD038()
{
    UnkObj1BD038 *obj = (UnkObj1BD038 *)MemAlloc1BD958(0x10);
    if (obj != 0)
    {
        obj->mField00 = 0;
        func_001BD228(&obj->mSub04);
    }
    return obj;
}

void func_001BD120(UnkObj1BD038 *obj)
{
    obj->mField00 = 0;
    func_001BD228(&obj->mSub04);
}

int func_001BF0C0(int arg0, int arg1)
{
    int size;

    int obj = func_001BFEE0(arg1);
    if (obj != 0)
    {
        void *data = func_001BE268(arg0, &size);
        if (data != 0)
        {
            func_001C00F8(obj, data, size);
            MemFree1BD978(data);
        }
        func_001BFFA0(obj);
    }
    return 0;
}

void *func_001BD558(int size, int kind); // 0x001BD558

// The game's allocator: func_001BD558 with kind 3.
void *MemAlloc1BD958(int size)
{
    return func_001BD558(size, 3);
}

int func_001BFAC0(int arg0)
{
    return *(int *)arg0 == 3;
}
