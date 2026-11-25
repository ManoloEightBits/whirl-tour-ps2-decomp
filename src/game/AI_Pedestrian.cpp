#include "game/AI_Pedestrian.h"

f32 AI_Pedestrian::GetField128()
{
    return mField128;
}

void AI_Pedestrian::SetField128(f32 v)
{
    mField128 = v;
}

void AI_Pedestrian::AddField128(f32 v)
{
    mField128 += v;
}

void AI_Pedestrian::SubField128(f32 v)
{
    mField128 -= v;
}

UnkPedParams * AI_Pedestrian::GetParams17C()
{
    return mParams17C;
}

int AI_Pedestrian::GetField180()
{
    return mField180;
}

int AI_Pedestrian::GetField160()
{
    return mField160;
}

int AI_Pedestrian::GetField154()
{
    return mField154;
}

int AI_Pedestrian::GetField158()
{
    return mField158;
}

int AI_Pedestrian::GetField164()
{
    return mField164;
}

int * AI_Pedestrian::GetPtr168()
{
    return &mField168;
}

f32 * AI_Pedestrian::GetPtr16C()
{
    return &mField16C;
}

void AI_Pedestrian::SetField16C(f32 v)
{
    mField16C = v;
}

void AI_Pedestrian::AddField16C(f32 v)
{
    mField16C += v;
}

f32 AI_Pedestrian::GetField170()
{
    return mField170;
}

void AI_Pedestrian::SetField170(f32 v)
{
    mField170 = v;
}

int AI_Pedestrian::GetField13C()
{
    return mField13C;
}

int AI_Pedestrian::GetField144()
{
    return mField144;
}

int AI_Pedestrian::GetField140()
{
    return mField140;
}

int AI_Pedestrian::GetField148()
{
    return mField148;
}

f32 AI_Pedestrian::GetField14C()
{
    return mField14C;
}

Vec3f *AI_Pedestrian::GetPosition()
{
    return (Vec3f *)&mMatrixD0.row[3];
}

Vec4f *AI_Pedestrian::GetRow2()
{
    return &mMatrixD0.row[2];
}

Mat4x4f *AI_Pedestrian::GetMatrix()
{
    return &mMatrixD0;
}

Vec4f *AI_Pedestrian::GetRow1()
{
    return &mMatrixD0.row[1];
}

Vec4f *AI_Pedestrian::GetRow0()
{
    return &mMatrixD0.row[0];
}

Vec3f * AI_Pedestrian::GetPtr110()
{
    return &mField110;
}

Vec3f * AI_Pedestrian::GetPtr11C()
{
    return &mField11C;
}

f32 AI_Pedestrian::GetField138()
{
    return mField138;
}

void AI_Pedestrian::SetField138Ratio(f32 v)
{
    f32 t = mField134 / v;
    mField138 = t < 1.0f ? t : 1.0f;
}

void AI_Pedestrian::ResetField138()
{
    mField138 = 1.0f;
}

f32 AI_Pedestrian::GetSpeed04()
{
    return mParams17C->mSpeed04;
}

f32 AI_Pedestrian::GetField130()
{
    return mField130;
}

void AI_Pedestrian::SetField130(f32 v)
{
    mField130 = v;
}

f32 AI_Pedestrian::GetProbability14()
{
    return mParams17C->mProbability14;
}

f32 AI_Pedestrian::GetTimeIn18()
{
    return mParams17C->mTimeIn18;
}

f32 AI_Pedestrian::GetTimeOut1C()
{
    return mParams17C->mTimeOut1C;
}

f32 AI_Pedestrian::GetProbability20()
{
    return mParams17C->mProbability20;
}

f32 AI_Pedestrian::GetStopRange24()
{
    return mParams17C->mStopRange24;
}

f32 AI_Pedestrian::GetTime28()
{
    return mParams17C->mTime28;
}

f32 AI_Pedestrian::GetSpeed2C()
{
    return mParams17C->mSpeed2C;
}

f32 AI_Pedestrian::GetLookAtRange30()
{
    return mParams17C->mLookAtRange30;
}

int AI_Pedestrian::GetField184()
{
    return mField184;
}
