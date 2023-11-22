#include <Arduino.h>
#include "tasks/DistanceControlTask.h"
#include "tasks/DistanceControlTask.h"
#include "config.h"

#define OPEN 180
#define CLOSED 0

DistanceControlTask::DistanceControlTask(ProximitySensor *proxSensor, ServoMotor *gate, ControllerTask *controllerTask){
    _proxSensor = proxSensor;
    _gate = gate;
    _controllerTask = controllerTask;
    _gateOpened = false;
    _alreadyPassedDist = false;
    setState(ENTERING);
    _gate->on();
    _gate->setAngle(CLOSED);
}

void DistanceControlTask::handleDistance(bool distanceCondition, bool timeCondition, CarWashingState stateToSet)
{
    // Check if the minimum distance condition is met
    if (!_alreadyPassedDist && distanceCondition) {
        _alreadyPassedDist = true;
        _firstTimeRegisteredMinDist = millis();
    } else if(_alreadyPassedDist) {
        // Reset the flag if the distance condition is not met
        if (!distanceCondition) {
            _alreadyPassedDist = false;
        } else if (timeCondition) {
            // Close the gate, turn it off, and transition to the specified state
            _gate->setAngle(CLOSED);
            _alreadyPassedDist = false;
            _gateOpened = false;
            // inverting the internal state before disactivating the task
            setState(getState() == ENTERING ? LEAVING : ENTERING);
            // Disactivating the task waiting to be activated by an outside task
            setActive(false);
            _controllerTask->setState(stateToSet);
        }
    }
}

/**
 * Opens the gate if not already opened
 */
void DistanceControlTask::handleGate() {
    if (!_gateOpened) {
        _gate->setAngle(OPEN);
        _gateOpened = true;
    }
}

void DistanceControlTask::tick()
{
    handleGate();

    // Get the current distance and time
    float distance = _proxSensor->getDistance();
    int currentTime = millis() - _firstTimeRegisteredMinDist;

    switch(state) {
        case ENTERING:
            // Handle distance conditions for entering state
            handleDistance(distance <= MINDIST, currentTime >= N2, READY_TO_WASH);
            break;

        case LEAVING:
            // Handle distance conditions for leaving state
            handleDistance(distance >= MAXDIST, currentTime >= N4, CAR_WAITING);
            break;

        default:
            break;
    }
}