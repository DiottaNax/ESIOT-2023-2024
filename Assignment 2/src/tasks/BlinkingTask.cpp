#include "tasks/BlinkingTask.h"
#include "devices/Led.h"

void BlinkingTask::init(int pin) {
    this->active = true;
    this->timeElapsed = 0;
    this->led = new Led(pin);
    this->led->setIntensity(LOW);
    this->state = OFF;
}

void BlinkingTask::tick() {
    switch(this->state) {
        case ON:
            this->led->turnOn();
            state = ON; 
            break;
        case OFF:
            this->led->turnOff();
            state = OFF;
            break;
    }
}