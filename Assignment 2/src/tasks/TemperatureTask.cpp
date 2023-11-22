#include "tasks/TemperatureTask.h"
#include "config.h"

TemperatureTask::TemperatureTask(int period, Bridge *controller) {
    active = false;
    periodic = true;
    this->period = period;
    this->bridge = controller;
}

void TemperatureTask::init(int pin) {
    this->sensor = new LM35Sensor(pin);
    this->active = true;
    this->timeElapsed = 0;
}

void TemperatureTask::tick() {
    if (this->sensor->getTemp() >= MAXTEMP) {
        bridge->setState(MANTEINANCE);
    }
}