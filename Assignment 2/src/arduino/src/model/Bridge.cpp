#include <Arduino.h>
#include "model/Bridge.h"
#include "serial/MsgService.h"
#include "config.h"

Bridge::Bridge() {
    this->setState(CAR_WAITING);
    this->lastStateTimeStamp = 0;
}

void Bridge::setState(CarWashingState newState) {
    // Manage timestamp based on state transitions
    if (currentState == MAINTENANCE && newState == CAR_WASHING) {
        // Restore the CAR_WASHING timestamp to the point it was interrupted by MAINTENANCE
        this->stateTimestamp = millis() - this->lastStateTimeStamp;
    } else {
        lastStateTimeStamp = this->elapsedTimeInState();
        stateTimestamp = millis();
    }
    currentState = newState;
    // Send a message with the updated state to the serial service
    MsgService.sendMsg("STATE:"+String(this->currentState));
}

CarWashingState Bridge::getState() {
    return this->currentState;
}

long Bridge::elapsedTimeInState() {
    return (millis() - this->stateTimestamp);
}