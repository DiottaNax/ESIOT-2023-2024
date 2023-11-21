#ifndef __LED__
#define __LED__

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