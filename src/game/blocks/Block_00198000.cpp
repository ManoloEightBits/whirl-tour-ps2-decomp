#include "common/types.h"
#include "common/libc.h"
#include "game/GL.h"
#include "game/FEScreen.h"

// Functions of 0x00198000..0x0019BFFF whose class and translation unit are not known yet.
// Names are address based; move each function to its file once its TU is identified.

void func_00197BC8(int);                               // 0x00197BC8
void func_001982D0(int, int);                          // 0x001982D0
void func_00198628(int, int, int, int);                // 0x00198628
void func_00198E08(int, int, int, int, int, int, int); // 0x00198E08
void func_00199738();                                  // 0x00199738
void func_001BD240(int);                               // 0x001BD240
void func_001BD360(void *);                            // 0x001BD360
int MemAlloc1BD958(int);                                // 0x001BD958
void MemFree1BD978(void *);                            // 0x001BD978

extern int data_002B2500[];

int func_00198090(int arg0)
{
    int result;

    result = MemAlloc1BD958(0x318);
    if (result != 0)
    {
        func_00197BC8(result);
        func_001982D0(result, arg0);
    }
    return result;
}

void func_00198330(int arg0, int arg1)
{
    if (arg1 != 0)
    {
        func_001BD240(arg0 + 0xC);
    }
}

void func_001983A0(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    func_00198E08(arg0 + 0x2C, arg1, arg2, arg3, arg4, arg5, arg6);
}

int func_00198578(int arg0, int arg1, int arg2)
{
    int result;

    result = MemAlloc1BD958(0x14);
    if (result != 0)
    {
        func_00198628(result, arg0, arg1, arg2);
    }
    return result;
}

int func_00198D00(int arg0)
{
    return arg0;
}

int func_00198D08(int arg0)
{
    return arg0 + 0x40;
}

int func_00198D10(int arg0)
{
    return arg0 + 0x80;
}

int func_00198D18(int arg0)
{
    return arg0 + 0xC0;
}

int func_00198D50(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5)
{
    int result;

    result = MemAlloc1BD958(0x34);
    if (result != 0)
    {
        func_00198E08(result, arg0, arg1, arg2, arg3, arg4, arg5);
    }
    return result;
}

void func_00198DE8(void *arg0)
{
    MemFree1BD978(arg0);
}

void func_001990C8()
{
    func_00199738();
}

void func_00199738()
{
}

void func_0019A610()
{
}

void DrawEnd19A6B0()
{
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void func_00197D98();                                       // 0x00197D98
void func_001A3188(int, int, int, int, int, int, int, int); // 0x001A3188
void func_001A3410(int);                                    // 0x001A3410
void func_001A42F8(int);                                    // 0x001A42F8

// UnkObj1982D0 (0x001982D0): no RTTI; its layout is the fields these methods use.
struct UnkObj1982D0
{
    char field_0x0[0x74];
    int mField74;                // 0x74

    void Method1982D0(int arg1); // 0x001982D0
};

void UnkObj1982D0::Method1982D0(int arg1)
{
    mField74 = arg1;
    func_00197D98();
}

// UnkObj198C78 (0x00198C78): no RTTI; its layout is the fields these methods use.
struct UnkObj198C78
{
    char field_0x0[0x14C];
    int mField14C;         // 0x14C

    void Method198C78();   // 0x00198C78
};

void UnkObj198C78::Method198C78()
{
    glDisable(GL_POLYGON_OFFSET_FILL);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, mField14C);
    func_001A3188(0xDE1, 0, 0, 0, 0, 0, 0x80, 0x80);
    func_001A42F8(0x100);
    func_001A3410(0);
}

// UnkObj198D20 (0x00198D20): no RTTI; its layout is the fields these methods use.
struct UnkObj198D20
{
    char field_0x0[0x14C];
    int mField14C;         // 0x14C

    int GetField14C();     // 0x00198D20
};

int UnkObj198D20::GetField14C()
{
    return mField14C;
}

// UnkObj199C88 (0x00199C88..0x00199D60): no RTTI; its layout is the fields these methods use.
struct UnkObj199C88
{
    u32 mField0;         // 0x0
    u32 mField4;         // 0x4
    u32 mField8;         // 0x8
    u32 mFieldC;         // 0xC
    void *mField10;      // 0x10
    int mField14;        // 0x14

    void Method199C58(u32 a, u32 b); // 0x00199C58
    void Method199C78(void *a, int b); // 0x00199C78
    void Method199C88(); // 0x00199C88
    void Method199CA8(int alignBits); // 0x00199CA8
    u32 Method199CD8(int size, int alignBits); // 0x00199CD8
    void Method199D60(); // 0x00199D60
};

extern UnkObj199C88 data_00265CE8;

void UnkObj199C88::Method199C58(u32 a, u32 b)
{
{
    do {
        mField4 = b;
        mFieldC = a;
        mField14 = 0;
    } while (0);
    mField0 = a;
    mField8 = a;
    mField10 = 0;
}
}

void UnkObj199C88::Method199C78(void *a, int b)
{
{
    do { mField14 = b; } while (0);
    mField10 = a;
}
}

void UnkObj199C88::Method199CA8(int alignBits)
{
    u32 align = 1 << alignBits;
    u32 rem = mField8 & (align - 1);
    if (rem != 0)
        mField8 += align - rem;
}

u32 UnkObj199C88::Method199CD8(int size, int alignBits)
{
{
    u32 align = 1 << alignBits;
    u32 mask = align - 1;
    u32 rem = mField8 & mask;
    if (rem != 0)
        mField8 += align - rem;
    if (mField8 + size >= mField0 + mField4)
    {
        if (mFieldC < mField8)
            mFieldC = mField8;
        mField8 = mField0;
        u32 rem0 = mField0 & mask;
        if (rem0 != 0)
            mField8 = mField0 + (align - rem0);
    }
    u32 cur = mField8;
    mField8 = cur + size;
    return cur;
}
}

u32 func_00199740(int size, int alignBits)
{
    UnkObj199C88 *p = &data_00265CE8;
    u32 align = 1 << alignBits;
    u32 mask = align - 1;
    u32 rem = p->mField8 & mask;
    if (rem != 0)
        p->mField8 += align - rem;
    if (p->mField8 + size >= p->mField0 + p->mField4)
    {
        if (p->mFieldC < p->mField8)
            p->mFieldC = p->mField8;
        p->mField8 = p->mField0;
        u32 rem0 = p->mField0 & mask;
        if (rem0 != 0)
            p->mField8 = p->mField0 + (align - rem0);
    }
    u32 cur = p->mField8;
    p->mField8 = cur + size;
    return cur;
}

#ifdef NON_MATCHING
// func_001997D0: register differences; func_00199858: 52/55 match (slt count < padded hoisted
// before ptr + bytes).
u32 func_001997D0(int size)
{
    UnkObj199C88 *p = &data_00265CE8;
    u32 rem = p->mField8 & 0xF;
    if (rem != 0)
        p->mField8 += 0x10 - rem;
    if (p->mField8 + size >= p->mField0 + p->mField4)
    {
        if (p->mFieldC < p->mField8)
            p->mFieldC = p->mField8;
        p->mField8 = p->mField0;
        u32 rem0 = p->mField0 & 0xF;
        if (rem0 != 0)
            p->mField8 = p->mField0 + (0x10 - rem0);
    }
    u32 cur = p->mField8;
    p->mField8 = cur + size;
    return cur;
}

void func_00199858(int count, int alignBits, void **outPtr)
{
    UnkObj199C88 *p = &data_00265CE8;
    u32 align = 1 << alignBits;
    u32 mask = align - 1;
    int padded = (count + 3) & ~3;
    u32 rem = p->mField8 & mask;
    int bytes = padded * 0xC;
    if (rem != 0)
        p->mField8 += align - rem;
    u32 ptr = p->mField8;
    if (ptr + bytes >= p->mField0 + p->mField4)
    {
        if (p->mFieldC < ptr)
            p->mFieldC = ptr;
        p->mField8 = p->mField0;
        u32 rem0 = p->mField0 & mask;
        if (rem0 != 0)
            p->mField8 = p->mField0 + (align - rem0);
        ptr = p->mField8;
    }
    p->mField8 = ptr + bytes;
    *outPtr = (void *)ptr;
    if (count < padded)
        memset((void *)(ptr + count * 0xC), 0, (padded - count) * 0xC);
}
#endif

void func_00199D80(int alignBits)
{
    u32 align = 1 << alignBits;
    u32 rem = data_00265CE8.mField8 & (align - 1);
    if (rem != 0)
        data_00265CE8.mField8 += align - rem;
}

void DrawBegin19A640()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, 1000.0f, 0.0f, 1000.0f, -1000.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
}

struct UnkObj19AE48
{
    char pad00[0x60];
    int mField60; // 0x60
    int mField64; // 0x64
    int mField68; // 0x68
    int mField6C; // 0x6C
};

void func_0019AE48(UnkObj19AE48 *arg0, int arg1, int arg2, int arg3, int arg4)
{
{
    arg0->mField60 = arg1;
    arg0->mField64 = arg2;
    arg0->mField68 = arg3;
    arg0->mField6C = arg4;
    glViewport(arg1, arg2, arg3, arg4);
}
}

void UnkObj199C88::Method199C88()
{
    u32 tmp;

    tmp = mField8;
    if ((u32) mFieldC < tmp)
    {
        mFieldC = tmp;
    }
    mField8 = (u32) mField0;
}

void UnkObj199C88::Method199D60()
{
    u32 tmp;

    tmp = mField8;
    if ((u32) mFieldC < tmp)
    {
        mFieldC = tmp;
    }
    mField8 = (u32) mField0;
}

// Matched from the second m2c sweep (globals, switch tables): strings and float constants are
// literals, variables are data_<addr> in config/symbols.txt.

void func_001A24D0(int, int *); // 0x001A24D0
extern f32 data_002659E0;
extern f32 data_002659E4;
extern int data_002659D0;
extern int data_002B2528;

int func_00198D28()
{
    return data_002659D0;
}

void func_00199458(f32 fparg0, f32 fparg1)
{
    data_002659E0 = fparg0;
    data_002659E4 = fparg1;
}

void func_00199490(f32 fparg0)
{
    data_002659E0 = fparg0;
}

void func_001994A0(f32 fparg0)
{
    data_002659E4 = fparg0;
}

f32 func_001994B0()
{
    return data_002659E0;
}

f32 func_001994C0()
{
    return data_002659E4;
}

void func_001994D0(f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3)
{
    u32 temp_v0;

    temp_v0 = ((int) (fparg3 * 128.0f) << 0x18) | ((int) (fparg2 * 128.0f) << 0x10) | ((int) (fparg1 * 128.0f) << 8) | (int) (fparg0 * 128.0f);
    data_002B2528 = (((temp_v0 >> 0x18) - 1) << 0x19) | (((((temp_v0 >> 0x10) - 1) * 2) & 0xFF) << 0x10) | ((((temp_v0 >> 8) - 1) << 9) & 0xFE00) | (((temp_v0 - 1) * 2) & 0xFF);
}

void func_0019A618(int arg0)
{
    int sp0;

    sp0 = arg0;
    func_001A24D0(1, &sp0);
}

// The front end's start-up and shut-down: a memory pool of the given size (func_001996F8 prepares it),
// the four pads (func_001BC2B8(1, n)), their copies at 0x002659B0, a pad of type 2 over all four and
// a 0x101-byte buffer (func_001BC448).
FEPad *func_001BC2B8(int type, int index); // 0x001BC2B8
void func_001BC318(void *pad);             // 0x001BC318
s8 *func_001BC448();                       // 0x001BC448
void func_001BC490(void *buffer);          // 0x001BC490
void func_001996F8(int pool, int size);    // 0x001996F8
extern FEPad *gFEPads2659A0[4];
extern FEPad *data_002659B8;
extern FEPad *data_002659BC;
extern FEPad *data_002659C0;
extern s8 *data_002659C4;
extern int data_002659D8;
extern int data_002659DC;

void func_00198F58(int size)
{
    data_002659DC = size;
    data_002659D8 = MemAlloc1BD958(size);
    func_001996F8(data_002659D8, data_002659DC);
    for (int i = 0; i < 4; i++)
        gFEPads2659A0[i] = func_001BC2B8(1, i);
    gFEPad2659B0 = gFEPads2659A0[0];
    gFEPad2659B4 = gFEPads2659A0[1];
    data_002659B8 = gFEPads2659A0[2];
    data_002659BC = gFEPads2659A0[3];
    data_002659C0 = func_001BC2B8(2, 4);
    data_002659C4 = func_001BC448();
}

void func_00199030()
{
    for (int i = 0; i < 4; i++)
    {
        if (gFEPads2659A0[i] != 0)
            func_001BC318(gFEPads2659A0[i]);
    }
    if (data_002659C0 != 0)
        func_001BC318(data_002659C0);
    func_001BC490(data_002659C4);
    MemFree1BD978((void *)data_002659D8);
    data_002659D8 = 0;
    data_002659DC = 0;
}

void func_001BD260(int);     // 0x001BD260
extern f32 data_002659E8;

void func_001982F0(int arg0, int enable)
{
    if (enable != 0)
    {
        func_001BD240(arg0);
    }
}

void func_00198310(int arg0, int enable)
{
    if (enable != 0)
    {
        func_001BD260(arg0);
    }
}

struct UnkEntry1983C0
{
    int mFlags00;       // 0x00
    char pad04[0x40];
};

struct UnkObj1983C0
{
    char pad00[0xD0];
    UnkEntry1983C0 mEntries[8]; // 0xD0
};

// Clears bit 0 of the flags of eight entries of 0x44 bytes.
void func_001983C0(UnkObj1983C0 *obj)
{
    for (int i = 0; i < 8; i++)
        obj->mEntries[i].mFlags00 &= ~1;
}

void func_00199470(f32 fparg0, f32 fparg1, f32 fparg2)
{
    data_002659E0 = fparg0;
    data_002659E4 = fparg1;
    data_002659E8 = fparg2;
}

struct UnkNode198538
{
    UnkNode198538 *mNext; // 0x00
    char pad04[0x08];
    int mId;              // 0x0C
};

struct UnkObj198538
{
    char pad00[0x18];
    UnkNode198538 *mHead18; // 0x18
};

int func_00198538(void *arg0, int arg1)
{
{
    UnkNode198538 *node = ((UnkObj198538 *)arg0)->mHead18;
    UnkNode198538 *next = node->mNext;
    while (next != 0)
    {
        if (arg1 == node->mId)
            return 1;
        node = next;
        next = next->mNext;
    }
    return 0;
}
}

struct UnkObj198628
{
    int mField00; // 0x00
    int mField04; // 0x04
    int mField08; // 0x08
    int mField0C; // 0x0C
    int mField10; // 0x10
};

void func_001985E0(UnkObj198628 *arg0)
{
    if (arg0->mField00 != 0 || arg0->mField04 != 0)
        func_001BD360(arg0);
    MemFree1BD978(arg0);
}

void func_00198628(int arg0, int arg1, int arg2, int arg3)
{
{
    UnkObj198628 *obj = (UnkObj198628 *)arg0;
    obj->mField04 = 0;
    obj->mField00 = 0;
    do {
        obj->mField08 = arg1;
        obj->mField10 = arg3;
    } while (0);
    obj->mField0C = arg2;
}
}

int func_00198D38(int arg0)
{
    return data_002B2500[arg0];
}

struct UnkObj198E08
{
    int mField00; // 0x00
    int mField04; // 0x04
    int mField08; // 0x08
    int mField0C; // 0x0C
    int mField10; // 0x10
    int mField14; // 0x14
    f32 mField18; // 0x18
    f32 mField1C; // 0x1C
    f32 mField20; // 0x20
    f32 mField24; // 0x24
    int mField28; // 0x28
};

void func_00198E08(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
{
    UnkObj198E08 *obj = (UnkObj198E08 *)arg0;
    do {
        obj->mField10 = arg1;
        obj->mField14 = arg2;
        obj->mField08 = arg4;
        obj->mField0C = arg5;
        obj->mField04 = arg6;
        obj->mField00 = arg3;
    } while (0);
    f32 one = 1.0f;
    obj->mField24 = one;
    obj->mField18 = one;
    do {
        obj->mField1C = one;
        obj->mField20 = one;
    } while (0);
    obj->mField28 = 0;
}
}

struct UnkObj1974D8
{
    UnkObj1974D8 *mNext; // 0x00
    void Method1974D8(); // 0x001974D8
};

struct UnkObj198158
{
    UnkObj1974D8 *mHead00;  // 0x00
    char pad04[0x08];
    UnkObj1974D8 *mHead0C;  // 0x0C
    char pad10[0x08];
    UnkObj198628 *mHead18;  // 0x18
};

void func_00198158(UnkObj198158 *arg0)
{
    UnkObj1974D8 *a = arg0->mHead00;
    UnkObj1974D8 *next = a->mNext;
    while (next != 0)
    {
        a->Method1974D8();
        a = next;
        next = next->mNext;
    }
    UnkObj1974D8 *b = arg0->mHead0C;
    next = b->mNext;
    while (next != 0)
    {
        b->Method1974D8();
        b = next;
        next = next->mNext;
    }
    UnkObj198628 *c = arg0->mHead18;
    UnkObj198628 *nextC = *(UnkObj198628 **)c;
    while (nextC != 0)
    {
        func_001BD360(c);
        func_001985E0(c);
        c = nextC;
        nextC = *(UnkObj198628 **)nextC;
    }
    func_00197BC8((int)arg0);
}

void func_00198210(int arg0)
{
    UnkObj198158 *obj = (UnkObj198158 *)arg0;
    UnkObj1974D8 *a = obj->mHead00;
    UnkObj1974D8 *next = a->mNext;
    while (next != 0)
    {
        a->Method1974D8();
        a = next;
        next = next->mNext;
    }
    UnkObj1974D8 *b = obj->mHead0C;
    next = b->mNext;
    while (next != 0)
    {
        b->Method1974D8();
        b = next;
        next = next->mNext;
    }
    UnkObj198628 *c = obj->mHead18;
    UnkObj198628 *nextC = *(UnkObj198628 **)c;
    while (nextC != 0)
    {
        func_001BD360(c);
        func_001985E0(c);
        c = nextC;
        nextC = *(UnkObj198628 **)nextC;
    }
    func_00197BC8(arg0);
    MemFree1BD978(obj);
}
