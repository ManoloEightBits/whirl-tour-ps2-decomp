#include "common/types.h"

// Functions of 0x001BC000..0x001BFFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001BD4A0();           // 0x001BD4A0
void func_001BD978(void *arg0); // 0x001BD978
void func_0022F45C();           // 0x0022F45C
void func_00239BE0(int);        // 0x00239BE0
void func_0023CCF8(int);        // 0x0023CCF8

void func_001BC318(void *arg0)
{
    func_001BD978(arg0);
}

void func_001BC490(void *arg0)
{
    func_001BD978(arg0);
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

void func_001BD978(void *arg0)
{
    func_001BD4A0();
}

void func_001BDA00()
{
}

void func_001BDCA0(void *arg0)
{
    func_001BD978(arg0);
}

void func_001BDEA8()
{
}

void func_001BF600()
{
    func_0022F45C();
}

int func_001BF620()
{
    return 1;
}

void func_001BF668(void *arg0)
{
    func_001BD978(arg0);
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

void func_001BD978(void *);      // 0x001BD978
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
            func_001BD978(mField24);
        }
    }
    else
    {
        temp_a0 = mField20;
        if (temp_a0 != NULL)
        {
            func_001BD978(temp_a0);
        }
        temp_a0_2 = mField1C;
        if (temp_a0_2 != NULL)
        {
            func_001BD978(temp_a0_2);
        }
    }
    mField20 = NULL;
    mField24 = NULL;
    mField8 = 0;
    mFieldC = 0;
    mField10 = 0;
    mField14 = 0;
    mField1C = NULL;
    func_001BD978(this);
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
