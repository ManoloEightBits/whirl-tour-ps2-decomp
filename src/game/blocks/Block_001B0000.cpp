#include "common/types.h"

// Functions of 0x001B0000..0x001B3FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001B0F60(int, int); // 0x001B0F60
int MemAlloc1BD958(int);       // 0x001BD958
void MemFree1BD978(void *);   // 0x001BD978

void func_001B0E98(void *arg0)
{
    MemFree1BD978(arg0);
}

int func_001B0F18(int arg0)
{
    int result;

    result = MemAlloc1BD958(0xC);
    if (result != 0)
    {
        func_001B0F60(result, arg0);
    }
    return result;
}

void func_001B0F70(void *arg0)
{
    MemFree1BD978(arg0);
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
    MemFree1BD978(arg0);
}

// UnkObj1B0438 (0x001B0438): no RTTI; its layout is the fields these methods use.
struct UnkObj1B0438
{
    char field_0x0[0x5C];
    int mField5C;         // 0x5C

    int Method1B0438();   // 0x001B0438
};

int UnkObj1B0438::Method1B0438()
{
    return (mField5C * 4) + 0x60;
}

// UnkObj1B0F08 (0x001B0F08): no RTTI; its layout is the fields these methods use.
struct UnkObj1B0F08
{
    char field_0x0[0x34];
    u16 mField34;         // 0x34

    int Method1B0F08();   // 0x001B0F08
};

int UnkObj1B0F08::Method1B0F08()
{
    return (mField34 * 8) + 0x38;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

// Allocates n entries of 16 bytes after a 4-byte count (an array new), and stores n.
int *func_001B2948(int n)
{
    int *block = (int *)MemAlloc1BD958((n * 0x10) | 4);
    if (block != 0)
    {
        *block = n;
    }
    return block;
}

void func_001B3A20(Mat4x4f *m, Vec3f *v, Vec3f *out)
{
    out->x = v->x * m->row[0].x + v->y * m->row[0].y + v->z * m->row[0].z;
    out->y = v->x * m->row[1].x + v->y * m->row[1].y + v->z * m->row[1].z;
    out->z = v->x * m->row[2].x + v->y * m->row[2].y + v->z * m->row[2].z;
}
