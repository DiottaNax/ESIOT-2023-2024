#include "tasks/ControllerTask.h"
#include "config.h"
#include <avr/sleep.h>

ControllerTask::ControllerTask(Bridge *bridge, BlinkingTask *blink, TemperatureTask *tempController, PresenceDetectorImpl *presenceSensor) {
    this->blink = blink;
    this->tempController = tempController;
    this->bridge = bridge;
    this->presenceSensor = presenceSensor;
    this->period = PERIOD;
    this->periodic = true;
}

void ControllerTask::init(int pinL1, int pinL3) {
    active = true;
    this->L1 = new Led(pinL1);
    this->L3 = new Led(pinL3);
    this->bridge->setState(CAR_WAITING);
    /*attachInterrupt(digitalPinToInterrupt(PRESENCE_SENSOR), bridge->setState(WELCOME),RISING);*/
}

void ControllerTask::tick() {
    switch (this->bridge->getState()) {
    case CAR_WAITING:
        break;
    case WELCOME:
        //LCDdisplay scrive "Welcome"
        this->L1->turnOn();
        if (this->bridge->elapsedTimeInState() >= N1) {
            this->bridge->setState(GATE_OPENING);
        }
        break;
    case GATE_OPENING:
        //LCDdisplay scrive "Proceed to the Washing Area"
        this->blink->changePeriod(10);
        this->blink->setActive(true);
        //Attiva sensore di distanza e apre il gate
        break;
    case READY_TO_WASH:
        this->blink->setActive(true);
        //Disattiva il sensore di distanza e chiude il gate
        //LCDdisplay scrive "Ready To Wash"
        break;
    case CAR_WASHING:
        this->tempController->setActive(true);
        this->blink->changePeriod(50);
        this->blink->setActive(true);
        //LCDdisplay compare una barra di caricamento N3->0
        break;
    case MAINTENANCE:
        break;
    case WASHING_COMPLETED:
        this->tempController->setActive(false);
        this->blink->setActive(false);
        this->L3->turnOn();
        //LCDdisplay scrive "Washing complete, you can leave the area"
        //Attiva distanceContoller e apre la sbarra
        break;
    default:
        break;
    }
}