#include "devices/Button.h"

Button::Button(int pin) {
  this->pin = pin;
}

// Sync to set last and current state
void Button::sync() {
  lastState = currentState;
  currentState = digitalRead(pin);
}

void Button::begin() {
  pinMode(pin, INPUT);
  currentState = digitalRead(pin);
  lastState = currentState;
}

bool Button::isPressed() {
  sync();
  return currentState == HIGH;
}

bool Button::wasPressed() {
  sync();
  return (currentState == HIGH) && (lastState == LOW);
}

bool Button::wasReleased() {
  sync();
  return (currentState == LOW) && (lastState == HIGH);
}
