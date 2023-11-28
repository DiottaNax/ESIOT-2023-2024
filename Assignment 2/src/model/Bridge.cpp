#include <Arduino.h>
#include "model/Bridge.h"
#include "serial/MsgService.h"
#include "config.h"

Bridge::Bridge() {
    this->currentState = CAR_WAITING;
    this->lastStateTimeStamp = 0;
}

void Bridge::setState(CarWashingState newState) {
    if (currentState == MAINTENANCE && newState == CAR_WASHING) {
        stateTimestamp = lastStateTimeStamp;
    } else {
        stateTimestamp = millis();
    }

    currentState = newState;
    MsgService.sendMsg("STATE:"+this->currentState);
}

CarWashingState Bridge::getState() {
    return this->currentState;
}

long Bridge::elapsedTimeInState() {
    return (millis() - this->stateTimestamp);
}