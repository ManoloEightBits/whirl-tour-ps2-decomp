#include "common/types.h"

// Functions of 0x001B4000..0x001B7FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001BD978(void *); // 0x001BD978
void func_002306F0(int);    // 0x002306F0

void func_001B4F08()
{
}

void func_001B4F10()
{
    func_002306F0(0);
}

void func_001B4F30()
{
}

void func_001B6590(void *arg0)
{
    func_001BD978(arg0);
}
