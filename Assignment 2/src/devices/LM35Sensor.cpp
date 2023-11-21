#include "devices/LM35Sensor.h"
#include <Arduino.h>

LM35Sensor::LM35Sensor(int pin) {
    this->pin = pin;
    pinMode(this->pin,INPUT);
}

int LM35Sensor::getTemp() {
    int val = analogRead(this->pin);
    val = (val*(5000/1024))*0.1;
    return val;
}