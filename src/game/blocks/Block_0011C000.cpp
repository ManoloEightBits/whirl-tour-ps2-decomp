#include "common/types.h"

// Functions of 0x0011C000..0x0011FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// UnkObj11F568 (0x0011F568): no RTTI; its layout is the fields these methods use.
struct UnkObj11F568
{
    char field_0x0[0x20];
    int mField20;                // 0x20

    void Method11F568(int arg1); // 0x0011F568
};

void UnkObj11F568::Method11F568(int arg1)
{
    mField20 = (int) (arg1 - 1);
}
