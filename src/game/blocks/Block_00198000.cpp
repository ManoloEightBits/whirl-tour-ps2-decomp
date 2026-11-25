#include "common/types.h"

// Functions of 0x00198000..0x0019BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00197BC8(int);                               // 0x00197BC8
void func_001982D0(int, int);                          // 0x001982D0
void func_00198628(int, int, int, int);                // 0x00198628
void func_00198E08(int, int, int, int, int, int, int); // 0x00198E08
void func_00199738();                                  // 0x00199738
void func_0019B2C0();                                  // 0x0019B2C0
void func_001A2DB8(int);                               // 0x001A2DB8
void func_001A3638(int);                               // 0x001A3638
void func_001A3808();                                  // 0x001A3808
void func_001BD240(int);                               // 0x001BD240
int func_001BD958(int);                                // 0x001BD958
void func_001BD978(void *);                            // 0x001BD978

int func_00198090(int arg0)
{
    int result;

    result = func_001BD958(0x318);
    if (result != 0)
    {
        func_00197BC8(result);
        func_001982D0(result, arg0);
    }
    return result;
}

void func_00198330(int arg0, int arg1)
{
    if (arg1 != 0)
    {
        func_001BD240(arg0 + 0xC);
    }
}

void func_001983A0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    func_00198E08(arg0 + 0x2C, arg1, arg2, arg3, arg4, arg5, arg6);
}

int func_00198578(int arg0, int arg1, int arg2)
{
    int result;

    result = func_001BD958(0x14);
    if (result != 0)
    {
        func_00198628(result, arg0, arg1, arg2);
    }
    return result;
}

int func_00198D00(int arg0)
{
    return arg0;
}

int func_00198D08(int arg0)
{
    return arg0 + 0x40;
}

int func_00198D10(int arg0)
{
    return arg0 + 0x80;
}

int func_00198D18(int arg0)
{
    return arg0 + 0xC0;
}

int func_00198D50(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    int result;

    result = func_001BD958(0x34);
    if (result != 0)
    {
        func_00198E08(result, arg0, arg1, arg2, arg3, arg4, arg5);
    }
    return result;
}

void func_00198DE8(void *arg0)
{
    func_001BD978(arg0);
}

void Release198F38(void *arg0)
{
    func_001BD978(arg0);
}

void func_001990C8()
{
    func_00199738();
}

void func_00199738()
{
}

void func_0019A610()
{
}

void DrawEnd19A6B0()
{
    func_001A2DB8(0xB71);
    func_001A3638(0x1701);
    func_001A3808();
    func_001A3638(0x1700);
    func_001A3808();
}

void func_0019B778()
{
    func_0019B2C0();
}
