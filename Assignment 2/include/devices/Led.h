#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led {
public:
  Led(int pin);

  void turnOn();
  void turnOff();
  void setIntensity(int intensity);

private:
  int pin;
};

#endif