#include <Arduino.h>
#include "tasks/DistanceControlTask.h"
#include "devices/Gate.h"
#include "devices/UltrasonicSensor.h"

#define OPEN 90
#define CLOSED 0

DistanceControlTask::DistanceControlTask(Bridge *bridge){
    proxSensor = new UltrasonicSensor(ECHO_PIN, TRIGGER_PIN);
    gate = new Gate(GATE_PIN);
    this->bridge = bridge;
}

void DistanceControlTask::handleDistance(bool distanceCondition, bool timeCondition, CarWashingState stateToSet)
{
    // Check if the minimum distance condition is met
    if (!alreadyPassedDist && distanceCondition) {
        alreadyPassedDist = true;
        firstTimeRegisteredMinDist = millis();
    } else if(alreadyPassedDist) {
        // Reset the flag if the distance condition is not met
        if (!distanceCondition) {
            alreadyPassedDist = false;
        } else if (timeCondition) {
            // Close the gate, turn it off, and transition to the specified state
            gate->setAngle(CLOSED);
            alreadyPassedDist = false;
            gateOpened = false;
            // inverting the internal state before disactivating the task
            setState(getState() == ENTERING ? LEAVING : ENTERING);
            // Disactivating the task waiting to be activated by an outside task
            setActive(false);
            bridge->setState(stateToSet);
        }
    }
}

/**
 * Opens the gate if not already opened
 */
void DistanceControlTask::handleGate() {
    if (!gateOpened) {
        gate->setAngle(OPEN);
        gateOpened = true;
    }
}

void DistanceControlTask::init(){
    gateOpened = false;
    alreadyPassedDist = false;
    setState(ENTERING);
    gate->on();
    gate->setAngle(CLOSED);
}

void DistanceControlTask::tick()
{
    handleGate();

    // Get the current distance and time
    float distance = proxSensor->getDistance();
    int currentTime = millis() - firstTimeRegisteredMinDist;

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