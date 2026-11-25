#include "game/AI_Race.h"

int ArrayGetCount1BB0D0(void *list);          // 0x001BB0D0: number of elements
void *ArrayGetElement1BB098(void *list, int i); // 0x001BB098: element i

int AI_Race::GetFieldA0()
{
    return mFieldA0;
}

void AI_Race::SetFieldA0(int v)
{
    mFieldA0 = v;
}

int AI_Race::GetFieldD0()
{
    return mFieldD0;
}

int AI_Race::GetFieldB0()
{
    return mFieldB0;
}

f32 AI_Race::GetFieldA4()
{
    return mFieldA4;
}

void AI_Race::SetFieldA4(f32 v)
{
    mFieldA4 = v;
}

f32 AI_Race::GetFieldA8()
{
    return mFieldA8;
}

void AI_Race::AddFieldA8(f32 v)
{
    mFieldA8 += v;
}

void AI_Race::SetFieldA8(f32 v)
{
    mFieldA8 = v;
}

void *AI_Race::GetFieldC4()
{
    return mListC4;
}

u8 AI_Race::GetStateC8()
{
    return mStateC8;
}

void AI_Race::NextStateC8()
{
    mPrevStateC9 = mStateC8;
    mStateC8++;
}

void AI_Race::SetStateC8(u8 s)
{
    mPrevStateC9 = mStateC8;
    mStateC8 = s;
}

u8 AI_Race::GetStateCA()
{
    return mStateCA;
}

void AI_Race::SetStateCA(u8 s)
{
    mPrevStateCB = mStateCA;
    mStateCA = s;
}

int AI_Race::GetFieldCC()
{
    return mFieldCC;
}

void AI_Race::SetFieldCC(int v)
{
    mFieldCC = v;
}

Vec4f *AI_Race::GetPlayerRow2()
{
    return &func_00122D08(mPlayer110)->row[2];
}

Mat4x4f *AI_Race::GetPlayerMatrix()
{
    return func_00122D08(mPlayer110);
}

Vec4f * AI_Race::GetPlayerRow1()
{
    return &func_00122D08(mPlayer110)->row[1];
}

Vec4f * AI_Race::GetPlayerRow0()
{
    return &func_00122D08(mPlayer110)->row[0];
}

Player * AI_Race::GetPlayer110()
{
    return mPlayer110;
}

f32 AI_Race::GetField13C()
{
    return mField13C;
}

f32 AI_Race::GetField134()
{
    return mField134;
}

f32 AI_Race::GetField138()
{
    return mField138;
}

Vec3f * AI_Race::GetPtr11C()
{
    return &mField11C;
}

f32 * AI_Race::GetPtrE0()
{
    return mFieldE0;
}

void AI_Race::SetFieldE0(int i, f32 v)
{
    mFieldE0[i] = v;
}

int AI_Race::GetFieldDC()
{
    return mFieldDC;
}

int AI_Race::GetFieldF4()
{
    return mFieldF4;
}

int AI_Race::GetField148()
{
    return mField148;
}

void * AI_Race::GetPtrF8()
{
    return mBlockF8;
}

f32 AI_Race::GetFieldAC()
{
    return mFieldAC;
}

void AI_Race::SetFieldAC(f32 v)
{
    mFieldAC = v;
}

void AI_Race::AddFieldAC(f32 v)
{
    mFieldAC += v;
}

f32 AI_Race::GetFieldF0()
{
    return mFieldF0;
}

void AI_Race::SetFieldF0(f32 v)
{
    mFieldF0 = v;
}

void AI_Race::AddFieldF0(f32 v)
{
    mFieldF0 += v;
}

f32 AI_Race::GetFieldB4()
{
    return mFieldB4;
}

void AI_Race::SetFieldB4(f32 v)
{
    mFieldB4 = v;
}

f32 AI_Race::GetFieldB8()
{
    return mFieldB8;
}

void AI_Race::SetFieldB8(f32 v)
{
    mFieldB8 = v;
}

f32 AI_Race::GetFieldD8()
{
    return mFieldD8;
}

void AI_Race::SetFieldD8(f32 v)
{
    mFieldD8 = v;
}

void AI_Race::SubFieldD8(f32 v)
{
    mFieldD8 -= v;
}

void AI_Race::Action122EC8()
{
    func_00122EC8(mPlayer110);
}

void AI_Race::Action10B198()
{
    func_0010B198();
}

void AI_Race::Action10BE90()
{
    func_0010BE90(mStateC8);
}

void AI_Race::Action10BF08()
{
    func_0010BF08(mStateCA);
}

void AI_Race::func_0010BC20()
{
    if (!(mFlags20 & 0x2000))
    {
        mFlags20 |= 8;
        func_00122EA8(mPlayer110);
        mFieldE0[1] = -1.0f;
    }
}

void *AI_Race::func_0010BE90(int i)
{
    if (i >= ArrayGetCount1BB0D0(mListC4))
        return 0;
    return ArrayGetElement1BB098(mListC4, i);
}

void *AI_Race::func_0010BF08(int i)
{
    return func_0010BF50(i, (void **)func_0010BE90(mStateC8));
}

void *AI_Race::func_0010BF50(int i, void **list)
{
    if (i >= ArrayGetCount1BB0D0(*list))
        return 0;
    return *(void **)ArrayGetElement1BB098(*list, i);
}

void UnkPtrList10C058::Create()
{
    mArray00 = ArrayCreate1BB0E0(4);
}

void UnkPtrList10C058::Destroy()
{
    mArray00->Destroy();
    mArray00 = NULL;
}
