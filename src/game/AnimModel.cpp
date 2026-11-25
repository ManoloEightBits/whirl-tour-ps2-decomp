#include "common/types.h"

// UnkActor11A (0x0011A198..0x0011A820), UnkTable11A8 (0x0011A8C8..0x0011A910),
// UnkDef11AB (0x0011AB78..0x0011AC98), UnkClip1B7 (0x001B7D18..0x001B7F90) and
// UnkAnim1B8 (0x001B8748..0x001B8A30). No RTTI; names are ours from address ranges.

struct UnkClipEntry1B7
{
    int mField00; // +0x54
    int mField04; // +0x58
};

struct UnkClip1B7
{
    char field_0x00[0x40];
    f32 mField40;                  // 0x40
    f32 mField44;                  // 0x44
    int mCount48;                  // 0x48
    int mField4C;                  // 0x4C
    int mField50;                  // 0x50
    UnkClipEntry1B7 mEntries54[1]; // 0x54

    UnkClip1B7 *GetSelf();                 // 0x001B7D18
    f32 GetField40();                      // 0x001B7D20
    f32 GetField44();                      // 0x001B7D28
    f32 GetDuration44_40();                // 0x001B7D30
    int GetByteSize1B7D40();               // 0x001B7D40
    int GetField48();                      // 0x001B7D50
    int GetEntry54(int idx);               // 0x001B7D58
    int GetEntry58(int idx);               // 0x001B7D68
    int GetField50();                      // 0x001B7D78
    void Destroy1B7F28();                  // 0x001B7F28
    void SetEntry54(int idx, int val);     // 0x001B7F48
    void SetEntry58(int idx, int val);     // 0x001B7F58
    void SetField50(int v);                // 0x001B7F90
};

void MemFree1BD978(void *);       // 0x001BD978
int func_001B6950(void *);        // 0x001B6950
int func_001B6958(void *, int);   // 0x001B6958
int func_001B6960(void *, int);   // 0x001B6960
int func_001B6970(void *);        // 0x001B6970
int func_001B6978(void *, int);   // 0x001B6978
int func_001B6998(void *);        // 0x001B6998
void func_001B88B0(void *);       // 0x001B88B0
void func_001B8840(void *, int, int, int, f32, f32, f32); // 0x001B8840
void func_001B8A38(void *, void *); // 0x001B8A38
void *func_00126280(int id);      // 0x00126280
int func_001BEE68(int, int, int); // 0x001BEE68
int func_001BEEE0(int, int, int, int); // 0x001BEEE0
extern int data_0027B488[];       // 0x0027B488

UnkClip1B7 *UnkClip1B7::GetSelf()
{
    return this;
}

f32 UnkClip1B7::GetField40()
{
    return mField40;
}

f32 UnkClip1B7::GetField44()
{
    return mField44;
}

f32 UnkClip1B7::GetDuration44_40()
{
    return mField44 - mField40;
}

int UnkClip1B7::GetByteSize1B7D40()
{
    return mField4C * 8 + 0x54;
}

int UnkClip1B7::GetField48()
{
    return mCount48;
}

int UnkClip1B7::GetEntry54(int idx)
{
    return mEntries54[idx].mField00;
}

int UnkClip1B7::GetEntry58(int idx)
{
    return mEntries54[idx].mField04;
}

int UnkClip1B7::GetField50()
{
    return mField50;
}

void UnkClip1B7::Destroy1B7F28()
{
    MemFree1BD978(this);
}

void UnkClip1B7::SetEntry54(int idx, int val)
{
    mEntries54[idx].mField00 = val;
}

void UnkClip1B7::SetEntry58(int idx, int val)
{
    mEntries54[idx].mField04 = val;
}

void UnkClip1B7::SetField50(int v)
{
    mField50 = v;
}

struct UnkAnimSub34
{
    int mField00; // 0x00
};

struct UnkAnim1B8
{
    int mFlags00;         // 0x00
    f32 mField04;         // 0x04
    f32 mField08;         // 0x08
    void *mField0C;       // 0x0C
    UnkClip1B7 *mClip10;  // 0x10
    int mField14;         // 0x14
    f32 mField18;         // 0x18
    int mField1C;         // 0x1C
    int mField20;         // 0x20
    int mField24;         // 0x24
    f32 mField28;         // 0x28
    f32 mField2C;         // 0x2C
    f32 mField30;         // 0x30
    UnkAnimSub34 *mSub34; // 0x34
    int mField38;         // 0x38
    void *mField3C;       // 0x3C
    int mField40;         // 0x40
    int mField44;         // 0x44
    int mField48;         // 0x48
    int mField4C;         // 0x4C
    int mField50;         // 0x50

    int Action1B6958(int a);          // 0x001B8748
    void *GetField3C();               // 0x001B8768
    void *GetFieldC();                // 0x001B8770
    int GetField44();                 // 0x001B8778
    int GetField40();                 // 0x001B8780
    int Action1B6970();               // 0x001B8788
    int GetEntry48(int idx);          // 0x001B87A8
    int GetField48();                 // 0x001B87B8
    int Action1B6978(int a);          // 0x001B87C0
    int func_001B87E0();              // 0x001B87E0
    void Action1B6950();              // 0x001B8820
    void ClearFlags00_C();            // 0x001B88F0
    void SetFlag00_2();               // 0x001B8908
    void func_001B8918();             // 0x001B8918
    void SetFields4C_50(int a, int b);// 0x001B8950
    int TestFlag00_1();               // 0x001B8960
    int TestFlag00_4();               // 0x001B8970
    int TestFlag00_8();               // 0x001B8980
    int GetSub34Field00();            // 0x001B8990
    int GetField24();                 // 0x001B89A0
    UnkClip1B7 *GetField10();         // 0x001B89A8
    f32 GetField30();                 // 0x001B89B0
    void SetField2C(f32 v);           // 0x001B89B8
    void SetField8(f32 v);            // 0x001B89C0
    int GetConst0();                  // 0x001B89C8
    f32 GetConst0F();                 // 0x001B89D0
    void SetFlag00_10(int enable);    // 0x001B89E0
    void SetFlag00_20();              // 0x001B8A08
    void ClearFlag00_20();            // 0x001B8A18
    void SetField4(f32 v);            // 0x001B8A30
};

int UnkAnim1B8::Action1B6958(int a)
{
    return func_001B6958(mField0C, a);
}

void *UnkAnim1B8::GetField3C()
{
    return mField3C;
}

void *UnkAnim1B8::GetFieldC()
{
    return mField0C;
}

int UnkAnim1B8::GetField44()
{
    return mField44;
}

int UnkAnim1B8::GetField40()
{
    return mField40;
}

int UnkAnim1B8::Action1B6970()
{
    return func_001B6970(mField0C);
}

int UnkAnim1B8::GetEntry48(int idx)
{
    return mField48 + (idx << 6);
}

int UnkAnim1B8::GetField48()
{
    return mField48;
}

int UnkAnim1B8::Action1B6978(int a)
{
    return func_001B6978(mField0C, a);
}

int UnkAnim1B8::func_001B87E0()
{
    if (func_001B6970(mField0C) != 0)
        return func_001B6978(mField0C, 0);
    return 0;
}

void UnkAnim1B8::Action1B6950()
{
    func_001B6950(mField3C);
}

void UnkAnim1B8::ClearFlags00_C()
{
    mFlags00 &= ~0xC;
}

void UnkAnim1B8::SetFlag00_2()
{
    mFlags00 |= 2;
}

void UnkAnim1B8::func_001B8918()
{
    if (mField18 > 0.0f)
        mField28 = mField18 - 1.0f;
}

void UnkAnim1B8::SetFields4C_50(int a, int b)
{
    mField4C = a;
    mField50 = b;
}

int UnkAnim1B8::TestFlag00_1()
{
    return mFlags00 & 1;
}

int UnkAnim1B8::TestFlag00_4()
{
    return mFlags00 & 4;
}

int UnkAnim1B8::TestFlag00_8()
{
    return mFlags00 & 8;
}

int UnkAnim1B8::GetSub34Field00()
{
    return mSub34->mField00;
}

int UnkAnim1B8::GetField24()
{
    return mField24;
}

UnkClip1B7 *UnkAnim1B8::GetField10()
{
    return mClip10;
}

f32 UnkAnim1B8::GetField30()
{
    return mField30;
}

void UnkAnim1B8::SetField2C(f32 v)
{
    mField2C = v;
}

void UnkAnim1B8::SetField8(f32 v)
{
    mField08 = v;
}

int UnkAnim1B8::GetConst0()
{
    return 0;
}

f32 UnkAnim1B8::GetConst0F()
{
    return 0.0f;
}

void UnkAnim1B8::SetFlag00_10(int enable)
{
    if (enable != 0)
    {
        do
        {
            mFlags00 |= 0x10;
        } while (0);
    }
    else
    {
        mFlags00 &= ~0x10;
    }
}

void UnkAnim1B8::SetFlag00_20()
{
    mFlags00 |= 0x20;
}

void UnkAnim1B8::ClearFlag00_20()
{
    mFlags00 &= ~0x20;
}

void UnkAnim1B8::SetField4(f32 v)
{
    mField04 = v;
}

struct UnkEntry8
{
    f32 mField00;
    int mField04;
};

struct UnkTable8
{
    int mCount00;
    UnkEntry8 mEntries04[1];
};

struct UnkPair84
{
    s8 mField00;
    char pad01[3];
    int mField04;
};

struct UnkPair98
{
    int mId00;
    void *mPtr04;
};

struct UnkDef11AB
{
    char field_0x00[0x4C];
    int mCount4C;             // 0x4C
    int mArr50[10];           // 0x50..0x77
    f32 mField78;             // 0x78
    UnkTable8 *mEntries7C;    // 0x7C
    int mCount80;             // 0x80
    UnkPair84 mArr84[2];      // 0x84..0x93
    int mCount94;             // 0x94
    UnkPair98 mArr98[6];      // 0x98..0xC7
    int mCountC8;             // 0xC8
    UnkPair98 mArrCC[1];      // 0xCC

    void SetField78(f32 v);              // 0x0011AB78
    void SetField7C(UnkTable8 *v);       // 0x0011AB80
    void AddEntry84(int a, s8 b);        // 0x0011AB88
    void ClearCounts80_C8();             // 0x0011ABB8
    void AddEntry98(int id);             // 0x0011ABC8
    void AddEntry50(int val);            // 0x0011AC20
    void AddEntryCC(int id);             // 0x0011AC40
    void ResolveEntries11AC98();         // 0x0011AC98
};

struct UnkActor11A
{
    UnkDef11AB *mDef00;   // 0x00
    int mArr04[3];        // 0x04..0x0F
    int mArr10[3];        // 0x10..0x1B
    char field_0x1C[0x18];
    int mField34;         // 0x34
    int mField38;         // 0x38
    int mField3C;         // 0x3C
    char field_0x40[0x0C];
    int mFlags4C;         // 0x4C
    UnkAnim1B8 *mAnim50;  // 0x50
    f32 mField54;         // 0x54
    int mField58;         // 0x58
    int mField5C;         // 0x5C
    Vec3f mVec60;         // 0x60
    f32 mField6C;         // 0x6C
    f32 mVec70X;          // 0x70
    f32 mVec70Y;          // 0x74
    f32 mVec70Z;          // 0x78
    f32 mField7C;         // 0x7C
    int mField80;         // 0x80
    u32 mField84;         // 0x84

    UnkPair84 *GetDefPair84(int idx);         // 0x0011A198
    void SetFlag4C_1();                       // 0x0011A1B0
    void ClearFlag4C_1();                     // 0x0011A1C0
    void SetVec70(f32 x, f32 y, f32 z);       // 0x0011A1D8
    void SetField6C(f32 v);                   // 0x0011A1E8
    void SetField7C_1();                      // 0x0011A1F0
    void SetField7C_001();                    // 0x0011A200
    void ClearField7C();                      // 0x0011A218
    int IsField7CNonZero();                   // 0x0011A220
    void SetField80(int v);                   // 0x0011A248
    void SetField84Bounded(u32 v);            // 0x0011A250
    UnkAnim1B8 *GetField50();                 // 0x0011A270
    int GetField34();                         // 0x0011A278
    int GetArr04(u32 idx);                    // 0x0011A280
    int GetArr10(u32 idx);                    // 0x0011A2A0
    int GetField58();                         // 0x0011A2C0
    int GetField5C();                         // 0x0011A2C8
    int GetEntry7C_8(int id);                 // 0x0011A2D0
    f32 GetEntry7C_4(int id);                 // 0x0011A2F0
    void SetField54(f32 v);                   // 0x0011A310
    void Action1B8A30(f32 v);                 // 0x0011A318
    void func_0011A338(f32 v);                // 0x0011A338
    void Action1B89C0(f32 v);                 // 0x0011A380
    void SetVec60(const Vec3f *v);            // 0x0011A3A0
    void SetFields38_0_3C_1();                // 0x0011A3C0
    void SetFields3C_0_38_1();                // 0x0011A3D0
    int Action1B8960();                       // 0x0011A470
    int Action1B8970();                       // 0x0011A490
    int Action1B8980();                       // 0x0011A4B0
    void Action1B88F0();                      // 0x0011A4D0
    void Action1B8908();                      // 0x0011A4F0
    void Action1B8918();                      // 0x0011A510
    int Action1B89A0();                       // 0x0011A530
    void Action1B8820();                      // 0x0011A550
    int Action1B8990();                       // 0x0011A570
    void Action1B88B0();                      // 0x0011A590
    void Action1B89E0(int enable);            // 0x0011A5B0
    void CopyFrom11A5D0(UnkActor11A *other);  // 0x0011A5D0
    void Method11A818();                      // 0x0011A818
};

UnkPair84 *UnkActor11A::GetDefPair84(int idx)
{
    return &mDef00->mArr84[idx];
}

void UnkActor11A::SetFlag4C_1()
{
    mFlags4C |= 1;
}

void UnkActor11A::ClearFlag4C_1()
{
    mFlags4C &= ~1;
}

void UnkActor11A::SetVec70(f32 x, f32 y, f32 z)
{
    mVec70X = x;
    mVec70Y = y;
    mVec70Z = z;
}

void UnkActor11A::SetField6C(f32 v)
{
    mField6C = v;
}

void UnkActor11A::SetField7C_1()
{
    mField7C = 1.0f;
}

void UnkActor11A::SetField7C_001()
{
    mField7C = 0.001f;
}

void UnkActor11A::ClearField7C()
{
    *(int *)&mField7C = 0;
}

int UnkActor11A::IsField7CNonZero()
{
    return mField7C != 0.0f;
}

void UnkActor11A::SetField80(int v)
{
    mField80 = v;
}

void UnkActor11A::SetField84Bounded(u32 v)
{
    if (v < (u32)mDef00->mCountC8)
        mField84 = v;
}

UnkAnim1B8 *UnkActor11A::GetField50()
{
    return mAnim50;
}

int UnkActor11A::GetField34()
{
    return mField34;
}

int UnkActor11A::GetArr04(u32 idx)
{
    if (idx > 3)
        idx = 3;
    return mArr04[idx];
}

int UnkActor11A::GetArr10(u32 idx)
{
    if (idx > 3)
        idx = 3;
    return mArr10[idx];
}

int UnkActor11A::GetField58()
{
    return mField58;
}

int UnkActor11A::GetField5C()
{
    return mField5C;
}

int UnkActor11A::GetEntry7C_8(int id)
{
    return mDef00->mEntries7C->mEntries04[(id & 0xFFF) - 1].mField04;
}

f32 UnkActor11A::GetEntry7C_4(int id)
{
    return mDef00->mEntries7C->mEntries04[(id & 0xFFF) - 1].mField00;
}

void UnkActor11A::SetField54(f32 v)
{
    mField54 = v;
}

void UnkActor11A::Action1B8A30(f32 v)
{
    mAnim50->SetField4(v);
}

void UnkActor11A::func_0011A338(f32 v)
{
    mAnim50->SetField2C(v * mAnim50->GetField10()->GetDuration44_40());
}

void UnkActor11A::Action1B89C0(f32 v)
{
    mAnim50->SetField8(v);
}

void UnkActor11A::SetVec60(const Vec3f *v)
{
    Vec3f *d = &mVec60;
    d->x = v->x;
    d->y = v->y;
    d->z = v->z;
}

void UnkActor11A::SetFields38_0_3C_1()
{
    mField38 = 0;
    mField3C = 1;
}

void UnkActor11A::SetFields3C_0_38_1()
{
    mField3C = 0;
    mField38 = 1;
}

int UnkActor11A::Action1B8960()
{
    return mAnim50->TestFlag00_1();
}

int UnkActor11A::Action1B8970()
{
    return mAnim50->TestFlag00_4();
}

int UnkActor11A::Action1B8980()
{
    return mAnim50->TestFlag00_8();
}

void UnkActor11A::Action1B88F0()
{
    mAnim50->ClearFlags00_C();
}

void UnkActor11A::Action1B8908()
{
    mAnim50->SetFlag00_2();
}

void UnkActor11A::Action1B8918()
{
    mAnim50->func_001B8918();
}

int UnkActor11A::Action1B89A0()
{
    return mAnim50->GetField24();
}

void UnkActor11A::Action1B8820()
{
    mAnim50->Action1B6950();
}

int UnkActor11A::Action1B8990()
{
    return mAnim50->GetSub34Field00();
}

void UnkActor11A::Action1B88B0()
{
    func_001B88B0(mAnim50);
}

void UnkActor11A::Action1B89E0(int enable)
{
    mAnim50->SetFlag00_10(enable);
}

void UnkActor11A::CopyFrom11A5D0(UnkActor11A *other)
{
    mField54 = other->mField54;
    mFlags4C = other->mFlags4C;
    func_001B8A38(mAnim50, other->mAnim50);
}

void UnkActor11A::Method11A818()
{
}

struct UnkTable11A8Entry
{
    f32 mField00;
    int mField04;
};

struct UnkTable11A8
{
    int mCount00;
    UnkTable11A8Entry mEntries04[1];

    void ClearCount00();              // 0x0011A8C8
    int GetByteSize11A8D0();          // 0x0011A8D0
    void AddEntry(int a, f32 b);      // 0x0011A8E0
};

void UnkTable11A8::ClearCount00()
{
    mCount00 = 0;
}

int UnkTable11A8::GetByteSize11A8D0()
{
    return (mCount00 * 8) | 4;
}

void UnkTable11A8::AddEntry(int a, f32 b)
{
    mEntries04[mCount00].mField04 = a;
    mEntries04[mCount00].mField00 = b;
    mCount00++;
}

void UnkDef11AB::SetField78(f32 v)
{
    mField78 = v;
}

void UnkDef11AB::SetField7C(UnkTable8 *v)
{
    mEntries7C = v;
}

void UnkDef11AB::AddEntry84(int a, s8 b)
{
    mArr84[mCount80].mField00 = b;
    mArr84[mCount80].mField04 = a;
    mCount80++;
}

void UnkDef11AB::ClearCounts80_C8()
{
    mCount80 = 0;
    mCountC8 = 0;
}

void UnkDef11AB::AddEntry98(int id)
{
    mArr98[mCount94].mId00 = id;
    mArr98[mCount94].mPtr04 = func_00126280(id);
    mCount94++;
}

void UnkDef11AB::AddEntry50(int val)
{
    mArr50[mCount4C++] = val;
}

void UnkDef11AB::AddEntryCC(int id)
{
    mArrCC[mCountC8].mId00 = id;
    mArrCC[mCountC8].mPtr04 = func_00126280(id);
    mCountC8++;
}

void UnkDef11AB::ResolveEntries11AC98()
{
    u32 i;
    for (i = 0; i < (u32)mCount94; i++)
        mArr98[i].mPtr04 = func_00126280(mArr98[i].mId00);
    for (i = 0; i < (u32)mCountC8; i++)
        mArrCC[i].mPtr04 = func_00126280(mArrCC[i].mId00);
}

// 0x001B6950..0x001B6998: Skeleton header (0x10 bytes + 0x20-byte joints)
struct UnkSkel1B6
{
    u16 mCount00;  // 0x00
    u16 mCount02;  // 0x02
    u8 mCount04;   // 0x04
    u8 mCount05;   // 0x05
    u16 mField06;  // 0x06
    int mField08;  // 0x08
    int mField0C;  // 0x0C
};

int func_001B6950(void *p)
{
    return ((UnkSkel1B6 *)p)->mField0C;
}

int func_001B6958(void *p, int)
{
    return ((UnkSkel1B6 *)p)->mCount02;
}

int func_001B6960(void *p, int idx)
{
    int off = (idx << 5) + 0x10;
    return (int)p + off;
}

int func_001B6970(void *p)
{
    return ((UnkSkel1B6 *)p)->mCount05;
}

int func_001B6978(void *p, int idx)
{
    UnkSkel1B6 *s = (UnkSkel1B6 *)p;
    int off = (s->mCount00 << 5) + 0x10;
    return (int)s + off + (idx << 5);
}

int func_001B6998(void *p)
{
    UnkSkel1B6 *s = (UnkSkel1B6 *)p;
    int c0 = s->mCount00 - 1;
    int a = (s->mCount04 << 5) + 0x30;
    return (c0 << 5) + a;
}

// 0x001B7638..0x001B76F8: Keyframe helper structs
struct UnkBlock16
{
    u8 b[16];
};

struct UnkBlock20
{
    u8 b[16];
    int c;
};

struct UnkKey1B76
{
    Vec3f mVec00; // 0x00
    u16 mField0C; // 0x0C
    u8 mField0E;  // 0x0E
    u8 mField0F;  // 0x0F
    f32 mField10; // 0x10

    void Init1B7638(u8 e, u16 c, const Vec3f *v);         // 0x001B7638
    void Copy1B7660(const void *src);                     // 0x001B7660
    void Init1B7688(u8 e, u16 c, const Vec3f *v, f32 f);  // 0x001B7688
    void Copy1B76B8(const void *src);                     // 0x001B76B8
    void SetHalfs1B76E8(u16 a, u16 b);                    // 0x001B76E8
    void Set1B76F8(u8 e, u16 c, const Vec3f *v);          // 0x001B76F8
};

void UnkKey1B76::Init1B7638(u8 e, u16 c, const Vec3f *v)
{
    mField0E = e;
    mField0C = c;
    mField0F = 0;
    mVec00.x = v->x;
    mVec00.y = v->y;
    mVec00.z = v->z;
}

void UnkKey1B76::Copy1B7660(const void *src)
{
    *(UnkBlock16 *)this = *(const UnkBlock16 *)src;
}

void UnkKey1B76::Init1B7688(u8 e, u16 c, const Vec3f *v, f32 f)
{
    mField0E = e;
    mField0C = c;
    mField0F = 0;
    mVec00.x = v->x;
    mVec00.y = v->y;
    mVec00.z = v->z;
    mField10 = f;
}

void UnkKey1B76::Copy1B76B8(const void *src)
{
    *(UnkBlock20 *)this = *(const UnkBlock20 *)src;
}

void UnkKey1B76::SetHalfs1B76E8(u16 a, u16 b)
{
    ((u16 *)this)[0] = a;
    ((u16 *)this)[1] = b;
}

void UnkKey1B76::Set1B76F8(u8 e, u16 c, const Vec3f *v)
{
    mField0E = e;
    mField0C = c;
    mVec00.x = v->x;
    mVec00.y = v->y;
    mVec00.z = v->z;
}

// 0x001B7AE8..0x001B7C08: UnkModel1B7
struct UnkModel1B7
{
    char field_0x00[0x40];
    u16 mCount40; // 0x40
    u16 mCount42; // 0x42
    int mPtr44;   // 0x44
    u16 mCount48; // 0x48
    u16 mCount4A; // 0x4A
    int mPtr4C;   // 0x4C
    u16 mCount50; // 0x50
    u16 mCount52; // 0x52
    int mPtr54;   // 0x54
    u16 mCount58; // 0x58
    u16 mCount5A; // 0x5A
    int mPtr5C;   // 0x5C
    u16 mCount60; // 0x60
    u16 mCount62; // 0x62
    int mPtr64;   // 0x64
    int mField68; // 0x68
    int mField6C; // 0x6C

    void Destroy1B7AE8();              // 0x001B7AE8
    void InitPtrs1B7B08();             // 0x001B7B08
    u16 GetCount42();                  // 0x001B7B58
    u16 GetCount4A();                  // 0x001B7B60
    u16 GetCount52();                  // 0x001B7B68
    u16 GetCount5A();                  // 0x001B7B70
    u16 GetCount62();                  // 0x001B7B78
    u16 GetCount60();                  // 0x001B7B80
    UnkModel1B7 *GetSelf();            // 0x001B7B88
    int GetEntry44(int idx);           // 0x001B7B90
    int GetEntry4C(int idx);           // 0x001B7BA0
    int GetEntry54(int idx);           // 0x001B7BB8
    int GetEntry5C(int idx);           // 0x001B7BC8
    int GetEntry64(int idx);           // 0x001B7BD8
    int GetField64();                  // 0x001B7BE8
    void Copy4_1B7BF0(const void *s);  // 0x001B7BF0
    void Copy16_1B7C08(const void *s); // 0x001B7C08
};

struct UnkBlock4
{
    u8 b[4];
};

void UnkModel1B7::Destroy1B7AE8()
{
    MemFree1BD978(this);
}

void UnkModel1B7::InitPtrs1B7B08()
{
    mPtr64 = (int)this + 0x70;
    mPtr44 = mPtr64 + (mCount62 << 5);
    mPtr4C = mPtr44 + (mCount40 << 4);
    mPtr54 = mPtr4C + mCount48 * 0x14;
    mPtr5C = mPtr54 + (mCount50 << 2);
}

u16 UnkModel1B7::GetCount42()
{
    return mCount42;
}

u16 UnkModel1B7::GetCount4A()
{
    return mCount4A;
}

u16 UnkModel1B7::GetCount52()
{
    return mCount52;
}

u16 UnkModel1B7::GetCount5A()
{
    return mCount5A;
}

u16 UnkModel1B7::GetCount62()
{
    return mCount62;
}

u16 UnkModel1B7::GetCount60()
{
    return mCount60;
}

UnkModel1B7 *UnkModel1B7::GetSelf()
{
    return this;
}

int UnkModel1B7::GetEntry44(int idx)
{
    return mPtr44 + (idx << 4);
}

int UnkModel1B7::GetEntry4C(int idx)
{
    return mPtr4C + idx * 0x14;
}

int UnkModel1B7::GetEntry54(int idx)
{
    return mPtr54 + (idx << 2);
}

int UnkModel1B7::GetEntry5C(int idx)
{
    return mPtr5C + (idx << 4);
}

int UnkModel1B7::GetEntry64(int idx)
{
    return mPtr64 + (idx << 5);
}

int UnkModel1B7::GetField64()
{
    return mPtr64;
}

void UnkModel1B7::Copy4_1B7BF0(const void *s)
{
    *(UnkBlock4 *)this = *(const UnkBlock4 *)s;
}

void UnkModel1B7::Copy16_1B7C08(const void *s)
{
    *(UnkBlock16 *)this = *(const UnkBlock16 *)s;
}

// 0x001B9730..0x001B9950: UnkScene1B9
int func_001B9730(int idx)
{
    return data_0027B488[idx];
}

struct UnkScene1B9
{
    int mField00;     // 0x00
    int mField04;     // 0x04
    int mField08;     // 0x08
    int mArr0C[14];   // 0x0C..0x44 (0x0C, 0x10, 0x14, 0x18, 0x1C, 0x20, 0x24, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C, 0x40)
    int mField44;     // 0x44
    int mField48;     // 0x48
    int mField4C;     // 0x4C

    int LookupArr0C(int idx, int a);             // 0x001B9748
    int LookupArr0CEx(int idx, int a, int b, int c); // 0x001B9780
    int Lookup0C(int a);                         // 0x001B97C0
    int Lookup30(int a);                         // 0x001B97E8
    int Lookup2C(int a);                         // 0x001B9810
    int Lookup20(int a);                         // 0x001B9838
    int Lookup28(int a);                         // 0x001B9860
    int Lookup18(int a);                         // 0x001B9888
    int Lookup34(int a);                         // 0x001B98B0
    int Lookup4C(int a);                         // 0x001B98D8
    int Lookup3C(int a);                         // 0x001B9900
    int Lookup38(int a);                         // 0x001B9928
    int Lookup40(int a);                         // 0x001B9950
};

int UnkScene1B9::LookupArr0C(int idx, int a)
{
    int r = 0;
    if (mArr0C[idx] != 0)
        r = func_001BEE68(mArr0C[idx], a, 0);
    return r;
}

int UnkScene1B9::LookupArr0CEx(int idx, int a, int b, int c)
{
    int r = 0;
    if (mArr0C[idx] != 0)
        r = func_001BEEE0(mArr0C[idx], a, b, c);
    return r;
}

int UnkScene1B9::Lookup0C(int a)
{
    int r = 0;
    if (mArr0C[0] != 0)
        r = func_001BEE68(mArr0C[0], a, 0);
    return r;
}

int UnkScene1B9::Lookup30(int a)
{
    int r = 0;
    if (mArr0C[9] != 0)
        r = func_001BEE68(mArr0C[9], a, 0);
    return r;
}

int UnkScene1B9::Lookup2C(int a)
{
    int r = 0;
    if (mArr0C[8] != 0)
        r = func_001BEE68(mArr0C[8], a, 0);
    return r;
}

int UnkScene1B9::Lookup20(int a)
{
    int r = 0;
    if (mArr0C[5] != 0)
        r = func_001BEE68(mArr0C[5], a, 0);
    return r;
}

int UnkScene1B9::Lookup28(int a)
{
    int r = 0;
    if (mArr0C[7] != 0)
        r = func_001BEE68(mArr0C[7], a, 0);
    return r;
}

int UnkScene1B9::Lookup18(int a)
{
    int r = 0;
    if (mArr0C[3] != 0)
        r = func_001BEE68(mArr0C[3], a, 0);
    return r;
}

int UnkScene1B9::Lookup34(int a)
{
    int r = 0;
    if (mArr0C[10] != 0)
        r = func_001BEE68(mArr0C[10], a, 0);
    return r;
}

int UnkScene1B9::Lookup4C(int a)
{
    int r = 0;
    if (mField4C != 0)
        r = func_001BEE68(mField4C, a, 0);
    return r;
}

int UnkScene1B9::Lookup3C(int a)
{
    int r = 0;
    if (mArr0C[12] != 0)
        r = func_001BEE68(mArr0C[12], a, 0);
    return r;
}

int UnkScene1B9::Lookup38(int a)
{
    int r = 0;
    if (mArr0C[11] != 0)
        r = func_001BEE68(mArr0C[11], a, 0);
    return r;
}

int UnkScene1B9::Lookup40(int a)
{
    int r = 0;
    if (mArr0C[13] != 0)
        r = func_001BEE68(mArr0C[13], a, 0);
    return r;
}

// 0x001BAA50..0x001BAA90: UnkTex1BA
struct UnkTex1BA
{
    char field_0x00[0x14];
    int mField14; // 0x14
    int mField18; // 0x18
    int mField1C; // 0x1C
    int mField20; // 0x20
    int mPtr24;   // 0x24

    void Destroy1BAA50();        // 0x001BAA50
    int GetEntry24(u8 idx);      // 0x001BAA70
    int GetField14();            // 0x001BAA88
    int GetField18();            // 0x001BAA90
};

void UnkTex1BA::Destroy1BAA50()
{
    MemFree1BD978(this);
}

int UnkTex1BA::GetEntry24(u8 idx)
{
    return mPtr24 + idx * 0x30;
}

int UnkTex1BA::GetField14()
{
    return mField14;
}

int UnkTex1BA::GetField18()
{
    return mField18;
}
