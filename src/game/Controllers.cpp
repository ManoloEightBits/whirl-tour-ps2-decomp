#include "game/Controllers.h"

// The game controllers come from several TUs (IP_PosCtrl and MotionCtrl share the one of
// DD_Event_Listener.cpp); grouped here because they are written identically.

void IP_PosCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

int IP_PosCtrl::get_controller_priority()
{
    return 500;
}

IP_PosCtrl::~IP_PosCtrl()
{
    func_001FA170(this, mCore08);
}

void MotionCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

int MotionCtrl::get_controller_priority()
{
    return 500;
}

MotionCtrl::~MotionCtrl()
{
    func_001FA170(this, mCore80);
}

void IP_RotCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

int IP_RotCtrl::get_controller_priority()
{
    return 500;
}

IP_RotCtrl::~IP_RotCtrl()
{
    func_001FA170(this, mCore08);
}

void IP_AnimCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

int IP_AnimCtrl::get_controller_priority()
{
    return 500;
}

IP_AnimCtrl::~IP_AnimCtrl()
{
    func_001FA170(this, mCore0C);
}

void MBCtrl::core_is_going_to_be_deleted_event(void *)
{
    delete this;
}

int MBCtrl::get_controller_priority()
{
    return 500;
}

MBCtrl::~MBCtrl()
{
    func_001FA170(this, mCore24);
}
