#include "Arduino.h"
#include "devices/Gate.h"

Gate::Gate(int pin){
  this->pin = pin;  
} 

void Gate::on(){
  // updated values: min is 544, max 2400 (see ServoTimer2 doc)
  motor.attach(pin); //, 544, 2400);    
}

void Gate::setAngle(short angle){
	if (angle > 180){
		angle = 180;
	} else if (angle < 0){
		angle = 0;
	}
  // 750 -> 0, 2250 -> 180 
  // 750 + angle*(2250-750)/180
  // updated values: min is 544, max 2400 (see ServoTimer2 doc)
  float coeff = (2400.0 - 544.0) / 180;
  motor.write(544 + angle * coeff);              
}

void Gate::off(){
  motor.detach();    
}
