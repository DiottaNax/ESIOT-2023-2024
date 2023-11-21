#include "Led.h"

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

void Led::setIntensity(int intensity) {
  intensity = map(intensity, 0, 1023, 0, 255);
  analogWrite(pin, intensity);
}
