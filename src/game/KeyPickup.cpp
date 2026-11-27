#include "game/GL.h"
#include "common/libc.h"
#include "game/Pickup.h"
#include "game/CollisionListeners.h"

extern UnkKeyword data_0025A230[]; // keywords of a pickups file: "pickups", "pickup", "mesh", ... "/pickup"

u32 HashStringCRC32(const char *str);                    // 0x001B1CD0
void SendScriptEvent(u32 eventCrc, int arg1, void *arg2); // 0x001266D0
PickupDef *FindPickupDef(const char *name);              // 0x00126518
void PickupHelper11B2A0(Pickup *);                       // 0x0011B2A0
void PhysicsDestroy1F21A8(void *);                       // 0x001F21A8
void PhysicsClear1F34B0(void *, int);                    // 0x001F34B0
void PhysicsRelease1F3A70(void *);                       // 0x001F3A70
void CleanupNode194EC0(void *);                          // 0x00194EC0
void EnvObjCleanup14FB70(EnvObj *);                      // 0x0014FB70
void func_00193100(UnkNode *);                           // 0x00193100
Mat4x4f *func_0012ECC0();                                // 0x0012ECC0
void func_001F3F30(void *obj, void *a, void *b);                   // 0x001F3F30
void func_001B40A0(Mat4x4f *m, f32 angle);                         // 0x001B40A0: rotation matrix
void func_001B3EC8(Mat4x4f *out, const Mat4x4f *a, const Mat4x4f *b); // 0x001B3EC8: product
void func_001B3900(Mat4x4f *dst, const Mat4x4f *src);              // 0x001B3900: copy
void func_00192820(UnkNode *node, f32 dt);                         // 0x00192820: updates a node
void DrawModel196110(void *model);                       // 0x00196110
int func_001262B0(int id);                               // 0x001262B0
void *func_00116560(UnkObjDef *, const Vec3f *pos, const Vec4f *rot, int); // 0x00116560: creates the physics object
void func_0014FB08(EnvObj *, UnkObjDef *, int);          // 0x0014FB08
void *func_001262E0(int id);                             // 0x001262E0: model by id
void func_0012EE48(Pickup *);                            // 0x0012EE48

static inline f32 AbsF(f32 x)
{
    return __builtin_fabsf(x);
}

void Pickup::Call11B2A0()
{
    PickupHelper11B2A0(this);
}

Vec3f *Pickup::GetPos44()
{
    return &mPos44;
}

Vec3f *Pickup::GetPos50()
{
    return &mPos50;
}

int Pickup::IsState4()
{
    return mState60 == 4;
}

void Pickup::OnCollected(Player *)
{
}

void Pickup::SetCallback68(void (*callback)(int), int arg)
{
    mCallback68 = callback;
    mCallbackArg6C = arg;
}

inline Pickup::~Pickup()
{
    PhysicsDestroy1F21A8(mPhysicsObj18);
    PhysicsClear1F34B0(mPhysicsObj18, 0);
    PhysicsRelease1F3A70(mPhysicsObj18);
    if (mCount34 > 0)
    {
        for (int i = 0; i < mCount34; i++)
        {
            if (mArray3C[i] != 0)
                CleanupNode194EC0(mArray3C[i]);
        }
        if (mArray3C != 0)
            delete[] mArray3C;
    }
    if (mCount38 > 0)
    {
        for (int i = 0; i < mCount38; i++)
        {
            if (mArray40[i] != 0)
                CleanupNode194EC0(mArray40[i]);
        }
        if (mArray40 != 0)
            delete[] mArray40;
    }
    EnvObjCleanup14FB70(this);
}


void KeyPickup::Update(f32 dt)
{
    Pickup::Update(dt);
    if (mBounce88 != 0)
    {
        mHeightOffset74 += mVel80 * dt;
        mVel80 -= 9.8f * dt;
        if (mHeightOffset74 < mFloor84)
        {
            mVel80 = -mVel80 * 0.4f;
            mHeightOffset74 = mFloor84 + (mFloor84 - mHeightOffset74);
            if (AbsF(mVel80) < 0.5f)
            {
                mHeightOffset74 = mFloor84;
                mBounce88 = 0;
            }
        }
    }
}

void KeyPickup::OnCollected(Player *player)
{
    player->AddKey();
}

HealthPickup::HealthPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mObjDef14, FindPickupDef("healthpickup"))
{
}

void HealthPickup::OnCollected(Player *player)
{
    player->AddHealth(mDef70->mParam1_90);
}

ScooterPickup::ScooterPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mObjDef14, FindPickupDef("scooterpickup"))
{
    mScooterId = info->mParam10;
}

void ScooterPickup::OnCollected(Player *player)
{
    player->AddScooter(mScooterId);
}

BGMPickup::BGMPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mObjDef14, FindPickupDef("bgmpickup"))
{
    mBGMId = info->mParam10;
}

void BGMPickup::OnCollected(Player *player)
{
    player->AddBGM(mBGMId);
}

TransmitterPickup::TransmitterPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mObjDef14, FindPickupDef("transmitterpickup"))
{
}

void TransmitterPickup::OnCollected(Player *)
{
}

SpeedPickup::SpeedPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mObjDef14, FindPickupDef("speedpickup"))
{
}

void SpeedPickup::OnCollected(Player *player)
{
    PickupDef *def = mDef70;
    player->AddSpeedBoost(def->mTimeLimit8C, def->mParam1_90);
}

SpinPickup::SpinPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mObjDef14, FindPickupDef("spinpickup"))
{
}

void SpinPickup::OnCollected(Player *player)
{
    PickupDef *def = mDef70;
    player->AddSpinBoost(def->mTimeLimit8C, def->mParam1_90);
}

JumpPickup::JumpPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mObjDef14, FindPickupDef("jumppickup"))
{
}

void JumpPickup::OnCollected(Player *player)
{
    PickupDef *def = mDef70;
    player->AddJumpBoost(def->mTimeLimit8C, def->mParam1_90);
}

BalancePickup::BalancePickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mObjDef14, FindPickupDef("balancepickup"))
{
}

void BalancePickup::OnCollected(Player *player)
{
    PickupDef *def = mDef70;
    player->AddBalanceBoost(def->mTimeLimit8C, def->mParam1_90);
}

TimerPickup::TimerPickup(PickupSpawnInfo *info)
    : Pickup(&info->mPos18, info->mObjDef14, FindPickupDef("timerpickup"))
{
}

void TimerPickup::OnCollected(Player *)
{
    SendScriptEvent(HashStringCRC32("add_time"), 0, &mDef70->mTimeLimit8C);
}

void PickupDef::func_0011AD28(char *name, UnkParser *p)
{
    p->func_001C2C78("name", name);
    strncpy(mName00, name, 0x3F);
    mNumCreation5C = 0;
    mNumDestruction60 = 0;
    for (int i = 0; i < 5; i++)
    {
        mCreation64[i] = 0;
        mDestruction78[i] = 0;
    }
    mNumMeshes40 = 0;
    for (int j = 0; j < 5; j++)
        mMeshes44[j] = 0;
    mIcs58 = 0;
    mTimeLimit8C = 10.0f;
    mParam1_90 = 0.0f;
    mRegenerate94 = 0.0f;
    mRegenDelta98 = 0.0f;
    mSound9C = 0;
    int creation = 0;
    int destruction = 0;
    int n = 0;
    int done = 0;
    char buf[128];
    while (p->mEof102C == 0 && !done)
    {
        p->func_001C1D28(data_0025A230);
        switch (p->mToken14)
        {
        case 2: // mesh
            p->func_001C2C78("name", buf);
            if (mNumMeshes40 < 5)
                mMeshes44[mNumMeshes40++] = HashStringCRC32(buf);
            break;
        case 3: // ics
            p->func_001C2C78("name", buf);
            mIcs58 = HashStringCRC32(buf);
            break;
        case 4: // fountains
            p->func_001C2C78("type", buf);
            if (strcmp(buf, "creation") == 0)
            {
                creation = 1;
                n = 0;
            }
            else if (strcmp(buf, "destruction") == 0)
            {
                destruction = 1;
                n = 0;
            }
            break;
        case 6: // /fountains
            if (creation)
            {
                creation = 0;
                mNumCreation5C = n;
            }
            else if (destruction)
            {
                destruction = 0;
                mNumDestruction60 = n;
            }
            break;
        case 5: // fountain
        {
            p->func_001C2C78("name", buf);
            PickupDef *def = FindPickupDef(buf);
            if (def != 0)
            {
                if (creation)
                    mCreation64[n++] = (int)def;
                else if (destruction)
                    mDestruction78[n++] = (int)def;
            }
            break;
        }
        case 7: // settings
            p->func_001C3270("timelimit", &mTimeLimit8C);
            p->func_001C3270("param1", &mParam1_90);
            p->func_001C3270("regenerate", &mRegenerate94);
            p->func_001C3270("regendelta", &mRegenDelta98);
            break;
        case 8: // sound
            p->func_001C2C78("name", buf);
            mSound9C = HashStringCRC32(buf);
            break;
        case 9: // /pickup
            done = 1;
            break;
        default:
            p->func_001C2C10();
            break;
        }
    }
}

#ifdef NON_MATCHING
// 123 of 144 instructions match. Solved: register allocation (pos needs the do/while(0) around
// the copy to outrank the loop counter, see docs/MATCHING.md) and the order of the node fields.
// Left: the scheduler puts `i = 0` (daddu $s5) in the prologue instead of the first jal's delay
// slot, which shifts the prologue and the rot stores, and the copy into mPos50 gets $f1/$f2
// swapped for y/z. Placing the counter's initialization elsewhere does not change it.
static inline void CopyVec3(Vec3f *dst, const Vec3f *src)
{
    f32 x = src->x;
    f32 y = src->y;
    f32 z = src->z;
    dst->z = z;
    dst->y = y;
    dst->x = x;
}

Pickup::Pickup(const Vec3f *pos, UnkObjDef *objDef, PickupDef *def)
{
    Vec4f rot;
    rot.x = 0.0f;
    rot.y = 0.0f;
    rot.z = 0.0f;
    rot.w = 1.0f;
    mPhysicsObj18 = func_00116560(objDef, pos, &rot, func_001262B0(def->mIcs58));
    func_0014FB08(this, objDef, 0);
    ((IVP_Real_Object_Stub *)mPhysicsObj18)->mActorA8 = (DD_ActorInfo *)this;
    mCount1C = 0;
    for (int i = 0; i < def->mNumMeshes40; i++)
    {
        mArray20[mCount1C] = func_001262E0(def->mMeshes44[i]);
        if (mArray20[mCount1C] != 0)
            mCount1C++;
    }
    mField64 = 0;
    mState60 = 1;
    mHeightOffset74 = 0.0f;
    mField78 = def->mRegenerate94;
    mCount34 = def->mNumCreation5C;
    mCount38 = def->mNumDestruction60;
    mArray3C = 0;
    mArray40 = 0;
    do
    {
        CopyVec3(&mPos50, pos);
    } while (0);
    mField5C = objDef->field_0x3C;
    mCallback68 = 0;
    mCallbackArg6C = 0;
    mDef70 = def;
    if (def != 0)
    {
        if (mCount34 > 0)
        {
            mArray3C = new UnkNode *[def->mNumCreation5C];
            for (int j = 0; j < def->mNumCreation5C; j++)
                mArray3C[j] = 0;
            func_0011CC90(0);
        }
        if (mCount38 > 0)
        {
            mArray40 = new UnkNode *[def->mNumDestruction60];
            for (int k = 0; k < def->mNumDestruction60; k++)
                mArray40[k] = 0;
            func_0011CD80(0);
        }
    }
    func_0012EE48(this);
}
#endif

// Defined after the constructor: GCC 2.95 cannot inline them there (it calls the out-of-line
// copies, as the game does) but inlines them in func_0011B7B8 and KeyPickup's constructor.
inline void Pickup::func_0011CC90(int enable)
{
    for (int i = 0; i < mCount34; i++)
    {
        if (enable)
        {
            if (mArray3C[i] == 0)
                mArray3C[i] = func_00194DE0(mDef70->mCreation64[i]);
            if (mArray3C[i] != 0)
            {
                func_00194F40(mArray3C[i]);
                mArray3C[i]->field_0x70 = mArray3C[i]->field_0x10->field_0x4C;
            }
        }
        else if (mArray3C[i] != 0)
        {
            func_00194F90(mArray3C[i]);
        }
    }
}

inline void Pickup::func_0011CD80(int enable)
{
    for (int i = 0; i < mCount38; i++)
    {
        if (enable)
        {
            if (mArray40[i] == 0)
                mArray40[i] = func_00194DE0(mDef70->mDestruction78[i]);
            if (mArray40[i] != 0)
            {
                func_00194F40(mArray40[i]);
                mArray40[i]->field_0x70 = mArray40[i]->field_0x10->field_0x4C;
            }
        }
        else if (mArray40[i] != 0)
        {
            func_00194F90(mArray40[i]);
        }
    }
}

// After func_0011CC90 and func_0011CD80, which it inlines.
void Pickup::Update(f32 dt)
{
    int i = 0;
    Vec4f pos;
    Vec4f rot;
    func_001F3F30(mPhysicsObj18, &rot, &pos);
    Vec3f *p = &mPos44;
    p->x = pos.x;
    p->y = pos.y;
    p->z = pos.z;
    Mat4x4f turn;
    func_001B40A0(&turn, -1.5707964f);
    Mat4x4f m;
    func_001B3EC8(&m, &turn, func_0012ECC0());
    m.row[3].x += p->x;
    m.row[3].y += p->y + mHeightOffset74;
    m.row[3].z += p->z;
    for (i = 0; i < mCount34; i++)
    {
        if (mArray3C[i] != 0)
        {
            func_001B3900(&mArray3C[i]->mMatrix30, &m);
            func_00192820(mArray3C[i], dt);
            if (mArray3C[i]->mFlags1C & 1)
            {
                CleanupNode194EC0(mArray3C[i]);
                mArray3C[i] = 0;
            }
        }
    }
    for (i = 0; i < mCount38; i++)
    {
        if (mArray40[i] != 0)
        {
            func_001B3900(&mArray40[i]->mMatrix30, &m);
            func_00192820(mArray40[i], dt);
            if (mArray40[i]->mFlags1C & 1)
            {
                CleanupNode194EC0(mArray40[i]);
                mArray40[i] = 0;
            }
        }
    }
    mField64 += dt;
    if (mState60 == 0)
    {
        if (mField64 > 1.0f)
        {
            mState60 = 1;
            func_0011CC90(0);
        }
    }
    else if (mState60 == 2)
    {
        if (mField64 > 1.0f)
        {
            if (mField78 > 0.0f)
            {
                mField64 = 0.0f;
                mState60 = 3;
            }
            else
                mState60 = 4;
            func_0011CD80(0);
        }
    }
    else if (mState60 == 3)
    {
        if (mField78 < mField64)
        {
            mState60 = 0;
            mField64 = 0.0f;
            mField78 += mDef70->mRegenDelta98;
            func_0011CC90(1);
        }
    }
}

void PickupDef::func_0011CAD0(const char *name)
{
    strncpy(mName00, name, 0x3F);
    mNumCreation5C = 0;
    mNumDestruction60 = 0;
    for (int i = 0; i < 5; i++)
    {
        mCreation64[i] = 0;
        mDestruction78[i] = 0;
    }
    mNumMeshes40 = 0;
    for (int j = 0; j < 5; j++)
        mMeshes44[j] = 0;
    mSound9C = 0;
    mIcs58 = 0;
    mParam1_90 = 0.0f;
    mRegenerate94 = 0;
    mRegenDelta98 = 0;
    mTimeLimit8C = 10.0f;
}

// Collision callback of pickups (DD_CollisionCallback; its address sits in a data table).
void func_0011CEB8(IVP_Real_Object_Stub *self, IVP_Real_Object_Stub *other, u32, IVP_Event_Collision *)
{
    Pickup *pickup = (Pickup *)self->mActorA8;
    Player *player = (Player *)other->mActorA8;
    if ((u32)pickup->mState60 < 2)
    {
        pickup->OnCollected(player);
        pickup->func_0011B7B8();
    }
}

// Has to be a separate inline function taking the pickup: written in place, GCC schedules the
// mDef70 reload after the constructor's this, and the registers differ from the game.
static inline void SpawnCollectEffect(Pickup *p)
{
    if (p->mDef70->mSound9C != 0)
        (new UnkEffect(p->mDef70->mSound9C, &p->mPos44, 0, 20.0f, 1.0f, 1.0f))->func_001419A0(1);
}

void Pickup::func_0011B7B8()
{
    if (mState60 == 4 || mState60 == 2)
        return;
    if (mCallback68 != 0)
        mCallback68(mCallbackArg6C);
    mState60 = 2;
    mField64 = 0;
    func_0011CD80(1);
    SpawnCollectEffect(this);
}

KeyPickup::KeyPickup(const Vec3f *pos)
    : Pickup(pos, (UnkObjDef *)FindPickupDef("objkey"), FindPickupDef("keypickup"))
{
    mState60 = 0;
    func_0011CC90(1);
    mVel80 = 7.0f;
    mFloor84 = 1.0f;
    mHeightOffset74 = 1.0f;
    mBounce88 = 1;
}

// The position must come in through a pointer parameter: x is then addressed from the pickup and
// y/z through the pointer, as in the game.
static inline void TranslateTo(const Vec3f *pos, Pickup *p)
{
    glTranslatef(pos->x, pos->y + p->mHeightOffset74, pos->z);
}

void PickupHelper11B2A0(Pickup *p)
{
    for (int i = 0; i < p->mCount34; i++)
        if (p->mArray3C[i] != 0)
            func_00193100(p->mArray3C[i]);
    for (int j = 0; j < p->mCount38; j++)
        if (p->mArray40[j] != 0)
            func_00193100(p->mArray40[j]);
    if ((u32)p->mState60 < 2)
    {
        for (int k = 0; k < p->mCount1C; k++)
        {
            glPushMatrix();
            TranslateTo(&p->mPos44, p);
            glMultMatrixf(&func_0012ECC0()->row[0].x);
            DrawModel196110(p->mArray20[k]);
            glPopMatrix();
        }
    }
}
