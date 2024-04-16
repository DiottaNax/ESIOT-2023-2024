#ifndef __SONAR__
#define __SONAR__

const int trigSonar = 12;                 // Pin number for triggering the sonar sensor
const int echoSonar = 11;                 // Pin number for receiving echo from the sonar sensor
const float temperature = 20;             // Ambient temperature in degrees Celsius
const float vs = 331.5 + 0.6*temperature; // Speed of sound in air at the given temperature

/**
 * @brief A class representing a sonar sensor.
 */
class Sonar {
  private:
    float distance = 0.0; // Current distance measured by the sonar sensor

  public:
    /**
     * @brief Constructor.
     */
    Sonar();

    /**
     * @brief Initialize the sonar sensor.
     */
    void init();

    /**
     * @brief Get the distance measured by the sonar sensor.
     * 
     * @return The distance in centimeters.
     */
    float get_distance();
};

#endif
