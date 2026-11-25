#include "game/AI_Boss.h"

void func_00161978(void *); // 0x00161978

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
    return mField1DC;
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

Vec4f *AI_Boss::GetObj1E0Row3()
{
    return &mObj1E0->mMatrix50.row[3];
}

void AI_Boss::Action161978()
{
    func_00161978(mObj1E0);
}

Vec4f *AI_Boss::GetObj1E0Row1()
{
    return &mObj1E0->mMatrix50.row[1];
}

Vec4f *AI_Boss::GetObj1E0Row2()
{
    return &mObj1E0->mMatrix50.row[2];
}

Vec4f *AI_Boss::GetObj1E0Row0()
{
    return &mObj1E0->mMatrix50.row[0];
}

int * AI_Boss::GetPtr174()
{
    return &mField174;
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
    return &mFieldE0;
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

f32 AI_Boss::GetField138()
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
    return mField1F0;
}
