#include "game/AI_Boss.h"
#include "game/UnkEffect.h"
#include "game/Pickup.h"
#include "common/libc.h"

struct UnkActor11A
{
    int Action1B8980(); // 0x0011A4B0
};

void func_00161978(void *);    // 0x00161978
f32 func_001B1048(f32, f32);   // 0x001B1048
int func_0012F258(void *, int); // 0x0012F258
int func_0012F280(void *, int); // 0x0012F280
void func_0011A3E0(void *, int); // 0x0011A3E0
void PhysicsDestroy1F21A8(void *); // 0x001F21A8
void PhysicsClear1F34B0(void *, int); // 0x001F34B0
void func_0015F200(void *, int); // 0x0015F200
int func_00155460();           // 0x00155460
void func_00155558(int);       // 0x00155558
void func_0018C970(void *, int, int); // 0x0018C970
void *ArrayGetElement1BB098(void *, int); // 0x001BB098
extern s8 data_00262338;       // 0x00262338

UnkBossObj1E0 *AI_Boss::GetObj1E0()
{
    return mObj1E0;
}

UnkAttackActor *AI_Boss::GetField1D8()
{
    return mAttack1D8;
}

int AI_Boss::GetField1DC()
{
    return (int)mSound1DC;
}

f32 AI_Boss::GetAttackField10()
{
    return mAttack1D8->mField10;
}

int AI_Boss::GetField188()
{
    return mField188;
}

int AI_Boss::GetField18C()
{
    return mField18C;
}

void AI_Boss::SetField18C(int v)
{
    mField18C = v;
}

int AI_Boss::GetField190()
{
    return mField190;
}

void AI_Boss::SetField190(int v)
{
    mField190 = v;
}

Vec3f *AI_Boss::GetPosition()
{
    return (Vec3f *)&mObj1E0->mMatrix50.row[3];
}

void AI_Boss::Action161978()
{
    func_00161978(mObj1E0);
}

Vec4f *AI_Boss::GetObj1E0Row1()
{
    return &mObj1E0->mMatrix50.row[1];
}

Vec4f *AI_Boss::GetRow2()
{
    return &mObj1E0->mMatrix50.row[2];
}

Mat4x4f *AI_Boss::GetMatrix()
{
    return &mObj1E0->mMatrix50;
}

int * AI_Boss::GetPtr174()
{
    return (int *)&mPos174;
}

f32 AI_Boss::GetField180()
{
    return mField180;
}

void AI_Boss::SetField180(f32 v)
{
    mField180 = v;
}

f32 AI_Boss::GetField184()
{
    return mField184;
}

void AI_Boss::SetField184(f32 v)
{
    mField184 = v;
}

void AI_Boss::AddField184(f32 v)
{
    mField184 += v;
}

u8 AI_Boss::GetField13C()
{
    return mField13C;
}

void AI_Boss::SetField13C(u8 v)
{
    mField13C = v;
}

int AI_Boss::GetField15C()
{
    return mField15C;
}

int AI_Boss::GetField158()
{
    return mField158;
}

int * AI_Boss::GetPtrB0()
{
    return &mFieldB0;
}

int * AI_Boss::GetPtrF0()
{
    return &mFieldF0;
}

int * AI_Boss::GetPtrE0()
{
    return (int *)&mPosE0;
}

int AI_Boss::GetField1E4()
{
    return mField1E4;
}

int AI_Boss::GetField130()
{
    return mField130;
}

int AI_Boss::GetField160()
{
    return mField160;
}

u8 AI_Boss::GetField13D()
{
    return mField13D;
}

void AI_Boss::SetField13D(u8 v)
{
    mField13D = v;
}

f32 AI_Boss::VirtSlot8()
{
    return mField138;
}

void AI_Boss::SetField138(f32 v)
{
    mField138 = v;
}

f32 AI_Boss::GetField164()
{
    return mField164;
}

void AI_Boss::SetField164(f32 v)
{
    mField164 = v;
}

void AI_Boss::AddField164(f32 v)
{
    mField164 += v;
}

f32 AI_Boss::GetField168()
{
    return mField168;
}

void AI_Boss::SetField168(f32 v)
{
    mField168 = v;
}

void AI_Boss::AddField168(f32 v)
{
    mField168 += v;
}

f32 AI_Boss::GetField16C()
{
    return mField16C;
}

void AI_Boss::SetField16C(f32 v)
{
    mField16C = v;
}

void AI_Boss::AddField16C(f32 v)
{
    mField16C += v;
}

f32 AI_Boss::GetField170()
{
    return mField170;
}

void AI_Boss::SetField170(f32 v)
{
    mField170 = v;
}

int AI_Boss::GetField134()
{
    return mField134;
}

void AI_Boss::SetBits134(int bits)
{
    mField134 |= bits;
}

void AI_Boss::ClearBits134(int bits)
{
    mField134 &= ~bits;
}

int AI_Boss::TestFlags20_200()
{
    return mFlags20 & 0x200;
}

int AI_Boss::GetField1F0()
{
    return (int)mEffect1F0;
}

void AI_Boss::VirtSlot3()
{
}

f32 AI_Boss::GetField194(int i)
{
    return mArray194[i];
}

void AI_Boss::SetField194(int i, f32 v)
{
    mArray194[i] = v;
}

void AI_Boss::AddField194(int i, f32 v)
{
    mArray194[i] += v;
}

f32 AI_Boss::GetAttackField50(int i)
{
    return mAttack1D8->mArray50[i];
}

void Callback15EFF8(int arg)
{
    ((AI_Boss *)arg)->mFlags20 |= 0x20000000;
}

f32 AI_Boss::GetAttackField94(int i, int j)
{
    return mAttack1D8->mArray94[i][j];
}

void AI_Boss::Method15ED98()
{
    mField170 = func_001B1048(mFieldD0, mFieldD8);
}

int AI_Boss::GetField208(int i)
{
    return (int)mArr208[i];
}

void AI_Boss::Method15EF08()
{
    if (!(mFlags20 & 0x40000000))
    {
        if ((rand() % 10001) * 0.0001f < 0.5f || (mFlags20 & 0x400))
            mField134 |= 0x100;
        else
            mField134 |= 0x20;
        mField13D = 1;
    }
}

int AI_Boss::Method15E9C0()
{
    u8 idx = mField13C;
    if (idx >= 4)
        return 0;
    else
        return func_0012F258(mField98, idx);
}

int AI_Boss::Method15E9F8()
{
    u8 idx = mField13C;
    if (idx >= 4)
        return 0;
    else
        return func_0012F280(mField98, idx);
}

void AI_Boss::Method15EE30()
{
    if (mSound1DC->mCount10 != 0 && data_00262338 == -1)
    {
        if (mEffect1F0->mField2C & 0x20)
            mEffect1F0->func_00141A18();
        mEffect1F0->SetField28(mSound1DC->mArr74[rand() % mSound1DC->mCount10]);
        UnkEffect *eff = mEffect1F0;
        Vec3f *pos = &mPosE0;
        eff->mPos00.x = pos->x;
        eff->mPos00.y = pos->y;
        eff->mPos00.z = pos->z;
        mEffect1F0->func_001419A0(0);
        data_00262338 = mField1D;
    }
}

void AI_Boss::Method15D2F0()
{
    u32 arg = 0x10000;
    if (mField13D != 8)
    {
        func_0011A3E0((void *)mField15C, 0x19008);
        mField13D = 8;
        if (mSound1DC->mCount10 != 0 && data_00262338 == -1)
        {
            if (mEffect1F0->mField2C & 0x20)
                mEffect1F0->func_00141A18();
            mEffect1F0->SetField28(mSound1DC->mArr74[rand() % mSound1DC->mCount10]);
            UnkEffect *eff = mEffect1F0;
            Vec3f *pos = &mPosE0;
            eff->mPos00.x = pos->x;
            eff->mPos00.y = pos->y;
            eff->mPos00.z = pos->z;
            mEffect1F0->func_001419A0(0);
            data_00262338 = mField1D;
        }
        PhysicsDestroy1F21A8((void *)mField1E4);
        PhysicsClear1F34B0((void *)mField1E4, 0);
        arg = 0;
        if (mAttack1D8->mCount1FC != 0 && mArr208[0] != 0)
        {
            do
            {
                UnkBossSub208 *sub = mArr208[arg];
                arg = (u8)(arg + 1);
                sub->mField70 = sub->mSub10->mField4C;
            } while (arg < mAttack1D8->mCount1FC && mArr208[arg] != 0);
        }
    }
    func_0015F200(this, arg);
    if (((UnkActor11A *)mField15C)->Action1B8980() != 0)
    {
        if (func_00155460() != 0)
        {
            KeyPickup *kp = new KeyPickup(&mPosE0);
            kp->SetCallback68(Callback15EFF8, (int)this);
            func_00155558(2);
        }
        mField134 = (mField134 & ~0x80000) | 0x100000;
    }
}

void AI_Boss::Method15C890(int a, int b)
{
    if (mSound1DC->mCount14 != 0 && data_00262338 == -1 && !(mEffect1F0->mField2C & 0x20))
    {
        mEffect1F0->SetField28(mSound1DC->mArr88[rand() % mSound1DC->mCount14]);
        f32 pitch = (((rand() % 101) - 50) * 0.02f >= 0.0f) ? 1.25f : 0.75f;
        mEffect1F0->mField20 = pitch;
        f32 v = 1.0f - (rand() % 10001) * 0.000030000001f;
        mEffect1F0->field_0x1C = v;
        UnkEffect *eff = mEffect1F0;
        Vec3f *pos = &mPosE0;
        eff->mPos00.x = pos->x;
        eff->mPos00.y = pos->y;
        eff->mPos00.z = pos->z;
        mEffect1F0->func_001419A0(0);
        data_00262338 = mField1D;
    }
    func_0018C970(mFieldA0, a, b);
}

#ifdef NON_MATCHING
// 41 of 65 instructions differ: Vec3f copy and diff scheduling/register order; path->mCount0C is u16.
struct UnkBossNode15AD10 { int mField00; Vec3f mPos04; };

void AI_Boss::Method15AD10()
{
    u32 idx = mField190;
    Vec3f *target = &mPos174;
    mField134 = (mField134 & ~0x80) | 0x40;
    UnkBossPath *path = *(UnkBossPath **)ArrayGetElement1BB098((void *)mField188, mField18C);
    UnkBossNode15AD10 *node = (UnkBossNode15AD10 *)((char *)path + (idx * path->mStride01 * 4 + 0x10));
    target->x = node->mPos04.x;
    target->y = node->mPos04.y;
    target->z = node->mPos04.z;
    Vec3f *pos = GetPosition();
    Vec3f diff;
    diff.y = target->y - pos->y;
    diff.x = target->x - pos->x;
    diff.z = target->z - pos->z;
    mField180 = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
    mField190 = (idx >= (u32)(path->mCount0C - 1)) ? 0 : idx + 1;
}
#endif
