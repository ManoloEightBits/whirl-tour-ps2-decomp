#include "common/types.h"

// Functions of 0x00100000..0x00103FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00101250();       // 0x00101250
void func_001017A8();       // 0x001017A8
void func_001A4DA8();       // 0x001A4DA8
void func_001BD978(void *); // 0x001BD978

void func_00100B20()
{
    func_001A4DA8();
}

void func_00100B70()
{
}

void func_00101768()
{
    func_00101250();
}

void func_00101788()
{
    func_001017A8();
}

void func_001033C0(void *arg0)
{
    func_001BD978(arg0);
}
