#include "common/types.h"

// Functions of 0x00128000..0x0012BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00154C58();         // 0x00154C58
void func_002318F8(int, int); // 0x002318F8
int func_00231A0C(int);       // 0x00231A0C

void func_001285A8()
{
}

void func_00128CC0(int arg0, int arg1)
{
    func_002318F8(arg0 + 0x24, arg1);
}

void func_00128D38(int arg0, int arg1)
{
    func_002318F8(arg0 + 0xA4, arg1);
}

void func_00128ED8(int arg0, int arg1, int arg2)
{
    if (func_00231A0C(arg2) != 0)
    {
        func_002318F8((arg1 * 0x58) + arg0 + 0xD94, arg2);
    }
}

void func_00129138()
{
}

void func_00129CB8()
{
    func_00154C58();
}

void func_001BCAC0(int); // 0x001BCAC0

// UnkObj128E48 (0x00128E48..0x00128E50): no RTTI; its layout is the fields these methods use.
struct UnkObj128E48
{
    char field_0x0[0xD50];
    int mFieldD50;                 // 0xD50
    char field_0xD54[0xB78];
    f32 mField18CC;                // 0x18CC

    void SetField18CC(f32 fparg0); // 0x00128E48
    void SetFieldD50(int v);    // 0x00128E50
};

void UnkObj128E48::SetField18CC(f32 fparg0)
{
    mField18CC = fparg0;
}

void UnkObj128E48::SetFieldD50(int v)
{
    mFieldD50 = v;
}

// UnkObj129098 (0x00129098..0x001290B0): no RTTI; its layout is the fields these methods use.
struct UnkObj129098
{
    char field_0x0[0x187C];
    f32 mField187C;                // 0x187C
    int mField1880;                // 0x1880

    void SetField1880(int v);   // 0x00129098
    void SetField187C(f32 fparg0); // 0x001290B0
};

void UnkObj129098::SetField1880(int v)
{
    mField1880 = v;
}

void UnkObj129098::SetField187C(f32 fparg0)
{
    mField187C = fparg0;
}

// UnkObj129CD8 (0x00129CD8): no RTTI; its layout is the fields these methods use.
struct UnkObj129CD8
{
    char field_0x0[0x18];
    int mField18;         // 0x18

    void Method129CD8();  // 0x00129CD8
};

void UnkObj129CD8::Method129CD8()
{
    func_001BCAC0(mField18);
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_00198210(int);  // 0x00198210
extern int data_0025DE20;

void func_00129D40()
{
    func_00198210(data_0025DE20);
    data_0025DE20 = 0;
}
