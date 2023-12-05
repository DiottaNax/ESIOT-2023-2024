#include <Arduino.h>
#include "tasks/UserConsoleTask.h"
#include "config.h"

UserConsoleTask::UserConsoleTask(Bridge *bridge, BlinkingTask *tBlinking) {
    this->bridge = bridge;
    this->tBlinking = tBlinking;
    periodic = true;
    period = 100;
}

void UserConsoleTask::init(){
    display.initialize();
    tBlinking->init(PIN_LED2);
    for (int i = 0; i < 3; i++){
        leds[i].turnOff();
    }
}

int UserConsoleTask::getWashingPercentage(){
    return ((float)bridge->elapsedTimeInState()) / N3 * 100;
}

void UserConsoleTask::reset(){
    for (int i = 0; i < 3; i++) {
        leds[i].turnOff();
    }

    period = 100;
    display.clear();
}

void UserConsoleTask::tick(){

    if(!justChangedState && bridge->elapsedTimeInState() < 2 * period){
        display.clear();
        justChangedState = true;
    }

    switch (bridge->getState()) {
    case WELCOME:
        leds[0].turnOn();
        display.print("Welcome", 0, 0);
        this->setActive(false);
        break;
    
    case GATE_OPENING:
        tBlinking->changePeriod(100);
        tBlinking->setActive(true);
        leds[0].turnOff();
        display.print("Proceed to", 0, 0);
        display.print("the Washing Area", 0, 1);
        this->setActive(false);
        break;

    case READY_TO_WASH:
        if(justChangedState){
            tBlinking->setActive(false);
            leds[1].turnOn();
            display.print("Ready to Wash", 0, 0);
            period = 50; //permits to better detect if the button is pressed
        }

        if(button.isPressed()){
            bridge->setState(CAR_WASHING);
        }
        
        break;

    case CAR_WASHING:
        if(justChangedState){
            tBlinking->changePeriod(500);
            tBlinking->setActive(true);
        }
        period = 250; //percentage increments slowlier
        display.clear();
        display.print("Washing process:", 0, 0);
        display.print(String(getWashingPercentage()) + "%", 0, 1);

        if(getWashingPercentage() >= 100){
            bridge->setState(WASHING_COMPLETED);
        }
        break;
    
    case WASHING_COMPLETED:
        if (justChangedState) {
            tBlinking->setActive(false);
            display.print("Washing completed,", 0, 0);
            display.print("you can leave the area", 0, 1);
            leds[1].turnOff();
            leds[2].turnOn();
            period = SLIDING_PERIOD; // sets the task period to the sliding period
        }
    
        display.scrollToLeft();

        break;
    
    case MAINTENANCE:
        if (justChangedState) {
            display.print("Detected a Problem", 0, 0);
            display.print(" - Please Wait", 0, 1);
            period = SLIDING_PERIOD; // sets the task period to the sliding period
        }
    
        display.scrollToLeft();

        break;

    case CAR_WAITING:
        leds[2].turnOff();
        break;

    default:
        display.clear();
        setActive(false);
        break;
    }

    justChangedState = false;
}
