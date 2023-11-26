#ifndef __CONTROLLER_TASK__
#define __CONTROLLER_TASK__
#include "TaskWithState.h"
#include "tasks/UserConsoleTask.h"
#include "tasks/DistanceControlTask.h"
#include "tasks/TemperatureTask.h"
#include "devices/PresenceDetectorImpl.h"
#include "model/Bridge.h"
#include "serial/MsgService.h"
#include "config.h"

#define PERIOD 10

class ControllerTask : public TaskWithState {
private:
    TemperatureTask *tempController;
    PresenceDetectorImpl *presenceSensor;
    UserConsoleTask *userConsole;
    Bridge *bridge;

public:
    ControllerTask(Bridge *bridge, UserConsoleTask *userConsole, TemperatureTask *tempController, PresenceDetectorImpl *presenceSensor);
    void init();
    void tick();
};

#endif