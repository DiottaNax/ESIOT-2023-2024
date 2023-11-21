#ifndef __BUTTON__
#define __BUTTON__

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