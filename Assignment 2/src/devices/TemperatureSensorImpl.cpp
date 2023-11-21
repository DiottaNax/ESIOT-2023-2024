#include "TemperatureSensorImpl.h"
#include <Arduino.h>

TemperatureSensorImpl::TemperatureSensorImpl(int pin) {
    this->pin = pin;
    pinMode(this->pin,INPUT);
}

int TemperatureSensorImpl::getTemp() {
    int val = analogRead(this->pin);
    val = (val*(5000/1024))*0.1;
    return val;
}