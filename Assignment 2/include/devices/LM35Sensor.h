#ifndef __TEMP_SENSOR_IMPL__
#define __TEMP_SENSOR_IMPL__
#include "ITemperatureSensor.h"

/**
 * @brief Concrete implementation of the ITemperatureSensor interface for LM35 temperature sensor. 
 */
class LM35Sensor : public TemperatureSensor{

private:

    int pin; //The analog pin connected to the LM35 sensor.

public:

    /**
     * @brief Constructor for LM35Sensor.
     *
     * Initializes the LM35Sensor with the specified analog pin.
     *
     * @param pin The analog pin connected to the LM35 sensor.
     */
    LM35Sensor(int pin);

    /**
     * @brief Get the temperature reading from the LM35 sensor.
     *
     * @return The temperature reading as an integer value.
     */
    int getTemp();
};

#endif