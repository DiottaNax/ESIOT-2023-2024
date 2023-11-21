#ifndef __TEMP_SENSOR_IMPL__
#define __TEMP_SENSOR_IMPL__
#include "ITemperatureSensor.h"

class TemperatureSensorImpl : ITemperatureSensor{
private:
    int pin;
public:
    TemperatureSensorImpl(int pin);
    virtual int getTemp() = 0;
};

#endif