#include "common/types.h"

// Functions of 0x0015C000..0x0015FFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_0015F318();       // 0x0015F318
void func_0015F3C8(void *); // 0x0015F3C8
void func_0015F458();       // 0x0015F458

void func_0015E958()
{
}

void func_0015E960()
{
}

void func_0015F2F8()
{
    func_0015F318();
}

void func_0015F3A8(void *arg0)
{
    func_0015F3C8(arg0);
}

void func_0015F438()
{
    func_0015F458();
}

int func_0015F578()
{
    return 0;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

extern "C" void glPushMatrix();               // 0x001A3738
extern "C" void glPopMatrix();                // 0x001A3808
extern "C" void glMultMatrixf(const f32 *);   // 0x001A3AB0
f32 func_00151758(f32 *);                     // 0x00151758
void func_00151760();                         // 0x00151760
void func_00151768();                         // 0x00151768
void func_001517C0(f32);                      // 0x001517C0
void func_00119560(void *, int, int);        // 0x00119560

struct UnkObj15F3C8
{
    char pad00[0x18];
    u8 mField18;      // 0x18
    char pad19[0x97];
    f32 mMatB0[16];   // 0xB0
    f32 mMatF0[16];   // 0xF0
    char pad130[0x2C];
    void *mField15C;  // 0x15C
    char pad160[0xB0];
    f32 *mPtr210;     // 0x210
};

void func_0015F3C8(void *arg0)
{
    UnkObj15F3C8 *obj = (UnkObj15F3C8 *)arg0;
    glPushMatrix();
    glMultMatrixf(obj->mMatB0);
    glMultMatrixf(obj->mMatF0);
    func_00151760();
    func_001517C0(func_00151758(obj->mPtr210));
    func_00119560(obj->mField15C, obj->mField18, 1);
    func_00151768();
    glPopMatrix();
}

int func_0012E848(int);            // 0x0012E848
int func_001263D0(int);            // 0x001263D0
void func_001BB250(int, int *);    // 0x001BB250

struct UnkObj15F580
{
    int mField00; // 0x00
    int mField04; // 0x04
    int mField08; // 0x08
};

int func_0015F580(UnkObj15F580 *arg0, int unused1, int unused2, int arg3)
{
    if (arg0->mField04 == 3 && func_0012E848(arg0->mField08) == 0xA)
    {
        int sp0 = func_001263D0(arg0->mField00);
        if (sp0 != 0)
            func_001BB250(arg3, &sp0);
    }
    return 1;
}


