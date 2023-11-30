#include <Arduino.h>
#include "model/Bridge.h"
#include "serial/MsgService.h"
#include "config.h"

Bridge::Bridge() {
    this->currentState = CAR_WAITING;
    this->lastStateTimeStamp = 0;
}

void Bridge::setState(CarWashingState newState) {
    if (currentState == MAINTENANCE) {
        this->stateTimestamp = this->lastStateTimeStamp;
        Serial.println("elapsed tima stamp = "+String(stateTimestamp));
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