#ifndef __TEMP_SENSOR__
#define __TEMP_SENSOR__

#include <Arduino.h>

class ITemperatureSensor {
public:
    virtual int getTemp() = 0;
};

#endif