#include "tasks/ControllerTask.h"
#include "config.h"
#include <avr/sleep.h>

ControllerTask::ControllerTask(Bridge *bridge, UserConsoleTask *userConsole, TemperatureTask *tempController, PresenceDetectorImpl *presenceSensor) {
    this->tempController = tempController;
    this->bridge = bridge;
    this->presenceSensor = presenceSensor;
    this->period = PERIOD;
    this->periodic = true;
    this->userConsole = userConsole;
}

void ControllerTask::init() {
    active = true;
    this->bridge->setState(CAR_WAITING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    MsgService.init();
}

void ControllerTask::tick() {
    switch (this->bridge->getState()) {
    case CAR_WAITING:
        sleep_enable();
        sleep_mode(); 
        sleep_disable();
        this->bridge->setState(WELCOME);
        break;
    case WELCOME: 
        //LCDdisplay scrive "Welcome"
        if (this->bridge->elapsedTimeInState() >= N1) {
            this->bridge->setState(GATE_OPENING);
        }
        break;
    case GATE_OPENING:
        //LCDdisplay scrive "Proceed to the Washing Area"
        //Attiva sensore di distanza e apre il gate
        break;
    case READY_TO_WASH:
        //Disattiva il sensore di distanza e chiude il gate
        //LCDdisplay scrive "Ready To Wash"
        break;
    case CAR_WASHING:
        this->tempController->setActive(true);
        //LCDdisplay compare una barra di caricamento N3->0
        break;
    case MAINTENANCE:
        if(MsgService.isMsgAvailable()){
            Msg *msg = MsgService.receiveMsg();
            if(msg->getContent().equals("MAINTENANCE:DONE")){
                bridge->setState(CAR_WASHING);
            }
            delete (msg);
        }
        break;
    case WASHING_COMPLETED:
        this->tempController->setActive(false);
        //LCDdisplay scrive "Washing complete, you can leave the area"
        //Attiva distanceContoller e apre la sbarra
        break;
    default:
        break;
    }
}