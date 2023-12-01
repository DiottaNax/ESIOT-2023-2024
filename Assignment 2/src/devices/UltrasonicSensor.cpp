#include <Arduino.h>
#include "devices/UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(short echoPin, short triggerPin) : echoPin(echoPin), triggerPin(triggerPin) {
    pinMode(echoPin, INPUT);
    pinMode(triggerPin, OUTPUT);
}

float UltrasonicSensor::getDistance() {
    // sending impulse
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(3);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin, LOW);

    // receiving echo
    float tMicros = pulseIn(echoPin, HIGH);
    // converting time from us to s
    float t = tMicros / 1000.0 / 1000.0 / 2;
    return t * vs;
}

void UltrasonicSensor::setTemperature(float temperature) {
    vs = 331.5 + 0.6 * temperature;
}