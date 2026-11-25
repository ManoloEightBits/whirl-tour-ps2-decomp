#include "game/AI_Vehicle.h"

f32 AI_Vehicle::GetFieldEC()
{
    return mFieldEC;
}

void AI_Vehicle::SetFieldEC(f32 v)
{
    mFieldEC = v;
}

void AI_Vehicle::AddFieldEC(f32 v)
{
    mFieldEC += v;
}

void AI_Vehicle::SubFieldEC(f32 v)
{
    mFieldEC -= v;
}

UnkVehicleParams * AI_Vehicle::GetParams11C()
{
    return mParams11C;
}

int AI_Vehicle::GetFieldF0()
{
    return mFieldF0;
}

int AI_Vehicle::GetFieldF4()
{
    return mFieldF4;
}

int AI_Vehicle::GetField104()
{
    return mField104;
}

int * AI_Vehicle::GetPtr108()
{
    return &mField108;
}

f32 * AI_Vehicle::GetPtr10C()
{
    return &mField10C;
}

void AI_Vehicle::SetField10C(f32 v)
{
    mField10C = v;
}

void AI_Vehicle::AddField10C(f32 v)
{
    mField10C += v;
}

Vec3f * AI_Vehicle::GetPtrE0()
{
    return &mFieldE0;
}

Vec4f * AI_Vehicle::GetRow1()
{
    return &mMatrixA0.row[1];
}

Vec4f * AI_Vehicle::GetRow0()
{
    return &mMatrixA0.row[0];
}

f32 AI_Vehicle::GetParam1C()
{
    return mParams11C->mField1C;
}

f32 AI_Vehicle::GetFieldF8()
{
    return mFieldF8;
}

void AI_Vehicle::SetFieldF8(f32 v)
{
    mFieldF8 = v;
}

f32 AI_Vehicle::GetFieldFC()
{
    return mFieldFC;
}

f32 AI_Vehicle::GetField100()
{
    return mField100;
}

f32 AI_Vehicle::GetParam6C()
{
    return mParams11C->mField6C;
}
