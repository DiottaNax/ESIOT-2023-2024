#ifndef __PROXIMITY_SENSOR__
#define __PROXIMITY_SENSOR__

/**
 * @brief Abstract interface for a proximity sensor.
 */
class ProximitySensor {
    /**
     * @brief Retrieves the distance measured by the proximity sensor.
     *
     * @return The measured distance.
     */
    virtual float getDistance() = 0;

    /**
     * @brief Sets the ambient temperature for the sensor.
     *
     * @param temperature The ambient temperature in degrees Celsius.
     */
    virtual void setTemperature(float temperature) = 0;
};

#endif