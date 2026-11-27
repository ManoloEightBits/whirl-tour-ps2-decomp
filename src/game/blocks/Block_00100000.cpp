#include "common/types.h"

// Functions of 0x00100000..0x00103FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00101250();       // 0x00101250
void func_001017A8(void *); // 0x001017A8
void func_001A4DA8();       // 0x001A4DA8
void MemFree1BD978(void *); // 0x001BD978

void func_00100B20()
{
    func_001A4DA8();
}

void func_00100B70()
{
}

void func_00101768()
{
    func_00101250();
}

void func_00101788(void *arg0)
{
    func_001017A8(arg0);
}

void func_001033C0(void *arg0)
{
    MemFree1BD978(arg0);
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_00103068(int, int); // 0x00103068
void func_00103198(int);      // 0x00103198
extern int data_00259540;

void func_00103040(int arg0)
{
    func_00103068(data_00259540, arg0);
}

void func_00103170()
{
    if (data_00259540 != 0)
    {
        func_00103198(data_00259540);
    }
}

struct UnkNode;
void func_00193100(UnkNode *); // 0x00193100

struct UnkSub1017A8
{
    char pad00[0x2];
    u8 mCount02; // 0x02
};

struct UnkObj1017A8
{
    char pad00[0x60];
    UnkSub1017A8 *mSub60; // 0x60
    char pad64[0x8];
    UnkNode **mNodes6C;   // 0x6C
};

void func_001017A8(void *arg0)
{
    UnkObj1017A8 *obj = (UnkObj1017A8 *)arg0;
    u32 i = 0;
    if (obj->mSub60->mCount02 != 0)
    {
        do
        {
            func_00193100(obj->mNodes6C[i]);
            i = (i + 1) & 0xFF;
        } while (i < obj->mSub60->mCount02);
    }
}

struct UnkArray1BB0D0
{
    int GetCount(); // 0x001BB0D0
};

void *ArrayGetElement1BB098(void *list, int i); // 0x001BB098
void func_0015DB90(void *);                      // 0x0015DB90

struct UnkObj102EE8
{
    char pad00[0x4];
    UnkArray1BB0D0 *mArr04; // 0x04
};

struct UnkElem102EE8
{
    char pad00[0x1E];
    u8 mField1E; // 0x1E
};

void func_00102EE8(void *arg0, int arg1)
{
    UnkObj102EE8 *obj = (UnkObj102EE8 *)arg0;
    int idx = (arg1 - 1) & 0xFF;
    if (idx < obj->mArr04->GetCount())
    {
        UnkElem102EE8 *elem = *(UnkElem102EE8 **)ArrayGetElement1BB098(obj->mArr04, idx);
        if (elem->mField1E == 1)
        {
            func_0015DB90(elem);
        }
    }
}
