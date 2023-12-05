#include "devices/Led.h"

Led::Led(int pin) {
  this->pin = pin;
  pinMode(pin, OUTPUT);
}

void Led::turnOn() {
  digitalWrite(pin, HIGH);
}

void Led::turnOff() {
  digitalWrite(pin, LOW);
}