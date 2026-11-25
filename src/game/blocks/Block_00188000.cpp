#include "common/types.h"

// Functions of 0x00188000..0x0018BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8();       // 0x001974D8
void func_00197510();       // 0x00197510
void func_0019A6F0();       // 0x0019A6F0
void func_001BD978(void *); // 0x001BD978

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

void func_0018BA98()
{
    func_0019A6F0();
}

void func_0018BF80(void *arg0)
{
    func_001BD978(arg0);
}
