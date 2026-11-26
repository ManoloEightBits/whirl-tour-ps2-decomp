#include "common/types.h"
#include "game/FEScreen.h"
#include "game/GameCtx.h"

// Functions of 0x00130000..0x00133FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void MemFree1BD978(void *); // 0x001BD978

void CleanupDialog1309E0(void *arg0)
{
    MemFree1BD978(arg0);
}

// UnkObj130608 (0x00130608): no RTTI; its layout is the fields these methods use.
struct UnkObj130608
{
    char field_0x0[0x4];
    int mField4;          // 0x4
    char field_0x8[0x80];
    int mField88;         // 0x88

    int Method130608();   // 0x00130608
};

int UnkObj130608::Method130608()
{
    int var_a1;
    int var_v1;

    var_v1 = mField4;
    var_a1 = 1;
    if (var_v1 > 0)
    {
        do
        {
            var_v1 -= 1;
            var_a1 = ((mField88 ^ 1) & 1) ? 0 : var_a1;
        } while (var_v1 != 0);
    }
    return var_a1;
}

// UnkObj130750 (0x00130750): no RTTI; its layout is the fields these methods use.
struct UnkObj130750
{
    char field_0x0[0x88];
    int mField88;         // 0x88

    int Method130750();   // 0x00130750
};

int UnkObj130750::Method130750()
{
    return mField88 & 1;
}

// UnkObj130AC0 (0x00130AC0..0x00130AC8): no RTTI; its layout is the fields these methods use.
struct UnkObj130AC0
{
    char field_0x0[0x18];
    int mField18;              // 0x18
    int mField1C;              // 0x1C

    void SetField18(int v); // 0x00130AC0
    void SetField1C(int v); // 0x00130AC8
};

void UnkObj130AC0::SetField18(int v)
{
    mField18 = v;
}

void UnkObj130AC0::SetField1C(int v)
{
    mField1C = v;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

extern int data_0025E1A0;
extern int data_0025E1A4;

void func_00130008()
{
    data_0025E1A4 = 0;
}

void func_00130018()
{
    data_0025E1A4 = 0;
    data_0025E1A0 = 0;
}

FESub08::~FESub08()
{
}

struct UnkObj131320
{
    char pad00[0x28];
    int mField28;         // 0x28
    void *mField2C;       // 0x2C
    char pad30[0x0C];
    char mField3C[0x40];  // 0x3C
    f32 mField7C;         // 0x7C
    char pad80[0x4A4];
    char mBuf524[0x100];  // 0x524
    char mBuf624[0x100];  // 0x624
    char mBuf724[0x100];  // 0x724
};

void *func_00143100(const char *, int); // 0x00143100
void func_00143170(void *, int);        // 0x00143170
void func_001432A0(void *, f32);        // 0x001432A0
const char *func_00153360();            // 0x00153360
char *GetCurrentTrackName155AD8();      // 0x00155AD8
extern "C" void func_00231F08(char *, const char *, int); // 0x00231F08

void func_00131320(UnkObj131320 *arg0, int arg1)
{
    if (gGameCtx262250->mInGameMusic != 0)
    {
        if (arg0->mField2C != 0)
        {
            func_00143170(arg0->mField2C, 4);
            arg0->mField2C = 0;
        }
        const char *track = (arg1 != 0) ? func_00153360() : GetCurrentTrackName155AD8();
        if (track != 0)
        {
            void *snd = func_00143100(track + 0x60, 4);
            arg0->mField2C = snd;
            if (snd != 0)
                func_001432A0(snd, gGameCtx262250->mMusicVolume);
            arg0->mField7C = 2.0f;
            func_00231F08(arg0->mBuf524, track, 0x100);
            func_00231F08(arg0->mBuf624, track + 0x20, 0x100);
            func_00231F08(arg0->mBuf724, track + 0x40, 0x100);
        }
        else
        {
            gGameCtx262250->mInGameMusic = 0;
        }
    }
    else
    {
        if (arg0->mField28 != 0 && arg0->mField3C[0] != 0)
        {
            if (arg0->mField2C != 0)
            {
                func_00143170(arg0->mField2C, 4);
                arg0->mField2C = 0;
            }
            void *snd = func_00143100(arg0->mField3C, 4);
            arg0->mField2C = snd;
            if (snd != 0)
                func_001432A0(snd, gGameCtx262250->mMusicVolume);
        }
        else if (arg0->mField2C != 0)
        {
            func_00143170(arg0->mField2C, 4);
            arg0->mField2C = 0;
        }
    }
}
