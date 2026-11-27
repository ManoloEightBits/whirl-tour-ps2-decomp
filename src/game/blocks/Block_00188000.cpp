#include "common/types.h"

// Functions of 0x00188000..0x0018BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8();       // 0x001974D8
void func_00197510();       // 0x00197510
void func_0019A6F0(void *);       // 0x0019A6F0
void MemFree1BD978(void *); // 0x001BD978

void func_0018B528()
{
}

int func_0018B7B8(int arg0)
{
    return arg0 + 0x2B0;
}

void func_0018BA58()
{
    func_001974D8();
}

void func_0018BA78()
{
    func_00197510();
}

void func_0018BA98(void *arg0)
{
    func_0019A6F0(arg0);
}

void func_0018BF80(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001911B0(int, int); // 0x001911B0

// UnkObj18B748 (0x0018B748..0x0018B750): no RTTI; its layout is the fields these methods use.
struct UnkObj18B748
{
    char field_0x0[0x560];
    int mField560;         // 0x560
    char field_0x564[0x8];
    int mField56C;         // 0x56C

    int GetField560();     // 0x0018B748
    int Method18B750();    // 0x0018B750
};

int UnkObj18B748::GetField560()
{
    return mField560;
}

int UnkObj18B748::Method18B750()
{
    return mField56C == 0x32;
}

// UnkObj18B7C0 (0x0018B7C0..0x0018B7E0): no RTTI; its layout is the fields these methods use.
struct UnkObj18B7C0
{
    char field_0x0[0x94];
    int mField94;           // 0x94
    char field_0x98[0x4];
    int mField9C;           // 0x9C
    char field_0xA0[0x4C4];
    int mField564;          // 0x564

    void Method18B7C0();    // 0x0018B7C0
    int GetField9C();       // 0x0018B7E0
};

void UnkObj18B7C0::Method18B7C0()
{
    func_001911B0(mField94, mField564);
}

int UnkObj18B7C0::GetField9C()
{
    return mField9C;
}
