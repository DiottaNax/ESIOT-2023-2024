#include "model/Bridge.h"
#include "config.h"
#include <Arduino.h>

Bridge::Bridge() {
    this->currentState = CAR_WAITING;
    this->elapsedTimeInLastState = 0;
}

void Bridge::setState(CarWashingState newState) {
    this->currentState = newState;
    if (newState != MAINTENANCE) {
        this->elapsedTimeInLastState = this->elapsedTimeInState;
    }
    stateTimestamp = millis();
    MsgService.sendMsg("STATE:"+this->currentState);
}

CarWashingState Bridge::getState() {
    return this->currentState;
}

long Bridge::elapsedTimeInState() {
    return (millis() - this->stateTimestamp);
}

void Bridge::changeElapsedTimeInState(long time) {
    this->stateTimestamp=time;
}