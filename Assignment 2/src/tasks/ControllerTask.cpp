#include "tasks/ControllerTask.h"
#include "devices/Led.h"

ControllerTask::ControllerTask(BlinkingTask *blink, DistanceControlTask *distanceController, TemperatureTask *tempController) {
    this->blink = blink;
    this->distanceController = distanceController;
    this->tempController = tempController; 
    this->period = PERIOD;
    this->periodic = true;
}

void ControllerTask::init(int pinL1, int pinL3) {
    active = true;
    this->L1 = new Led(pinL1);
    this->L3 = new Led(pinL3);
    this->currentState = CAR_WAITING;
}

void ControllerTask::tick() {
    switch (this->currentState)
    {
    case CAR_WAITING:
        
        break;
    case WELCOME:
        break;
    case GATE_OPENING:
        break;
    case CAR_WASHING:
        break;
    case MANTEINANCE:
        break;
    case WASHING_COMPLETED:
        break;
    default:
        break;
    }
}