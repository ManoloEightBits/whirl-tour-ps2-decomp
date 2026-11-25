#include "common/types.h"

// Functions of 0x00168000..0x0016BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00168338(); // 0x00168338

void func_00168318()
{
    func_00168338();
}

void func_00168B38();                   // 0x00168B38
void func_001A1938(int, int, int);      // 0x001A1938
void func_001A2340(int, int);           // 0x001A2340
void func_001A2DB8(int);                // 0x001A2DB8
void func_001A2FB8(int);                // 0x001A2FB8
void func_001A43C8(int, int, int, int); // 0x001A43C8
void func_001A43E0(int, int, int, int); // 0x001A43E0
void func_001A43F8(int, int, int, int); // 0x001A43F8
void func_001A4410(int);                // 0x001A4410
void func_001A4490(int);                // 0x001A4490
void func_001A4930(int);                // 0x001A4930

// UnkObj168A20 (0x00168A20..0x00168A40): no RTTI; its layout is the fields these methods use.
struct UnkObj168A20
{
    char field_0x0[0x4];
    f32 mField4;                   // 0x4
    char field_0x8[0x4];
    int mFieldC;                   // 0xC
    f32 mField10;                  // 0x10
    char field_0x14[0xC];
    int mField20;                  // 0x20
    int mField24;                  // 0x24
    int mField28;                  // 0x28

    void Method168A20(f32 fparg0); // 0x00168A20
    void Method168A40();           // 0x00168A40
};

void UnkObj168A20::Method168A20(f32 fparg0)
{
    mField4 = (f32) (mField4 + fparg0);
    mField10 = (f32) (mField10 + fparg0);
}

void UnkObj168A20::Method168A40()
{
    if (mFieldC >= 2)
    {
        func_00168B38();
        func_001A2DB8(0xBE2);
        func_001A2DB8(0xDE1);
        func_001A2340(0xDE1, 0xCDEE3B39);
        func_001A4930(0);
        func_001A43E0(3, 0x1406, 0, mField20);
        func_001A43F8(4, 0x1401, 0, mField24);
        func_001A43C8(2, 0x1406, 0, mField28);
        func_001A4410(0x8074);
        func_001A4410(0x8076);
        func_001A4410(0x8078);
        func_001A1938(5, 0, mFieldC * 2);
        func_001A4490(0x8074);
        func_001A4490(0x8078);
        func_001A4490(0x8076);
        func_001A4930(1);
        func_001A2FB8(0xDE1);
        func_001A2FB8(0xBE2);
    }
}
