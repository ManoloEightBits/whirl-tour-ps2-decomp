#include "common/types.h"

// Functions of 0x0018C000..0x0018FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_0018CC70();       // 0x0018CC70
void func_0018D600();       // 0x0018D600
void func_0018E678();       // 0x0018E678
void func_0018EFD8();       // 0x0018EFD8
void func_001BD978(void *); // 0x001BD978

void func_0018D1E8()
{
    func_0018CC70();
}

void func_0018D990()
{
    func_0018D600();
}

void func_0018E658()
{
    func_0018E678();
}

void func_0018F980()
{
    func_0018EFD8();
}

void func_0018FA18(void *arg0)
{
    func_001BD978(arg0);
}
