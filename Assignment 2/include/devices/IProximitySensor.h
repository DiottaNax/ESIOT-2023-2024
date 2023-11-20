#ifndef __PROXIMITY_SENSOR___
#define __PROXIMITY_SENSOR__

/**
 * @brief Abstract interface for a proximity sensor.
 * The temperature of the environment is by default set to 20 degrees Celsius.
 */
class IProximitySensor
{
public:
    /**
     * @brief Constructor for the ProximitySensor class.
     *
     * Initializes a proximity sensor with the specified pin.
     *
     * @param pin The pin to which the proximity sensor is connected.
     */
    IProximitySensor(short pin);

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
protected:
    /**
     * Speed of sound, influenced by temperature.
     */
    float _vs = 331.5 + 0.6 * 20;
    /**
     * Pin to which the proximity sensor is connected.
     */
    short _pin;
};

#endif