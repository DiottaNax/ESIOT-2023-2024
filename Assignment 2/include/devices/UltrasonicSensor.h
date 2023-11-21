#ifndef __ULTRASONIC_SENSOR__
#define __ULTRASONIC_SENSOR__
#include "ProximitySensor.h"

/**
 * @brief Abstract interface for a proximity sensor.
 */
class UltrasonicSensor : public ProximitySensor {

public:
    UltrasonicSensor(short echoPin, short triggerPin);

    float getDistance();

    void setTemperature(float temperature);
    
protected:
    float _vs = 331.5 + 0.6 * 20;
    short _echoPin;
    short _triggerPin;
};

#endif