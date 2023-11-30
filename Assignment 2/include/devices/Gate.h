#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include "ServoMotor.h"
#include "ServoTimer2.h"

class Gate: public ServoMotor {

public:
  Gate(int pin);

  void on();
  void setAngle(short angle);
  void off();
    
private:
  int pin; 
  ServoTimer2 motor; 
};

#endif
