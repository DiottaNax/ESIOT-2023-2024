#ifndef __TEMP_SENSOR__
#define __TEMP_SENSOR__

#include <Arduino.h>

/**
 * @brief Abstract base class for temperature sensors.
 *
 * This class defines the interface for temperature sensors. 
 */
class TemperatureSensor {
public:
    /**
     * @brief Pure virtual function to get the temperature reading.
     *
     * @return The temperature reading as an integer value.
     */
    virtual int getTemp() = 0;
};

#endif