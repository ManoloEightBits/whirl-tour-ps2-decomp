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

struct UnkSub1491D8
{
    char pad00[0x1C];
    int mField1C; // 0x1C
};

struct UnkObj1491D8
{
    char pad00[0x98];
    UnkSub1491D8 *mField98; // 0x98
    void *mField9C;         // 0x9C
    char padA0[0x04];
    void *mFieldA4;         // 0xA4
    char padA8[0x08];
    int mFieldB0;           // 0xB0
    char padB4[0x10];
    int mFieldC4;           // 0xC4
    int mFieldC8;           // 0xC8
    int mFieldCC;           // 0xCC
    char padD0[0x08];
    void *mFieldD8;         // 0xD8
    int *mFieldDC;          // 0xDC
};

void func_001982D0(int, int); // 0x001982D0
void Release198F38(void *);  // 0x00198F38
void func_00191E40(void *);  // 0x00191E40
void ArrayDestroy1BB168(int); // 0x001BB168
void CleanupDialog1309E0(void *); // 0x001309E0
void MemFree1BD978(void *);  // 0x001BD978
void func_00126138(int);     // 0x00126138

void func_001491D8(UnkObj1491D8 *arg0)
{
    func_001982D0(arg0->mField98->mField1C, 0);
    Release198F38(arg0->mFieldA4);
    func_00191E40(arg0->mField9C);
    ArrayDestroy1BB168(arg0->mFieldCC);
    ArrayDestroy1BB168(arg0->mFieldC4);
    ArrayDestroy1BB168(arg0->mFieldC8);
    CleanupDialog1309E0(arg0->mFieldD8);
    *arg0->mFieldDC = arg0->mFieldB0;
    MemFree1BD978(arg0);
    func_00126138(0);
}

extern "C" void func_00149478(); // 0x00149478

void func_0014BCC0(UnkObj148F58 *arg0)
{
    func_00150FD0(0x8000, (void *)func_00149478, arg0, arg0->mField08->GetPtr50());
}
