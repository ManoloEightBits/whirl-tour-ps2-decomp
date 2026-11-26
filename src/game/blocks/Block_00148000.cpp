#include "common/types.h"

// Functions of 0x00148000..0x0014BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8(); // 0x001974D8

void func_00149258()
{
    func_001974D8();
}

struct UnkBody
{
    int GetPtr50(); // 0x0014CB40
};

extern "C" void func_00150FD0(int, void *, void *, int); // 0x00150FD0
extern "C" void func_00146CA8();                         // 0x00146CA8
struct UnkNode;
void func_00193100(UnkNode *);                           // 0x00193100

struct UnkObj148F58
{
    char pad00[0x08];
    UnkBody *mField08; // 0x08
    char pad0C[0x1C];
    void *mField28;    // 0x28
    void *mField2C;    // 0x2C
    void *mField30;    // 0x30
};

void func_00148F58(UnkObj148F58 *arg0)
{
    func_00150FD0(0x8000, (void *)func_00146CA8, arg0, arg0->mField08->GetPtr50());
    func_00150FD0(1, (void *)func_00193100, arg0->mField28, arg0->mField08->GetPtr50());
    func_00150FD0(1, (void *)func_00193100, arg0->mField2C, arg0->mField08->GetPtr50());
    func_00150FD0(1, (void *)func_00193100, arg0->mField30, arg0->mField08->GetPtr50());
}
