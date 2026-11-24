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

    void *mObj04;     // 0x04
    UnkCore *mCore08; // 0x08
    Vec3f mPos0C;     // 0x0C
};

class MotionCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(MotionCtrl) // 0x00117ED0, 0x00117728, 0x00117D28, 0x00117F08

    char field_0x04[0x7C];
    void *mCore80; // 0x80
};

class IP_RotCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(IP_RotCtrl) // 0x00118350, 0x00118080, 0x001182F8, 0x00118418

    int field_0x04;
    void *mCore08; // 0x08
};

class IP_AnimCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(IP_AnimCtrl) // 0x0016F908, 0x0016F128, 0x0016F8C8, 0x0016F940

    char field_0x04[0x8];
    void *mCore0C; // 0x0C
};

class MBCtrl : public IVP_Controller_Independent
{
public:
    WHIRL_CONTROLLER_SLOTS(MBCtrl) // 0x0018EA78, 0x0018E9B8, 0x0018E890, 0x0018EB18

    u8 mFlags04;      // 0x04: bit 0 = reset the core to mPos14 on the next step
    char pad_0x05[3];
    Vec3f mVel08;     // 0x08
    Vec3f mPos14;     // 0x14
    int field_0x20;
    UnkCore *mCore24; // 0x24
};

#endif
