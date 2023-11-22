#ifndef __CONTROLLER_TASK__
#define __CONTROLLER_TASK__
#include "TaskWithState.h"
#include "tasks/BlinkingTask.h"
#include "tasks/DistanceControlTask.h"
#include "tasks/TemperatureTask.h"
#include "config.h"

#define PERIOD 50

class ControllerTask : public TaskWithState {
private:
    BlinkingTask *blink;
    DistanceControlTask *distanceController;
    TemperatureTask *tempController;
    Led *L1;
    Led *L3;
    CarWashingState currentState;

public:
    ControllerTask(BlinkingTask *blink, DistanceControlTask *distanceController, TemperatureTask *tempController);
    void init(int L1pin, int L2pin);
    void tick();
};

#endif