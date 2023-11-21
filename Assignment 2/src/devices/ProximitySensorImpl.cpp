#include <Arduino.h>
#include "devices/ProximitySensorImpl.h"

ProximitySensorImpl::ProximitySensorImpl(short echoPin, short triggerPin) : _echoPin(echoPin), _triggerPin(triggerPin) {
    pinMode(_echoPin, INPUT);
    pinMode(_triggerPin, OUTPUT);
}

float ProximitySensorImpl::getDistance() {
    // sending impulse
    digitalWrite(_triggerPin, LOW);
    delayMicroseconds(3);
    digitalWrite(_triggerPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(_triggerPin, LOW);

    // receiving echo
    float tMicros = pulseIn(_echoPin, HIGH);
    // converting time from us to s
    float t = tMicros / 1000.0 / 1000.0 / 2;
    return t * _vs;
}

void ProximitySensorImpl::setTemperature(float temperature) {
    _vs = 331.5 + 0.6 * temperature;
}