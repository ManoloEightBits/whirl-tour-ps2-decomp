#include "common/types.h"

// Functions of 0x001F4000..0x001F7FFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

// Converted from m2c sweep drafts (tools/analysis/draft_to_cpp.py): strings and float constants
// are literals, variables are data_<addr> in config/symbols.txt.

int func_001F73F8(int *arg0)
{
    return *arg0;
}

extern "C" void func_001F7B18(void *, void *); // 0x001F7B18
extern "C" void func_001D9AD8(void *);         // 0x001D9AD8
extern "C" void func_001D8D40(void *, void *, void *); // 0x001D8D40
extern "C" void func_00209AA8(void *, void *, void *); // 0x00209AA8
extern "C" void func_00209B60(void *, void *, void *); // 0x00209B60
extern "C" void func_001D8FF0(void *, void *, void *, void *); // 0x001D8FF0
extern "C" void func_0020B428(const void *, void *); // 0x0020B428
extern "C" void func_00209AD8(void *, void *, void *); // 0x00209AD8
extern "C" void func_0020C418(void *, const void *, void *); // 0x0020C418
extern "C" void func_00223DC8(void *, void *, void *, int); // 0x00223DC8

struct UnkIVPTime1F4
{
    u64 mVal;
} __attribute__((packed));

struct UnkIVPEnv1F4
{
    char pad00[0x104];
    UnkIVPTime1F4 mTime104; // 0x104
};

struct UnkIVPPoint1F4
{
    f32 x, y, z, w;
    inline UnkIVPPoint1F4() {}
};

struct UnkIVPMat1F4
{
    UnkIVPPoint1F4 rows[3];
    UnkIVPPoint1F4 vv;
};

struct UnkIVPObj1F48A0
{
    char pad00[0x14];
    UnkIVPEnv1F4 *mEnv14; // 0x14
    char pad18[0x14];
    void *mField2C;       // 0x2C
    f32 mField30;         // 0x30
    f32 mField34;         // 0x34
    f32 mField38;         // 0x38
    char pad3C[0x3C];
    union
    {
        u8 mType78;       // 0x78
        u64 mFlags78;     // 0x78
    };
    char pad80[0x1C];
    void *mCore9C;        // 0x9C
    void *mFieldA0;       // 0xA0
};

void func_001F48A0(int objInt)
{
    UnkIVPObj1F48A0 *obj = (UnkIVPObj1F48A0 *)objInt;
    if (obj->mType78 != 8)
    {
        func_001D9AD8(obj->mCore9C);
    }
    else
    {
        func_001F7B18(obj->mEnv14, obj->mFieldA0);
    }
}

extern "C" void func_001F47D0(UnkIVPObj1F48A0 *obj, void *arg1, void *arg2)
{
    func_001F48A0((int)obj);
    void *core = obj->mCore9C;
    UnkIVPMat1F4 m;
    UnkIVPTime1F4 t = obj->mEnv14->mTime104;
    func_001D8D40(core, &t, &m);
    UnkIVPPoint1F4 sp50;
    UnkIVPPoint1F4 sp60;
    func_00209AA8(&m, arg1, &sp60);
    func_00209B60(&m, arg2, &sp50);
    func_001D8FF0(core, &sp60, &sp50, arg2);
}

struct UnkIVPPoint16
{
    f32 x, y, z, w;
} __attribute__((aligned(16)));

#ifdef NON_MATCHING
// 70 of 75 instructions differ: m.vv = *arg2 uses VU0 lqc2/sqc2 and register pressure spills core/arg3.
extern "C" void func_001F45C0(UnkIVPObj1F48A0 *obj, const UnkIVPPoint16 *arg1, const UnkIVPPoint16 *arg2, int arg3)
{
    void *core = obj->mCore9C;
    UnkIVPPoint16 sp0 = *arg1;
    UnkIVPPoint16 sp10 = *arg2;
    if (((int)(obj->mFlags78 >> 10) & 3) == 0)
    {
        UnkIVPMat1F4 m;
        func_0020B428(arg1, &m);
        *(UnkIVPPoint16 *)&m.vv = *arg2;
        UnkIVPPoint1F4 neg;
        neg.x = -obj->mField30;
        neg.y = -obj->mField34;
        neg.z = -obj->mField38;
        func_00209AD8(&m, &neg, &sp10);
    }
    if (obj->mField2C != 0)
    {
        func_0020C418(&sp0, arg1, obj->mField2C);
    }
    void *sp70 = core;
    func_00223DC8(&sp70, &sp0, &sp10, arg3);
}
#endif

#ifdef NON_MATCHING
// Uses VU0 inline asm (lqc2/qmtc2.ni/vmulx.xyz/vadd.xyz/sqc2) and IVP_Time unaligned copy.
extern "C" void func_001F37A0(void *, void *, int, int);          // 0x001F37A0
extern "C" void *func_001FDD40(void *, void *);                  // 0x001FDD40
extern "C" void func_001FD848(void *, void *);                    // 0x001FD848
extern "C" void func_001D9968(void *, void *, f32);               // 0x001D9968
extern "C" void func_001D9900(void *, void *);                    // 0x001D9900
extern "C" void func_001F4EB0(int, void *, void *, void *, int);  // 0x001F4EB0
extern "C" void func_001D6C90(void *);                            // 0x001D6C90

extern "C" void func_001F48E0(UnkIVPObj1F48A0 *arg0, UnkIVPObj1F48A0 *arg1, int arg2, int arg4, f32 dt)
{
    void *sp0[4];
    f32 sp10[4];
    UnkIVPPoint16 sp30;
    if (dt < 0.0f)
    {
        // Advances arg1's position/orientation by dt using VU0 vector math.
        arg1 = (UnkIVPObj1F48A0 *)&sp30;
    }
    if ((s8)arg0->mField78 < 8)
    {
        if ((s8)arg1->mField78 >= 8)
            func_001F37A0(arg1, arg1, arg2, arg4);
    }
    else if ((s8)arg1->mField78 < 8)
    {
        func_001F37A0(arg0, arg1, arg2, arg4);
    }
    void *core1 = arg1->mCore9C;
    if (*(void **)((u8 *)arg1 + 0x40) == 0)
    {
        *(void **)((u8 *)arg1 + 0x40) = func_001FDD40(*(void **)((u8 *)arg1->mEnv14 + 0x94), arg1);
    }
    void *cache = *(void **)((u8 *)arg1 + 0x40);
    if (arg1->mField78 < 8)
    {
        if (*(f32 *)cache < *(f32 *)((u8 *)arg1->mEnv14 + 0x11C))
            func_001FD848(cache, cache);
    }
    void *core0 = arg0->mCore9C;
    f32 t0 = dt + *(f32 *)((u8 *)core1 + 0x4);
    if (*(f32 *)((u8 *)core0 + 0x4) < t0)
        *(f32 *)((u8 *)core0 + 0x4) = t0;
    f32 t1 = dt + *(f32 *)((u8 *)core1 + 0x8);
    if (*(f32 *)((u8 *)core0 + 0x8) < t1)
        *(f32 *)((u8 *)core0 + 0x8) = t1;
    func_001D9968(core1, arg1, t1);
    arg1->mCore9C = core0;
    *(void **)((u8 *)arg1 + 0xA0) = core0;
    *(void **)((u8 *)arg1 + 0xA4) = core0;
    func_001D9900(core0, arg1);
    arg1->mField78 = arg0->mField78;
    func_001F4EB0(0, arg1, sp0, sp10, 0);
    func_001D6C90(core0);
}
#endif
