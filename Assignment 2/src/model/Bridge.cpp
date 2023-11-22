#include "models/Bridge.h"
#include "config.h"
#include <Arduino.h>

Bridge::Bridge() {
    this->currentState = CAR_WAITING;
}

void Bridge::setState(CarWashingState newState) {
    this->currentState = newState;
    stateTimestamp = millis();
}

CarWashingState Bridge::getState() {
    return this->currentState;
}

long Bridge::elapsedTimeInState() {
    return (millis() - this->stateTimestamp);
}