#include "tasks/TemperatureTask.h"
#include "config.h"
#include "serial/MsgService.h"

TemperatureTask::TemperatureTask(int period, Bridge *controller) {
    active = false;
    periodic = true;
    this->period = period;
    this->bridge = controller;
}

void TemperatureTask::init(int pin) {
    //this->sensor = new LM35Sensor(pin);
    this->timeElapsed = 0;
    dhtSens.begin();
}

bool fatto = false;

void TemperatureTask::tick() {
    int temp = dhtSens.readTemperature(); // this->sensor->getTemp();
    if(isnan(temp)){
        Serial.println("Errore nella lettura della temperatura");
    } else{
        if (temp >= MAXTEMP && this->bridge->getState() != MAINTENANCE) {
            bridge->setState(MAINTENANCE);
        }

        MsgService.sendMsg("TEMP:" + String(temp));
    }
}