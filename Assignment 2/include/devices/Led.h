#ifndef __LED__
#define __LED__

#include <Arduino.h>

/**
 * @brief Represents a class for controlling an LED.
 */
class Led {
public:
  /**
   * @brief Constructor for the Led class.
   * @param pin The pin to which the LED is connected.
   */
  Led(int pin);

  /**
   * @brief Turns on the LED.
   */
  void turnOn();

  /**
   * @brief Turns off the LED.
   */
  void turnOff();

  /**
   * @brief Sets the intensity of the LED.
   * @param intensity The intensity value (0 to 255).
   */
  void setIntensity(int intensity);

private:
  int pin; /**< The pin to which the LED is connected. */
};

#endif
