#ifndef __TEMP_SENSOR_IMPL__
#define __TEMP_SENSOR_IMPL__
#include "ITemperatureSensor.h"

class LM35Sensor : public ITemperatureSensor{
private:
    int pin;
public:
    LM35Sensor(int pin);
    int getTemp();
};

#endif