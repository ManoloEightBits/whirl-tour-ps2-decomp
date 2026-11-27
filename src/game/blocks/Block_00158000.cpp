#include "common/types.h"

// Functions of 0x00158000..0x0015BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

f32 func_00158F70()
{
    return 0.0f;
}

void func_00158F80()
{
}

void func_00158F88()
{
}

// UnkObj158860 (0x00158860..0x00158888): no RTTI; its layout is the fields these methods use.
struct UnkObj158860
{
    char field_0x0[0x3C];
    int mField3C;                // 0x3C
    int mField40;                // 0x40
    int mField44;                // 0x44

    int Method158860();          // 0x00158860
    void Method158870(int arg1); // 0x00158870
    void Method158888();         // 0x00158888
};

int UnkObj158860::Method158860()
{
    return mField40 == 0;
}

void UnkObj158860::Method158870(int arg1)
{
    mField40 = arg1;
    mField44 = 1;
    mField3C = 0;
}

void UnkObj158860::Method158888()
{
    mField3C += 1;
}

struct UnkDialog1588D0
{
    char pad00[0x8];
    int mField08;
};

struct UnkObj1588D0
{
    char pad00[0x8];
    UnkDialog1588D0 *mDialog08;
};

UnkDialog1588D0 *CreateDialog130960(int, int, int, void *, int); // 0x00130960
void CleanupDialog1309E0(void *); // 0x001309E0

void func_001588D0(UnkObj1588D0 *arg0, int arg1, int arg2, int arg3, void *arg4, int arg5, int arg6)
{
    if (arg0->mDialog08 != 0)
    {
        CleanupDialog1309E0(arg0->mDialog08);
        arg0->mDialog08 = 0;
    }
    UnkDialog1588D0 *d = CreateDialog130960(arg1, arg2, arg3, arg4, arg5);
    arg0->mDialog08 = d;
    if (d != 0)
        d->mField08 = arg6;
}

void func_00158898(UnkObj1588D0 *arg0)
{
    if (arg0->mDialog08 != 0)
    {
        CleanupDialog1309E0(arg0->mDialog08);
        arg0->mDialog08 = 0;
    }
}

void func_0018BA58();              // 0x0018BA58
void Release198F38(void *);        // 0x00198F38
extern "C" void __builtin_delete(void *);

struct UnkObj158678
{
    void *mField00; // 0x00
    int mField04;   // 0x04
};

void func_00158678(void *arg0, int arg1)
{
    UnkObj158678 *obj = (UnkObj158678 *)arg0;
    func_00158898((UnkObj1588D0 *)obj);
    ((void (*)(int))func_0018BA58)(obj->mField04);
    Release198F38(obj->mField00);
    if (arg1 & 1)
        __builtin_delete(obj);
}
