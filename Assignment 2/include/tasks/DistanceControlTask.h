#ifndef __DISTANCE_CONTROL_TASK__
#define __DISTANCE_CONTROL_TASK__

#include "TaskWithState.h"
#include "devices/ProximitySensor.h"
#include "devices/ServoMotor.h"
#include "ControllerTask.h"

class DistanceControlTask : TaskWithState {
    enum State{
        ENTERING,
        LEAVING
    };

private:
    long _firstTimeRegisteredMinDist;
    float _distance;
    bool _gateOpened;
    bool _alreadyPassedDist;
    ServoMotor *_gate;
    ProximitySensor *_proxSensor;
    ControllerTask *_controllerTask;

public:
    DistanceControlTask(ProximitySensor *proxSensor, ServoMotor *gate, ControllerTask* controllerTask);
    void tick();
};

#endif