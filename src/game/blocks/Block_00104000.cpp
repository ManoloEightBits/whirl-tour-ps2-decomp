#include "common/types.h"

// Functions of 0x00104000..0x00107FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00105F18(); // 0x00105F18
void func_00106C38(); // 0x00106C38

void func_00106C18()
{
    func_00106C38();
}

void func_00106C38()
{
}

void func_00106C40()
{
    func_00105F18();
}

void func_00106C60()
{
}
