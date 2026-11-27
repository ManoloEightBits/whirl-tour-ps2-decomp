#include "common/types.h"
#include "common/libc.h"

// Functions of 0x00194000..0x00197FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8();       // 0x001974D8
void MemFree1BD978(void *); // 0x001BD978

void func_001957F0()
{
    func_001974D8();
}

void func_00195A10(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_00196160()
{
}

void func_001961B0()
{
}

void func_001962C8()
{
}

void func_001962D0()
{
}

void func_00196410(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001965B0()
{
}

void func_001965F8(void *arg0)
{
    MemFree1BD978(arg0);
}

int func_00196648(int arg0)
{
    return ((arg0 - 1) * 0xC) + 0x10;
}

int func_00196D80()
{
    return 0;
}

void func_001AC198(int); // 0x001AC198
void func_001AC398(int); // 0x001AC398
void func_001AC3F0(int); // 0x001AC3F0

// UnkObj194EC0 (0x00194EC0): no RTTI; its layout is the fields these methods use.
struct UnkObj194EC0
{
    char field_0x0[0x2C];
    void *mField2C;        // 0x2C
    char field_0x30[0x48];
    void *mField78;        // 0x78
    void *mField7C;        // 0x7C
    void *mField80;        // 0x80
    void *mField84;        // 0x84

    void Method194EC0();   // 0x00194EC0
};

void UnkObj194EC0::Method194EC0()
{
    MemFree1BD978(mField78);
    MemFree1BD978(mField80);
    MemFree1BD978(mField7C);
    MemFree1BD978(mField84);
    MemFree1BD978(mField2C);
    MemFree1BD978(this);
}

// UnkObj196000 (0x00196000..0x00196030): no RTTI; its layout is the fields these methods use.
struct UnkObj196000
{
    char field_0x0[0x4];
    int mField4;          // 0x4
    int mField8;          // 0x8
    int mFieldC;          // 0xC
    int mField10;         // 0x10
    int mField14;         // 0x14
    char field_0x18[0x4];
    int mField1C;         // 0x1C
    char field_0x20[0x4];
    int mField24;         // 0x24

    int GetField8();      // 0x00196000
    int GetFieldC();      // 0x00196008
    int GetField10();     // 0x00196010
    int GetField14();     // 0x00196018
    int GetField24();     // 0x00196020
    int GetField4();      // 0x00196028
    int GetField1C();     // 0x00196030
};

int UnkObj196000::GetField8()
{
    return mField8;
}

int UnkObj196000::GetFieldC()
{
    return mFieldC;
}

int UnkObj196000::GetField10()
{
    return mField10;
}

int UnkObj196000::GetField14()
{
    return mField14;
}

int UnkObj196000::GetField24()
{
    return mField24;
}

int UnkObj196000::GetField4()
{
    return mField4;
}

int UnkObj196000::GetField1C()
{
    return mField1C;
}

// UnkObj196630 (0x00196630): no RTTI; its layout is the fields these methods use.
struct UnkObj196630
{
    char field_0x0[0x2];
    u16 mField2;         // 0x2

    int Method196630();  // 0x00196630
};

int UnkObj196630::Method196630()
{
    return ((mField2 - 1) * 0xC) + 0x10;
}

// UnkObj1972B0 (0x001972B0..0x001972F8): no RTTI; its layout is the fields these methods use.
struct UnkObj1972B0
{
    char field_0x0[0x8];
    int mField8;         // 0x8

    void Method1972B0(); // 0x001972B0
    void Method1972D8(); // 0x001972D8
    void Method1972F8(); // 0x001972F8
};

void UnkObj1972B0::Method1972B0()
{
    int tmp;

    tmp = mField8;
    if (tmp != 0)
    {
        func_001AC198(tmp);
    }
}

void UnkObj1972B0::Method1972D8()
{
    func_001AC3F0(mField8);
}

void UnkObj1972B0::Method1972F8()
{
    func_001AC398(mField8);
}

// UnkObj1974D8 (0x001974D8): no RTTI; its layout is the fields these methods use.
struct UnkObj1974D8
{
    void *mField00;           // 0x00
    void *mField04;           // 0x04
    char field_0x8[0xC];
    u16 mField14;             // 0x14
    char field_0x16[0x6];
    void (*mFreeCb1C)(void *); // 0x1C
    char field_0x20[0x20];
    UnkObj1974D8 *mChildren40; // 0x40
    char field_0x44[0x4C];
    char *mName90;            // 0x90

    void Method1974D8();      // 0x001974D8
    void Method1975D0();      // 0x001975D0
};

void UnkObj1974D8::Method1974D8()
{
    u16 tmp;

    tmp = mField14;
    if (tmp & 0x10)
    {
        mField14 = (u16) (tmp | 0x20);
        return;
    }
    Method1975D0();
}

void func_001BD360(void *); // 0x001BD360
void func_0019A6F0(void *); // 0x0019A6F0

void UnkObj1974D8::Method1975D0()
{
    if (mName90 != 0)
    {
        MemFree1BD978(mName90);
        mName90 = 0;
    }
    UnkObj1974D8 *cur = mChildren40;
    UnkObj1974D8 *next = *(UnkObj1974D8 **)cur;
    if (next != 0)
    {
        do
        {
            cur->Method1975D0();
            cur = next;
            next = *(UnkObj1974D8 **)next;
        } while (next != 0);
    }
    if (mField00 != 0 || mField04 != 0)
    {
        func_001BD360(this);
    }
    if (mFreeCb1C != 0)
    {
        mFreeCb1C(this);
        return;
    }
    MemFree1BD978(this);
}

void func_00197A70(void **arg0)
{
    void **cur = (void **)*arg0;
    void **next = (void **)*cur;
    if (next != 0)
    {
        do
        {
            func_0019A6F0(cur);
            cur = next;
            next = (void **)*next;
        } while (next != 0);
    }
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_001959B8(int, f32, f32, f32, f32); // 0x001959B8
void func_001973A0(int, f32, f32, f32);      // 0x001973A0
void func_00197468(int, int);                // 0x00197468
int func_001BD558(int, int);                 // 0x001BD558
int MemAlloc1BD958(int);                     // 0x001BD958

int func_00195940(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3)
{
    int temp_v0;

    temp_v0 = MemAlloc1BD958(0x44);
    if (temp_v0 != 0)
    {
        func_001959B8(temp_v0, fparg0, fparg1, fparg2, fparg3);
    }
    return temp_v0;
}

void func_00197468(int objInt, int nameInt)
{
    UnkObj1974D8 *obj = (UnkObj1974D8 *)objInt;
    const char *name = (const char *)nameInt;
    if (obj->mName90 != 0)
    {
        MemFree1BD978(obj->mName90);
        obj->mName90 = 0;
    }
    if (name != 0)
    {
        char *buf = (char *)MemAlloc1BD958(strlen(name) + 1);
        obj->mName90 = buf;
        if (buf != 0)
            strcpy(buf, name);
    }
}

struct UnkArg194DE0
{
    char pad00[0x4];
    int mCount04;  // 0x04
    char pad08[0xC0];
    int mFieldC8;  // 0xC8
};

struct UnkRes194DE0
{
    char pad00[0x10];
    void *mArg10; // 0x10
};

void func_00192478(void *, int, void *); // 0x00192478

void *func_00194DE0(int arg0Int)
{
    UnkArg194DE0 *arg0 = (UnkArg194DE0 *)arg0Int;
    UnkRes194DE0 *res = (UnkRes194DE0 *)func_001BD558(arg0->mCount04 * 0x28 + 0xA0, 4);
    if (res != 0)
    {
        res->mArg10 = arg0;
        func_00192478(res, arg0->mFieldC8, (u8 *)res + 0xA0);
    }
    return res;
}

int func_00197318(int arg0, f32 fparg0, f32 fparg1, f32 fparg2)
{
    int temp_v0;

    temp_v0 = func_001BD558(0xA0, 4);
    if (temp_v0 != 0)
    {
        func_001973A0(temp_v0, fparg0, fparg1, fparg2);
        func_00197468(temp_v0, arg0);
    }
    return temp_v0;
}

struct UnkObj1978E0
{
    char pad00[0x8];
    int mField08; // 0x08
};

void func_001978E0(UnkObj1978E0 *arg0)
{
    func_001BD360(arg0);
    arg0->mField08 = 0;
}

struct UnkNode
{
    char pad00[0x24];
    int mField24; // 0x24
    char pad28[0x48];
    int mField70; // 0x70
};

void func_00194F90(UnkNode *arg0)
{
    arg0->mField70 = 0;
    arg0->mField24 = 0;
}

struct UnkObj196430
{
    char pad00[0xCC];
    int mCountCC;   // 0xCC
    char padD0[0x10];
    void *mArrE0[1]; // 0xE0
};

void func_00196430(void *arg0Void, void *arg1)
{
    UnkObj196430 *arg0 = (UnkObj196430 *)arg0Void;
    for (int i = 0; i < arg0->mCountCC; i++)
        arg0->mArrE0[i] = arg1;
}

void func_00196460(UnkObj196430 *arg0, void *arg1, void *arg2)
{
    for (int i = 0; i < arg0->mCountCC; i++)
    {
        if (arg0->mArrE0[i] == arg1)
            arg0->mArrE0[i] = arg2;
    }
}
