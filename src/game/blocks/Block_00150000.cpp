#include "common/types.h"

// Functions of 0x00150000..0x00153FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8();       // 0x001974D8
void MemFree1BD978(void *); // 0x001BD978

void func_00151608(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_00151760()
{
}

void func_001519E0()
{
}

void func_001519E8()
{
}

void func_001519F0()
{
}

void func_001519F8()
{
}

void func_00151A00()
{
}

void func_00151A08()
{
}

void func_00151A10()
{
}

void func_00151C28()
{
}

void func_00151CB8()
{
    func_001974D8();
}

void func_0016F630(int); // 0x0016F630
void func_001F48A0(int); // 0x001F48A0

// UnkObj151900 (0x00151900..0x00151938): no RTTI; its layout is the fields these methods use.
struct UnkObj151900
{
    char field_0x0[0x6];
    s16 mField6;         // 0x6
    void *mField8;       // 0x8
    void *mFieldC;       // 0xC

    void Method151900(); // 0x00151900
    void Method151938(); // 0x00151938
};

void UnkObj151900::Method151900()
{
    MemFree1BD978(mFieldC);
    MemFree1BD978(mField8);
    MemFree1BD978(this);
}

void UnkObj151900::Method151938()
{
    mField6 = 0;
}

// UnkObj152498 (0x00152498): no RTTI; its layout is the fields these methods use.
struct UnkObj152498
{
    char field_0x0[0x68];
    int mField68;         // 0x68
    int mField6C;         // 0x6C

    void Method152498();  // 0x00152498
};

void UnkObj152498::Method152498()
{
    int tmp;

    tmp = mField6C;
    if (tmp != 0)
    {
        func_0016F630(tmp);
        func_001F48A0(mField68);
    }
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

f32 *MemAlloc1BD958(int); // 0x001BD958
extern f32 data_002B24F8;
extern f32 data_002B24FC;
extern int data_0025E720;
extern int data_0025E738;
// The object at data_0025E73C; only the fields read by func_001519B0..func_001519D0 are known.
struct UnkObj25E73C
{
    char pad00[0xCC];
    int mFieldCC; // 0xCC
    int mFieldD0; // 0xD0
    int padD4;
    int mFieldD8; // 0xD8
};
extern UnkObj25E73C *data_0025E73C;
extern int data_00261C4C;

void func_00150928(int arg0)
{
    data_0025E720 = arg0;
}

int func_00150938()
{
    return data_0025E720;
}

void func_001515B8(int arg0, f32 fparg0, f32 fparg1)
{
    data_0025E738 = arg0;
    data_002B24F8 = fparg0;
    data_002B24FC = fparg1;
}

void func_001515D8()
{
    f32 *temp_v0;

    temp_v0 = MemAlloc1BD958(4);
    if (temp_v0 != NULL)
    {
        *temp_v0 = 1.0f;
    }
}

f32 func_00151758(f32 *arg0)
{
    return *arg0;
}

int func_001519B0()
{
    return data_0025E73C->mFieldCC;
}

int func_001519C0()
{
    return data_0025E73C->mFieldD0;
}

int func_001519D0()
{
    return data_0025E73C->mFieldD8;
}

UnkObj25E73C *func_00151D10()
{
    return data_0025E73C;
}

void func_00151D20(int arg0)
{
    data_00261C4C = arg0;
}

int func_00151D30()
{
    return data_00261C4C;
}
