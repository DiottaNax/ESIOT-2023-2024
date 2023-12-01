#include "tasks/ControllerTask.h"
#include "config.h"
#include <avr/sleep.h>

ControllerTask::ControllerTask(Bridge *bridge, UserConsoleTask *userConsole, TemperatureTask *tempController, DistanceControlTask *distanceController) {
    this->tempController = tempController;
    this->bridge = bridge;
    this->distanceController = distanceController;
    this->period = PERIOD;
    this->periodic = true;
    this->userConsole = userConsole;
}

void ControllerTask::init() {
    active = true;
    this->bridge->setState(CAR_WAITING);

    distanceController->init();
    tempController->init(LM35_PIN);
    userConsole->init();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    MsgService.init();
}

void movementInterrupt() {
    Serial.println("Movement detected");
}

void ControllerTask::tick() {
    switch (this->bridge->getState()) {
    case CAR_WAITING:
        // Attach an interrupt for the presence detection using PIR sensor
        attachInterrupt(digitalPinToInterrupt(PIR_PIN), movementInterrupt, CHANGE);
        MsgService.sendMsg("NUMBER:"+String(washingNumber));
        this->washingNumber++;
        userConsole->reset();
        delay(10);
        //sleeping
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode(); 
        sleep_disable();

        detachInterrupt(digitalPinToInterrupt(PIR_PIN));
        this->bridge->setState(WELCOME);
        break;
    case WELCOME: 
        this->userConsole->setActive(true);
        if (this->bridge->elapsedTimeInState() >= N1) {
            this->bridge->setState(GATE_OPENING);
        }
        break;
    case GATE_OPENING:
        this->userConsole->setActive(true);
        this->distanceController->setActive(true);
        break;
    case READY_TO_WASH:
        this->userConsole->setActive(true);
        break;
    case CAR_WASHING:
        this->userConsole->setActive(true);
        if (!this->tempController->isActive()) {
            this->tempController->setActive(true);
        }
        break;
    case MAINTENANCE:
        this->userConsole->setActive(true);
        if(MsgService.isMsgAvailable()){
            Msg *msg = MsgService.receiveMsg();
            if(msg->getContent().equals("DONE")){
                bridge->setState(CAR_WASHING);
            }
            delete (msg);
        }
        break;
    case WASHING_COMPLETED:
        this->userConsole->setActive(true);
        this->tempController->setActive(false);
        this->distanceController->setActive(true);
        break;
    default:
        break;
    }
}