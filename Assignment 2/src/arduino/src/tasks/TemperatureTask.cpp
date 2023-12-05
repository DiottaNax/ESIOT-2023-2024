#include "tasks/TemperatureTask.h"
#include "config.h"
#include "serial/MsgService.h"

TemperatureTask::TemperatureTask(int period, Bridge *controller) {
    active = false;
    periodic = true;
    this->period = period;
    this->bridge = controller;
}

void TemperatureTask::init() {
    this->timeElapsed = 0;
    dhtSens.begin();
}

void TemperatureTask::tick() {
    int temp = dhtSens.readTemperature(); 
    if(isnan(temp)){
        Serial.println("Errore nella lettura della temperatura");
    } else{
        // Check if the temperature exceeds the maximum allowed and transition to MAINTENANCE state
        if (temp >= MAXTEMP && this->bridge->getState() != MAINTENANCE) {
            bridge->setState(MAINTENANCE);
        }

        // Send temperature reading to the communication channel
        MsgService.sendMsg("TEMP:" + String(temp));
    }
}