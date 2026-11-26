#include "common/types.h"
#include "common/libc.h"

// Functions of 0x00110000..0x00113FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_0010EF48(); // 0x0010EF48

void func_00110000()
{
    func_0010EF48();
}

void func_00112150()
{
}

void func_00112158()
{
}

void func_0010F550(int); // 0x0010F550

// UnkObj110020 (0x00110020): no RTTI; its layout is the fields these methods use.
struct UnkObj110020
{
    char field_0x0[0xA8];
    int mFieldA8;         // 0xA8

    void Method110020();  // 0x00110020
};

void UnkObj110020::Method110020()
{
    func_0010F550(mFieldA8);
}

// UnkObj111EB8 (0x00111EB8..0x00111ED0): no RTTI; its layout is the fields these methods use.
struct UnkObj111EB8
{
    char field_0x0[0x68];
    int mField68;         // 0x68

    void Method111EB8();  // 0x00111EB8
    void Method111EC8();  // 0x00111EC8
    int GetField68();     // 0x00111ED0
};

void UnkObj111EB8::Method111EB8()
{
    mField68 = 1;
}

void UnkObj111EB8::Method111EC8()
{
    mField68 = 0;
}

int UnkObj111EB8::GetField68()
{
    return mField68;
}

void func_00136C20(int, f32); // 0x00136C20

struct UnkObj112140
{
    char field_0x0[0x8];
    void *mField08;  // 0x08
    char field_0xC[0x10];
    f32 mField1C;    // 0x1C

    void Method112140(); // 0x00112140
};

void func_00112120(UnkObj112140 *arg0, int arg1)
{
    func_00136C20(arg1, arg0->mField1C);
}

void UnkObj112140::Method112140()
{
    mField08 = (void *)func_00112120;
}

void func_001BCAC0(int); // 0x001BCAC0

struct UnkObj1121A0
{
    char field_0x0[0x70];
    int mField70; // 0x70
};

void func_001121A0(UnkObj1121A0 *arg0)
{
    if (arg0->mField70 != 0)
        func_001BCAC0(arg0->mField70);
}

struct FEScreenDef
{
    char mName[0x460];
};

struct FEScreenTable
{
    int mField00;          // 0x00
    int mField04;          // 0x04
    int mField08;          // 0x08
    char field_0x0C[0x118];
    int mCount124;         // 0x124
    FEScreenDef mDefs128[1]; // 0x128
};

void func_001139C0(FEScreenTable *table)
{
    table->mField00 = 0;
    table->mField04 = 0;
    table->mCount124 = 0;
    table->mField08 = 0;
}

void *FindScreenDef113B48(void *arg0, const char *name)
{
    FEScreenTable *table = (FEScreenTable *)arg0;
    void *found = 0;
    for (int i = 0; i < table->mCount124; i++)
    {
        if (strcmp(table->mDefs128[i].mName, name) == 0)
        {
            found = &table->mDefs128[i];
            break;
        }
    }
    return found;
}
