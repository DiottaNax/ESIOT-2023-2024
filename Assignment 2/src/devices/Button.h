#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
public:
  Button(int pin);

  void begin();
  bool isPressed();
  bool wasPressed();
  bool wasReleased();

private:
  int pin;
  bool currentState;
  bool lastState;
};

#endif