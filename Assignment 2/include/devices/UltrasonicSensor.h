#ifndef __ULTRASONIC_SENSOR__
#define __ULTRASONIC_SENSOR__
#include "ProximitySensor.h"

/**
 * @brief Abstract interface for a proximity sensor.
 */
class UltrasonicSensor : public ProximitySensor {
public:
    /**
     * @brief Constructor for the UltrasonicSensor class.
     *
     * @param echoPin The pin to which the echo signal wire of the sensor is connected.
     * @param triggerPin The pin to which the trigger signal wire of the sensor is connected.
     */
    UltrasonicSensor(short echoPin, short triggerPin);
    /**
     * @brief Retrieves the distance measured by the proximity sensor.
     *
     * @return The measured distance.
     */
    float getDistance();
    /**
     * @brief Sets the ambient temperature for the sensor.
     *
     * @param temperature The ambient temperature in degrees Celsius.
     */
    void setTemperature(float temperature);
    
protected:
    float vs = 331.5 + 0.6 * 20; //Speed of sound at sea level, used for distance calculations.
    short echoPin;     //Pin to which the echo signal wire of the sensor is connected.
    short triggerPin;  //Pin to which the trigger signal wire of the sensor is connected.
};

#endif