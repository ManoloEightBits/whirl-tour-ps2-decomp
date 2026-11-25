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
