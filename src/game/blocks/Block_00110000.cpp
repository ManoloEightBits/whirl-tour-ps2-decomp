#include "common/types.h"

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
