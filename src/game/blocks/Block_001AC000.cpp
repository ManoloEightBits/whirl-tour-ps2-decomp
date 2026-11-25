#include "common/types.h"

// Functions of 0x001AC000..0x001AFFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001BD978(void *); // 0x001BD978

int func_001ACC08()
{
    return 1;
}

void func_001AF330(void *arg0)
{
    func_001BD978(arg0);
}

void func_001AFBF8(void *arg0)
{
    func_001BD978(arg0);
}
