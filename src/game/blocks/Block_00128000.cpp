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

int func_00198090(int);                // 0x00198090
void func_001983F0(int, void *, int);  // 0x001983F0
extern "C" void func_00129658();       // 0x00129658

void func_00129CF8(int arg0)
{
    int p = func_00198090(0);
    data_0025DE20 = p;
    func_001983F0(p, (void *)func_00129658, arg0);
}

int HashStringCRC32(const char *); // 0x001B1CD0

struct UnkEntry128F38
{
    char field_0x0[0x50];
    int mField50; // +0xDB4 from base 0xD64
    u16 mField54;
    u16 mField56; // +0xDBA from base 0xD64
};

struct UnkObj128F38
{
    char field_0x0[0xD64];
    UnkEntry128F38 mEntries[1]; // 0xD64

    void SetFieldDB4(int idx, int val); // 0x00128F38
    void SetFieldDBA(int idx, u16 val); // 0x00129058
};

void UnkObj128F38::SetFieldDB4(int idx, int val)
{
    mEntries[idx].mField50 = val;
}

void UnkObj128F38::SetFieldDBA(int idx, u16 val)
{
    mEntries[idx].mField56 = val;
}

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

struct UnkObj1290B8
{
    char pad00[0x1884];
    f32 mField1884; // 0x1884
    f32 mField1888; // 0x1888
    u32 mField188C; // 0x188C
};

void func_001290B8(UnkObj1290B8 *arg0, const char *arg1, f32 arg2, f32 arg3)
{
    u32 crc = HashStringCRC32(arg1);
    arg0->mField1888 = arg3;
    arg0->mField1884 = arg2;
    arg0->mField188C = crc;
}

struct UnkObj129108
{
    char pad00[0x18D0];
    int mField18D0; // 0x18D0
    int mField18D4; // 0x18D4
    int mField18D8; // 0x18D8
    int mField18DC; // 0x18DC
    int mField18E0; // 0x18E0
};

void func_00129108(UnkObj129108 *arg0, int *arg1)
{
    arg0->mField18D0 = arg1[0];
    arg0->mField18E0 = arg1[1];
    arg0->mField18D4 = arg1[2];
    arg0->mField18DC = arg1[3];
    arg0->mField18D8 = arg1[4];
}

// Synthesized from m2c (0x00128DE8)
struct UnkObj128DE8
{
    char pad00[0x18A8];
    int mField18A8; // 0x18A8
    int mArr18AC[1]; // 0x18AC
    void Method128DE8(int arg1);
};

void UnkObj128DE8::Method128DE8(int arg1)
{
    int temp_v1;

    temp_v1 = this->mField18A8;
    this->mArr18AC[temp_v1] = arg1;
    this->mField18A8 = (int) (temp_v1 + 1);
}

int HashStringCRC32(const char *);        // 0x001B1CD0
int *func_001BEE68(int, int, int);        // 0x001BEE68

struct UnkGlobal128780
{
    char pad00[0x14];
    int mField14; // 0x14
};

extern UnkGlobal128780 *data_0025DD40;

int func_00128780(const char *arg0)
{
    UnkGlobal128780 *g = data_0025DD40;
    int ret = 0;
    if (g != 0)
    {
        int *p = func_001BEE68(g->mField14, HashStringCRC32(arg0), 0);
        if (p != 0)
            ret = *p;
    }
    return ret;
}

void func_001BCAC0(int); // 0x001BCAC0

struct UnkGlobal1286C8
{
    char pad00[0x18];
    int mField18; // 0x18
};

void func_001286C8()
{
    if (data_0025DD40 != 0)
    {
        func_001BCAC0(((UnkGlobal1286C8 *)data_0025DD40)->mField18);
        data_0025DD40 = 0;
    }
}

void func_001BB250(int, int *); // 0x001BB250

struct UnkGlobal128700
{
    char pad00[0x10];
    int mField10; // 0x10
};

void func_00128700(int *arg0)
{
    if (data_0025DD40 != 0)
    {
        func_001BB250(((UnkGlobal128700 *)data_0025DD40)->mField10, arg0);
    }
}

void func_00129070(int arg0, int arg1, f32 deg)
{
    *(f32 *)((arg1 * 0x58) + arg0 + 0xDC8) = deg * 0.017453294f;
}

void func_00128F50(int arg0, int arg1, int arg2)
{
    u8 *p = (u8 *)((arg1 * 0x58) + arg0);
    *(u16 *)(p + 0xDB8) = *(u16 *)(p + 0xDB8) | (arg2 & 0xFF);
}

