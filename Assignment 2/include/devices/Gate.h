#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include <Servo.h>
#include "ServoMotor.h"

/**
 * @brief Implementation of the ServoMotor interface for controlling a gate using Servo library.
 */
class Gate : public ServoMotor{

private:
    Servo _servo; // Servo object to control the motor.
    short _pin;   // The Arduino pin to which the Servo motor is connected.

public:
    /**
     * @brief Constructor for the Gate class.
     *
     * @param pin The Arduino pin to which the Servo motor is connected.
     */
    Gate(short pin);
    void on();
    void setAngle(short angle);
    void off();
};

#endif