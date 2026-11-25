#include "common/types.h"

// Functions of 0x00140000..0x00143FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00142400();         // 0x00142400
void func_001A6368();         // 0x001A6368
void func_001A6458();         // 0x001A6458
int func_001A87E8();          // 0x001A87E8
void func_001A8950();         // 0x001A8950
void func_001A89F0();         // 0x001A89F0
void func_001A8C10(int, int); // 0x001A8C10
void func_001A8D50();         // 0x001A8D50
void func_001BD978(void *);   // 0x001BD978

void func_00140A88()
{
}

void func_001416A0(void *arg0)
{
}

void func_001416A8()
{
}

void func_001416B0()
{
}

void func_001416B8()
{
}

void func_00141A18()
{
    func_00142400();
}

void func_001425E0()
{
}

void func_00142D70()
{
    func_001A8C10(1, 5);
}

void func_00142D90()
{
    func_001A8C10(0x18, 0x2F);
}

void func_001430E0(void *arg0)
{
    func_001BD978(arg0);
}

void func_001436B0()
{
}

void func_001436B8()
{
    func_001A89F0();
}

void func_001436D8()
{
    func_001A8950();
}

int func_001436F8()
{
    return func_001A87E8() == 0;
}

void func_00143718()
{
    func_001A6368();
}

void func_00143738()
{
    func_001A6458();
}

void func_00143758()
{
    func_001A8D50();
}
