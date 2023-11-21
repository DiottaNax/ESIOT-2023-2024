#ifndef __CONTROLLER_TASK__
#define __CONTROLLER_TASK__
#include "TaskWithState.h"

enum class State {
    CAR_WAITING,
    WELCOME,
    GATE_OPENING,
    READY_TO_WASH,
    CAR_WASHING,
    WASHING_COMPLITED
};

class ControllerTask : TaskWithState {
    

};

#endif