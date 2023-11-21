#include <Arduino.h>
#include <Servo.h>
#include "devices/ServoMotorImpl.h"

ServoMotorImpl::ServoMotorImpl(short pin) : _pin(pin) {
}

void ServoMotorImpl::on(){
    _servo.attach(_pin);
}

void ServoMotorImpl::setAngle(short angle){
    if(_servo.attached()){
        if (angle <= 0){
            _servo.write(0);
        } else if(angle >= 180){
            _servo.write(180);
        } else{
            _servo.write(angle);
        }
    }
}