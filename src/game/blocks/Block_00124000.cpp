#include "common/types.h"

struct PickupDef;

// Functions of 0x00124000..0x00127FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// UnkObj1272A0 (0x001272A0..0x00127328): no RTTI; its layout is the fields these methods use.
struct UnkObj1272A0
{
    char field_0x0[0x28];
    int mField28;                  // 0x28
    f32 mField2C;                  // 0x2C
    char field_0x30[0xC];
    f32 mField3C;                  // 0x3C

    void Method1272A0(int arg1);   // 0x001272A0
    void Method1272B0(int arg1);   // 0x001272B0
    void SetField2C(f32 fparg0);   // 0x00127320
    void Method127328(f32 fparg0); // 0x00127328
};

void UnkObj1272A0::Method1272A0(int arg1)
{
    mField28 |= arg1;
}

void UnkObj1272A0::Method1272B0(int arg1)
{
    mField28 &= ~arg1;
}

void UnkObj1272A0::SetField2C(f32 fparg0)
{
    mField2C = fparg0;
}

void UnkObj1272A0::Method127328(f32 fparg0)
{
    f32 tmp;

    tmp = fparg0;
    if (tmp < 0.05f)
    {
        tmp = 0.05f;
    }
    mField3C = tmp;
}

// UnkObj127458 (0x00127458): no RTTI; its layout is the fields these methods use.
struct UnkObj127458
{
    char field_0x0[0x6F];
    s8 mField6F;              // 0x6F

    void SetField6F(s8 v); // 0x00127458
};

void UnkObj127458::SetField6F(s8 v)
{
    mField6F = v;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

int func_0012D120();                         // 0x0012D120
void func_0012D248(int, int, int, int, int); // 0x0012D248
int func_00182CF0(int, int, int);            // 0x00182CF0
void func_00182D98(int, int, int, int);      // 0x00182D98
int func_00182E20(int, int, int);            // 0x00182E20
int func_00182E98(int, int, int, int, int);  // 0x00182E98
void func_001832A8(int, int);                // 0x001832A8
int func_00183580(int);                      // 0x00183580
extern int data_0025DC60;
extern int data_0025DC64;

int func_001260A0()
{
    int var_v1;

    var_v1 = 0;
    if (data_0025DC60 != 0)
    {
        var_v1 = func_00183580(data_0025DC60);
    }
    return var_v1;
}

void func_00126138(int arg0)
{
    if (data_0025DC60 != 0)
    {
        func_001832A8(data_0025DC60, arg0);
    }
}

int func_00126168(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182CF0(data_0025DC60, arg0, 0x2710);
    }
    return var_v0;
}

void func_00126198(int arg0, int arg1, int arg2)
{
    if (data_0025DC60 != 0)
    {
        func_00182D98(data_0025DC60, arg0, arg1, arg2);
    }
}

int func_001261D0(int arg0, int arg1)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, arg0, arg1);
    }
    return var_v0;
}

int func_00126250(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xD, arg0);
    }
    return var_v0;
}

int func_00126280(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0, arg0);
    }
    return var_v0;
}

int func_001262B0(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 5, arg0);
    }
    return var_v0;
}

int func_001262E0(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 3, arg0);
    }
    return var_v0;
}

int func_00126310(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xA, arg0);
    }
    return var_v0;
}

int func_00126340(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0x10, arg0);
    }
    return var_v0;
}

int func_00126370(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xC, arg0);
    }
    return var_v0;
}

int func_001263A0(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xB, arg0);
    }
    return var_v0;
}

int func_001263D0(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 8, arg0);
    }
    return var_v0;
}

int func_00126400(int arg0)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E20(data_0025DC60, 0xF, arg0);
    }
    return var_v0;
}

int func_00126430(int arg0, int arg1, int arg2)
{
    int var_v0;

    var_v0 = 0;
    if (data_0025DC60 != 0)
    {
        var_v0 = func_00182E98(data_0025DC60, 8, arg0, arg1, arg2);
    }
    return var_v0;
}

void func_00126620(int arg0, int arg1, int arg2, int arg3)
{
    if (data_0025DC64 == 0)
    {
        data_0025DC64 = func_0012D120();
    }
    func_0012D248(data_0025DC64, arg0, arg1, arg2, arg3);
}

void func_0012D278(int, int);             // 0x0012D278

void func_001266A0(int arg0)
{
    if (data_0025DC64 != 0)
    {
        func_0012D278(data_0025DC64, arg0);
    }
}

void func_0012CEA8(int, void *, int);              // 0x0012CEA8
void func_0012D2F0(int, u32, int, void *);         // 0x0012D2F0
void func_0012D398(int);                  // 0x0012D398
void func_00182F88(int, int);             // 0x00182F88
PickupDef *func_00182FD0(int, const char *);       // 0x00182FD0
void func_001830A0(int, int);             // 0x001830A0
void func_001830F0(int, int, int);        // 0x001830F0
void func_001831F8(int, int, int, const char *);   // 0x001831F8

void func_00126470(int arg0, int arg1)
{
    if (data_0025DC60 != 0)
    {
        func_001831F8(data_0025DC60, arg0, arg1, "db_fontset");
    }
}

void func_001264F0(int arg0)
{
    func_00182F88(data_0025DC60, arg0);
}

// Looks a pickup type's definition up by name in the definition database (data_0025DC60).
PickupDef *FindPickupDef(const char *name)
{
    return func_00182FD0(data_0025DC60, name);
}

void func_00126578(int arg0)
{
    func_001830A0(data_0025DC60, arg0);
}

void func_001265A0(int arg0, int arg1)
{
    func_001830F0(data_0025DC60, arg0, arg1);
}

void SendScriptEvent(u32 eventCrc, int arg1, void *arg2)
{
    if (data_0025DC64 != 0)
    {
        func_0012D2F0(data_0025DC64, eventCrc, arg1, arg2);
    }
}

void func_00126708(void *arg0, int arg1)
{
    if (data_0025DC64 != 0)
    {
        func_0012CEA8(data_0025DC64, arg0, arg1);
    }
}

void func_00126738()
{
    if (data_0025DC64 != 0)
    {
        func_0012D398(data_0025DC64);
    }
}

extern int data_0025DC68;

void *func_00127038()
{
    return &data_0025DC68;
}

struct UnkObj127048
{
    int mField0; // 0x00
    int mField4; // 0x04

    void SetFields4_0(int a, int b); // 0x00127048
};

void UnkObj127048::SetFields4_0(int a, int b)
{
    mField0 = b;
    mField4 = a;
}

struct UnkObj12D0F0
{
    void Method12D0F0(); // 0x0012D0F0
    void Method12D178(); // 0x0012D178
};

void func_001265D0()
{
    if (data_0025DC64 != 0)
    {
        ((UnkObj12D0F0 *)data_0025DC64)->Method12D0F0();
        if (data_0025DC64 != 0)
        {
            ((UnkObj12D0F0 *)data_0025DC64)->Method12D178();
            data_0025DC64 = 0;
        }
    }
}

extern int data_0025DC60;
u32 HashStringCRC32(const char *); // 0x001B1CD0
int func_00182F38(int, u32);       // 0x00182F38

int FindFont1264A8(const char *name)
{
    int ret = 0;
    if (data_0025DC60 != 0)
        ret = func_00182F38(data_0025DC60, HashStringCRC32(name));
    return ret;
}

struct UnkObj183480
{
    int GetField8(); // 0x00183578
};

int func_00126068()
{
    int ret = 0;
    if (data_0025DC60 != 0)
        ret = ((UnkObj183480 *)data_0025DC60)->GetField8();
    return ret;
}

// Synthesized from m2c (0x00127310)
struct UnkObj127310
{
    char pad00[0x30];
    f32 mField30; // 0x30
    f32 mField34; // 0x34
    void Method127310(f32 fparg0, f32 fparg1);
};

void UnkObj127310::Method127310(f32 fparg0, f32 fparg1)
{
    this->mField30 = fparg0;
    this->mField34 = fparg1;
}

