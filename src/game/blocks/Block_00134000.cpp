#include "common/types.h"

// Functions of 0x00134000..0x00137FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001562E8();    // 0x001562E8
void func_001BDCF8(int); // 0x001BDCF8
void func_001BDE60(int); // 0x001BDE60

void func_00135B58()
{
    func_001562E8();
}

void func_00136C50(int arg0)
{
    func_001BDCF8(arg0 + 0xC);
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
