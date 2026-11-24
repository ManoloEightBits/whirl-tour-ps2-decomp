// IVP library TU (0x001F6FC8..0x001F7108): IVP_Controller and IVP_Controller_Independent.
#include "game/Controllers.h"

extern char data_0027B878[]; // static object returned by IVP_Controller_Independent (0x0027B878)

void IVP_Controller::core_is_going_to_be_deleted_event(void *)
{
}

f32 IVP_Controller::get_minimum_simulation_frequency()
{
    return 1.0f;
}

void IVP_Controller::reset_time()
{
}

void *IVP_Controller_Independent::get_associated_controlled_cores()
{
    return data_0027B878;
}
