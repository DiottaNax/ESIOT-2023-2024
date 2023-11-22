#ifndef __CONTROLLER_TASK__
#define __CONTROLLER_TASK__
#include "TaskWithState.h"
#include "tasks/BlinkingTask.h"
#include "tasks/DistanceControlTask.h"
#include "tasks/TemperatureTask.h"
#include "devices/PresenceDetectorImpl.h"
#include "model/Bridge.h"
#include "config.h"

#define PERIOD 50

class ControllerTask : public TaskWithState {
private:
    BlinkingTask *blink;
    TemperatureTask *tempController;
    PresenceDetectorImpl *presenceSensor;
    Led *L1;
    Led *L3;
    Bridge *bridge;

public:
    ControllerTask(Bridge *bridge, BlinkingTask *blink, TemperatureTask *tempController, PresenceDetectorImpl *presenceSensor);
    void init(int L1pin, int L2pin);
    void tick();
};

#endif