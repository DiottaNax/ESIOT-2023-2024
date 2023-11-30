#include <Arduino.h>
#include "model/Bridge.h"
#include "serial/MsgService.h"
#include "config.h"

Bridge::Bridge() {
    this->setState(CAR_WAITING);
    this->lastStateTimeStamp = 0;
}

void Bridge::setState(CarWashingState newState) {
    if (currentState == MAINTENANCE && newState == CAR_WASHING) {
        this->stateTimestamp = millis() - this->lastStateTimeStamp;
    } else {
        lastStateTimeStamp = this->elapsedTimeInState();
        stateTimestamp = millis();
    }
    currentState = newState;
    MsgService.sendMsg("STATE:"+String(this->currentState));
}

CarWashingState Bridge::getState() {
    return this->currentState;
}

long Bridge::elapsedTimeInState() {
    return (millis() - this->stateTimestamp);
}