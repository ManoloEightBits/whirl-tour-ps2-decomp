#include "common/types.h"

// Functions of 0x0014C000..0x0014FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00126138(int);    // 0x00126138
void func_0014C4E8(int);    // 0x0014C4E8
void func_001974D8();       // 0x001974D8
int MemAlloc1BD958(int);     // 0x001BD958
void MemFree1BD978(void *); // 0x001BD978

void func_0014C198()
{
    func_001974D8();
}

void func_0014C200()
{
}

void func_0014C208(void *arg0)
{
    MemFree1BD978(arg0);
    func_00126138(0);
}

void func_0014C2B8()
{
    func_001974D8();
}

void func_0014C3B8()
{
}

void func_0014C4D8()
{
}

void func_0014C4E0()
{
}

int func_0014C908(int arg0)
{
    return arg0 + 4;
}

int func_0014C920()
{
    return 0xA;
}

int func_0014C9C0()
{
    int result;

    result = MemAlloc1BD958(0x98);
    if (result != 0)
    {
        func_0014C4E8(result);
    }
    return result;
}

void func_0014CAC8(void *arg0)
{
    MemFree1BD978(arg0);
}

int func_0014CAE8(int arg0)
{
    return arg0 + 0xC;
}

void func_0014E990(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_0014E9B0()
{
    func_001974D8();
}

void func_0014EC80()
{
    func_001974D8();
}

void func_0014C2B8();    // 0x0014C2B8
void func_0016F630(int); // 0x0016F630
void func_0018BFA0(int); // 0x0018BFA0
int func_0018C018(int);  // 0x0018C018
void func_001F48A0(int); // 0x001F48A0

// UnkObj14C1B8 (0x0014C1B8): no RTTI; its layout is the fields these methods use.
struct UnkObj14C1B8
{
    char field_0x0[0x94];
    int mField94;         // 0x94

    void Method14C1B8();  // 0x0014C1B8
};

void UnkObj14C1B8::Method14C1B8()
{
    int tmp;

    tmp = mField94;
    switch (tmp)                                /* irregular */
    {
    case 0x100:
        mField94 = 0xF000;
        return;
    case 0xF000:
        func_0014C2B8();
        break;
    }
}

// UnkObj14E748 (0x0014E748): no RTTI; its layout is the fields these methods use.
struct UnkObj14E748
{
    int mField0;                 // 0x0
    int mField4;                 // 0x4

    void Method14E748(int arg1); // 0x0014E748
};

void UnkObj14E748::Method14E748(int arg1)
{
    mField4 = 0;
    mField0 = (int) (1 << arg1);
}

// UnkObj14EF90 (0x0014EF90): no RTTI; its layout is the fields these methods use.
struct UnkObj14EF90
{
    char field_0x0[0x6C];
    int mField6C;         // 0x6C

    int Method14EF90();   // 0x0014EF90
};

int UnkObj14EF90::Method14EF90()
{
    int temp_a0;
    int var_v0;

    temp_a0 = mField6C;
    var_v0 = 0;
    if (temp_a0 != 0)
    {
        var_v0 = func_0018C018(temp_a0);
    }
    return var_v0;
}

// UnkObj14F3A8 (0x0014F3A8): no RTTI; its layout is the fields these methods use.
struct UnkObj14F3A8
{
    char field_0x0[0x6C];
    int mField6C;         // 0x6C

    void Method14F3A8();  // 0x0014F3A8
};

void UnkObj14F3A8::Method14F3A8()
{
    int tmp;

    tmp = mField6C;
    if (tmp != 0)
    {
        func_0018BFA0(tmp);
    }
}

// UnkObj14F5D8 (0x0014F5D8): no RTTI; its layout is the fields these methods use.
struct UnkObj14F5D8
{
    char field_0x0[0x18];
    int mField18;         // 0x18
    int mField1C;         // 0x1C

    void Method14F5D8();  // 0x0014F5D8
};

void UnkObj14F5D8::Method14F5D8()
{
    int tmp;

    tmp = mField1C;
    if (tmp != 0)
    {
        func_0016F630(tmp);
        func_001F48A0(mField18);
    }
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_0014C900(int *arg0)
{
    return *arg0;
}

int func_0014C910(int *arg0, int *arg1)
{
    return *arg1 - *arg0;
}
