#ifndef __TEMP_SENSOR_IMPL__
#define __TEMP_SENSOR_IMPL__
#include "TemperatureSensor.h"

/**
 * @brief Concrete implementation of the TemperatureSensor interface for LM35 temperature sensor. 
 */
class LM35Sensor : public TemperatureSensor{
public:
    /**
     * @brief Constructor for LM35Sensor.
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

private:
    int pin; //The analog pin connected to the LM35 sensor.
};

#endif