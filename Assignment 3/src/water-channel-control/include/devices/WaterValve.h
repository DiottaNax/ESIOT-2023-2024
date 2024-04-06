#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"

/**
 * @brief The Gate class inherits from the ServoMotor class.
 */
class WaterValve: public ServoMotor {

public:
  /**
   * @brief Constructor for the WaterValve class.
   * @param pin The pin number to which the servo motor is connected.
   */
  WaterValve(int pin);

  /**
   * @brief Turns on the servo motor.
   */
  void on();

  /**
   * @brief Sets the angle of the servo motor to the specified value.
   * 
   * @param angle The desired angle for the servo motor.
   */
  void setAngle(short angle);

  /**
   * @brief Turns off the servo motor.
   */
  void off();
    
private:
  int pin; //Private member variable to store the pin number.
};

#endif
