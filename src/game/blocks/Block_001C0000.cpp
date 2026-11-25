#include "common/types.h"

// Functions of 0x001C0000..0x001C3FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001BD978(void *);       // 0x001BD978
void func_002318F8(int, int);     // 0x002318F8
void func_00239BE0(int);          // 0x00239BE0
int func_0023CE78(int, int, int); // 0x0023CE78
int func_0023D320(int, int, int); // 0x0023D320

int func_001C00F8(int arg0, int arg1, int arg2)
{
    int result;

    func_00239BE0(0);
    result = func_0023D320(arg0 - 1, arg1, arg2);
    func_00239BE0(0);
    return result;
}

int func_001C02A0(int arg0, int arg1, int arg2)
{
    int result;

    func_00239BE0(0);
    result = func_0023CE78(arg0 - 1, arg1, arg2);
    func_00239BE0(0);
    return result;
}

void func_001C03A0(void *arg0)
{
    func_001BD978(arg0);
}

int func_001C13A8(u32 arg0)
{
    return (arg0 >> 0x18) | ((arg0 >> 8) & 0xFF00) | ((arg0 & 0xFF00) << 8) | (arg0 << 0x18);
}

int func_001C1428(u32 arg0)
{
    return (arg0 >> 0x18) | ((arg0 >> 8) & 0xFF00) | ((arg0 & 0xFF00) << 8) | (arg0 << 0x18);
}

void func_001C38D0(int arg0, int arg1)
{
    func_002318F8(arg1, arg0 + 0x3030);
}
