#include "common/types.h"
#include "common/libc.h"

// Functions of 0x00128000..0x0012BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void DestroyGameCtx154C58(); // 0x00154C58

void func_001285A8()
{
}

void func_00128CC0(char *arg0, const char *arg1)
{
    strcpy(arg0 + 0x24, arg1);
}

void func_00128D38(char *arg0, const char *arg1)
{
    strcpy(arg0 + 0xA4, arg1);
}

void func_00128ED8(char *arg0, int arg1, const char *arg2)
{
    if (strlen(arg2) != 0)
    {
        strcpy((arg1 * 0x58) + arg0 + 0xD94, arg2);
    }
}

void func_00129138()
{
}

void func_00129CB8()
{
    DestroyGameCtx154C58();
}

void func_001BCAC0(int); // 0x001BCAC0

// UnkObj128E48 (0x00128E08..0x00128E58): no RTTI; its layout is the fields these methods use.
struct UnkObj128E48
{
    char field_0x0[0xD50];
    int mFieldD50;                 // 0xD50
    char field_0xD54[0xB3C];
    f32 mField1890;                // 0x1890
    f32 mField1894;                // 0x1894
    f32 mField1898;                // 0x1898
    f32 mField189C;                // 0x189C
    f32 mField18A0;                // 0x18A0
    f32 mField18A4;                // 0x18A4
    char field_0x18A8[0xC];
    int mField18B4;                // 0x18B4
    f32 mField18B8;                // 0x18B8
    f32 mField18BC;                // 0x18BC
    f32 mField18C0;                // 0x18C0
    f32 mField18C4;                // 0x18C4
    f32 mField18C8;                // 0x18C8
    f32 mField18CC;                // 0x18CC

    void SetFields1890(f32 fparg0, f32 fparg1, f32 fparg2); // 0x00128E08
    void SetFields189C(f32 fparg0, f32 fparg1, f32 fparg2); // 0x00128E18
    void SetFields18B4(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4); // 0x00128E28
    void SetField18CC(f32 fparg0); // 0x00128E48
    void SetFieldD50(int v);    // 0x00128E50
};

void UnkObj128E48::SetFields1890(f32 fparg0, f32 fparg1, f32 fparg2)
{
    mField1890 = fparg0;
    mField1894 = fparg1;
    mField1898 = fparg2;
}

void UnkObj128E48::SetFields189C(f32 fparg0, f32 fparg1, f32 fparg2)
{
    mField189C = fparg0;
    mField18A0 = fparg1;
    mField18A4 = fparg2;
}

void UnkObj128E48::SetFields18B4(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4)
{
    mField18B4 = 1;
    mField18B8 = fparg0;
    mField18BC = fparg1;
    mField18C0 = fparg2;
    mField18C4 = fparg3;
    mField18C8 = fparg4;
}

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
    char field_0x0[0x1874];
    f32 mField1874;                // 0x1874
    f32 mField1878;                // 0x1878
    f32 mField187C;                // 0x187C
    int mField1880;                // 0x1880

    void SetField1880(int v);   // 0x00129098
    void SetFields1874(f32 fparg0, f32 fparg1); // 0x001290A0
    void SetField187C(f32 fparg0); // 0x001290B0
};

void UnkObj129098::SetField1880(int v)
{
    mField1880 = v;
}

void UnkObj129098::SetFields1874(f32 fparg0, f32 fparg1)
{
    mField1874 = fparg0;
    mField1878 = fparg1;
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

int HashStringCRC32(const char *); // 0x001B1CD0

struct UnkNamed128C80
{
    u32 mCrc00;          // 0x00: CRC32 of mName04
    char mName04[0x20];  // 0x04: length unknown
};

// Sets an object's name and its CRC32.
void func_00128C80(UnkNamed128C80 *obj, const char *name)
{
    strcpy(obj->mName04, name);
    obj->mCrc00 = HashStringCRC32(name);
}
