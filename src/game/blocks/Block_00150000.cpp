#include "common/types.h"

// Functions of 0x00150000..0x00153FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_001974D8();       // 0x001974D8
void func_001BD978(void *); // 0x001BD978

void func_00151608(void *arg0)
{
    func_001BD978(arg0);
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
    func_001BD978(mFieldC);
    func_001BD978(mField8);
    func_001BD978(this);
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
