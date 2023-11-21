#include "devices/PresenceDetectorImpl.h"
#include <Arduino.h>

PresenceDetectorImpl::PresenceDetectorImpl(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

boolean PresenceDetectorImpl::isDetected() {
    boolean read = digitalRead(this->pin);
    if (read == HIGH) {
        return true;
    } else {
        return false;
    }
}
