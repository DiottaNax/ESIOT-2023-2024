#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include <Servo.h>
#include "ServoMotor.h"

class ServoMotorImpl : ServoMotor{

private:
    Servo _servo;
    short _pin;

public:
    ServoMotorImpl(short pin);
    void on();
    void setAngle(short angle);
    void off();
};

#endif