#ifndef GAME_CONTROLLERS_H
#define GAME_CONTROLLERS_H

#include "common/types.h"

// IVP controller interface and the game's controllers (all RTTI class names recovered from
// SLUS_204.89). The IVP method names are from memory of the IVP API and unverified (see TODO.md);
// the slot order is confirmed by verify_vtables.py.
class IVP_Controller
{
public:
    virtual void core_is_going_to_be_deleted_event(void *core);       // slot 1: 0x001F7008
    virtual f32 get_minimum_simulation_frequency();                    // slot 2: 0x001F7010
    virtual void *get_associated_controlled_cores() = 0;               // slot 3
    virtual void reset_time();                                         // slot 4: 0x001F7020
    virtual void do_simulation_controller(void *event, void *cores) = 0; // slot 5
    virtual int get_controller_priority() = 0;                         // slot 6
    inline virtual ~IVP_Controller() {}                                // slot 7: 0x001F7028
};

class IVP_Controller_Independent : public IVP_Controller
{
public:
    virtual void *get_associated_controlled_cores();                   // slot 3: 0x001F7100
    inline virtual ~IVP_Controller_Independent() {}                    // slot 7: 0x001F7058
};

// Core data written by the controllers (an IVP core; layout from IP_PosCtrl).
struct UnkCore
{
    char pad_0x00[0x90];
    Vec3f field_0x90; // zeroed by IP_PosCtrl
    char pad_0x9C[0x14];
    Vec3f field_0xB0; // set to IP_PosCtrl::mPos0C
};

void func_001F3F30(void *obj, void *a, void *b); // 0x001F3F30 (IVP code)

// Removes a controller from a core (IVP code; called by every game controller's destructor).
void func_001FA170(IVP_Controller *controller, void *core);            // 0x001FA170
void func_001FA148(IVP_Controller *controller, void *core);            // 0x001FA148

struct UnkCtrlObj
{
    char field_0x00[0x9C];
    UnkCore *mCore9C; // 0x9C
};

// The game controllers all override the same four slots: slot 1 deletes the controller, slot 6
// returns priority 500, slot 7 is the destructor, and slot 5 (the simulation step) is not
// decompiled yet.
#define WHIRL_CONTROLLER_SLOTS(Class)                                   \
    virtual void core_is_going_to_be_deleted_event(void *core);        \
    virtual void do_simulation_controller(void *event, void *cores);   \
    virtual int get_controller_priority();                             \
    virtual ~Class();

class IP_PosCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(IP_PosCtrl) // 0x00116A10, 0x00116968, 0x00116960, 0x00116AA0
    void SetPos0C(const Vec3f *v);     // 0x001169D8
    void ClearPos0C();                 // 0x001169F8
    IP_PosCtrl(UnkCtrlObj *obj);       // 0x00116A48

    void *mObj04;     // 0x04
    UnkCore *mCore08; // 0x08
    Vec3f mPos0C;     // 0x0C
};

struct UnkCtrlSub78
{
    char pad00[0x90];
    void *mField90; // 0x90
};

class MotionCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(MotionCtrl) // 0x00117ED0, 0x00117728, 0x00117D28, 0x00117F08
    void ClearFlag04_1();              // 0x00117E78
    void SetFlag04_1();                // 0x00117E90
    void Method117EA0(const Vec4f *v); // 0x00117EA0
    void Method117F68(const Vec4f *v); // 0x00117F68
    void Method117FE8(const Vec4f *v); // 0x00117FE8

    int mFlags04;     // 0x04
    char field_0x08[0x08];
    Vec4f mVec10;     // 0x10
    Vec4f mVec20;     // 0x20
    Vec4f mVec30;     // 0x30
    Vec4f mVec40;     // 0x40
    char field_0x50[0x28];
    UnkCtrlSub78 *mField78; // 0x78
    int mField7C;     // 0x7C
    void *mCore80;    // 0x80
};

class IP_RotCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(IP_RotCtrl) // 0x00118350, 0x00118080, 0x001182F8, 0x00118418
    void func_00118300(void *arg);     // 0x00118300
    IP_RotCtrl(UnkCtrlObj *obj, f32 val); // 0x00118388

    void *mObj04;     // 0x04
    void *mCore08;    // 0x08
    int field_0x0C;
    Vec4f mQuat10;    // 0x10
    f32 mField20;     // 0x20
};

class IP_AnimCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(IP_AnimCtrl) // 0x0016F908, 0x0016F128, 0x0016F8C8, 0x0016F940
    int TestFlag04_1();                 // 0x0016F8F8

    int mFlags04;     // 0x04
    int field_0x08;
    void *mCore0C; // 0x0C
};

class MBCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(MBCtrl) // 0x0018EA78, 0x0018E9B8, 0x0018E890, 0x0018EB18
    void SetFlags04(u8 mask);      // 0x0018E898
    u8 GetFlags04();               // 0x0018E8A8
    void ClearFlags04(u8 mask);    // 0x0018E8B0
    void SetVel08(Vec3f v);        // 0x0018E8C8
    void SetPos14(Vec3f v);        // 0x0018E908
    f32 GetHorizDist18E950();      // 0x0018E950
    Vec3f *GetPtr14();             // 0x0018E970
    void AddCorePosB0(const Vec3f *v); // 0x0018E978
    MBCtrl(UnkCtrlObj *obj);       // 0x0018EAB0

    u8 mFlags04;      // 0x04: bit 0 = reset the core to mPos14 on the next step
    char pad_0x05[3];
    Vec3f mVel08;     // 0x08
    Vec3f mPos14;     // 0x14
    void *mObj20;     // 0x20
    UnkCore *mCore24; // 0x24
};

class ScootCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(ScootCtrl) // 0x00180780, 0x00180560, 0x00180690, 0x00180820
    void SetPos08(const Vec3f *v);    // 0x00180698
    void SetPos08X(f32 x);            // 0x001806C8
    void SetPos08Y(f32 y);            // 0x001806E0
    void SetPos08Z(f32 z);            // 0x001806F8
    void SetVel14(f32 x, f32 y, f32 z); // 0x00180710
    void ClearFlags04_7();            // 0x00180728
    void AddCoreVel90(const Vec3f *v); // 0x00180740
    ScootCtrl(UnkCtrlObj *obj);       // 0x001807B8

    int mFlags04;     // 0x04: bits 0..2 = set the core's x/y/z to mPos08 on the next step
    Vec3f mPos08;     // 0x08
    Vec3f mVel14;     // 0x14
    void *mObj20;     // 0x20
    UnkCore *mCore24; // 0x24
};

#endif
