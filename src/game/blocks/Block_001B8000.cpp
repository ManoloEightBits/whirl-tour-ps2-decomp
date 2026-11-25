#include "common/types.h"

// Functions of 0x001B8000..0x001BBFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

int func_001B9D98();        // 0x001B9D98
void func_001BD978(void *); // 0x001BD978
void func_001C11D8();       // 0x001C11D8
void func_001C1450(int);    // 0x001C1450

void func_001B81C8(int arg0)
{
    func_001C11D8();
    func_001C1450(arg0 + 0x10);
}

void func_001B9160(int arg0)
{
    func_001C11D8();
    func_001C1450(arg0 + 0x10);
}

void func_001B9240(void *arg0)
{
    func_001BD978(arg0);
}

void func_001B9D78(void *arg0)
{
    func_001BD978(arg0);
}

void func_001BA638(void *arg0)
{
    func_001BD978(arg0);
}

int func_001BA658(int arg0)
{
    int result;

    result = 0;
    if (arg0 != 0)
    {
        result = func_001B9D98();
    }
    return result;
}
