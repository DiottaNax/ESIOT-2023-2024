#ifndef __PROXIMITY_SENSOR_IMPL__
#define __PROXIMITY_SENSOR_IMPL__
#include "ProximitySensor.h"

/**
 * @brief Abstract interface for a proximity sensor.
 */
class ProximitySensorImpl : public ProximitySensor {

public:
    ProximitySensorImpl(short echoPin, short triggerPin);

    float getDistance();

    void setTemperature(float temperature);
    
protected:
    float _vs = 331.5 + 0.6 * 20;
    short _echoPin;
    short _triggerPin;
};

#endif