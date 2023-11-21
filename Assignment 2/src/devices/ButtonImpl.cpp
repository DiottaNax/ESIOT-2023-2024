#include "devices/Button.h"

Button::Button(int pin) {
  this->pin = pin;
}

void Button::begin() {
  pinMode(pin, INPUT);
  currentState = digitalRead(pin);
  lastState = currentState;
}

bool Button::isPressed() {
  currentState = digitalRead(pin);
  return currentState == HIGH;
}

bool Button::wasPressed() {
  currentState = digitalRead(pin);
  return (currentState == HIGH) && (lastState == LOW);
}

bool Button::wasReleased() {
  currentState = digitalRead(pin);
  return (currentState == LOW) && (lastState == HIGH);
}
