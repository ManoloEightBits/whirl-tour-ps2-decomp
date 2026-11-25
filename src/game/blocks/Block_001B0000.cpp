#include "common/types.h"

// Functions of 0x001B0000..0x001B3FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001B0F60(int, int); // 0x001B0F60
int func_001BD958(int);       // 0x001BD958
void func_001BD978(void *);   // 0x001BD978

void func_001B0E98(void *arg0)
{
    func_001BD978(arg0);
}

int func_001B0F18(int arg0)
{
    int result;

    result = func_001BD958(0xC);
    if (result != 0)
    {
        func_001B0F60(result, arg0);
    }
    return result;
}

void func_001B0F70(void *arg0)
{
    func_001BD978(arg0);
}

int func_001B1038(int arg0)
{
    return (arg0 * 8) + 0x38;
}

int func_001B2940()
{
    return 0;
}

void func_001B2980(void *arg0)
{
    func_001BD978(arg0);
}
