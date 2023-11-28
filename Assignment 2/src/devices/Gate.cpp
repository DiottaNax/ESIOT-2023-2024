#include <Arduino.h>
#include <Servo.h>
#include "devices/Gate.h"

Gate::Gate(short pin) : _pin(pin) {
}

void Gate::on(){
    _servo.attach(_pin);
}

void Gate::setAngle(short angle){
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

void Gate::off(){
    _servo.detach();
}