#include "common/types.h"

// Functions of 0x0016C000..0x0016FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

struct EnvObj;
void EnvObjCleanup14FB70(EnvObj *); // 0x0014FB70

void MemFree1BD978(void *);         // 0x001BD978

void func_0016FDB8(EnvObj *obj)
{
    EnvObjCleanup14FB70(obj);
    MemFree1BD978(obj);
}
