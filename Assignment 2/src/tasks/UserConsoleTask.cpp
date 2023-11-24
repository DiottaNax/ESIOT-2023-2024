#include <Arduino.h>
#include "tasks/UserConsoleTask.h"
#include "config.h"

UserConsoleTask::UserConsoleTask(Bridge *bridge, BlinkingTask *tBlinking) {
    _bridge = bridge;
    _tBlinking = tBlinking;
    _timeStamp = 0;
}

void UserConsoleTask::init(){
    _display.initialize();
    _tBlinking->init(PIN_LED2);
    for (int i = 0; i < 3; i++){
        _leds[i].turnOff();
    }
}

int UserConsoleTask::getWashingPercentage(){
    return ((float)_bridge->elapsedTimeInState()) / N3 * 100;
}

void UserConsoleTask::makeTextScroll(){
    if (_bridge->elapsedTimeInState() - _timeStamp >= SLIDING_PERIOD) {
        Serial.println("Slided");
        _timeStamp = _bridge->elapsedTimeInState();
        _display.scrollToLeft();
    }
}

void UserConsoleTask::tick(){

    if(!_justChangedState && _bridge->elapsedTimeInState() < TICK_PERIOD){
        _display.clear();
        _justChangedState = true;
    }

    switch (_bridge->getState()) {
    case WELCOME:
        _leds[0].turnOn();
        _display.print("Welcome", 0, 0);
        setActive(false);
        break;
    
    case GATE_OPENING:
        _leds[0].turnOff();
        _display.print("Proceed to", 0, 0);
        _display.print("the Washing Area", 0, 1);
        _tBlinking->changePeriod(100);
        _tBlinking->setActive(true);
        setActive(false);
        break;

    case READY_TO_WASH:
        if(_justChangedState){
            _display.clear();
            _leds[1].turnOn();
            _display.print("Ready to Wash", 0, 0);
        }

        if(_button.isPressed()){
            _bridge->setState(CAR_WASHING);
        }
        
        break;

    case CAR_WASHING:
        _display.print("Washing process:", 0, 0);
        _display.print(String(getWashingPercentage()) + "%", 0, 1);
        if(getWashingPercentage() >= 100){
            setActive(false);
        }
        break;
    
    case WASHING_COMPLETED:
        if (_justChangedState) {
            _timeStamp = SLIDING_PERIOD;
            _display.print("Washing completed,", 0, 0);
            _display.print("you can leave the area", 0, 1);
            _leds[1].turnOff();
            _leds[2].turnOn();
        }

        makeTextScroll();

        break;
    
    case MAINTENANCE:
        if (_justChangedState) {
            _timeStamp = SLIDING_PERIOD;
            _display.print("Dectected a Problem", 0, 0);
            _display.print(" - Please Wait", 0, 1);
        }

        makeTextScroll();

        break;

    case CAR_WAITING:
        _leds[2].turnOff();
        break;

    default:
        _display.clear();
        setActive(false);
        break;
    }

    _justChangedState = false;

    if(!isActive()){
        _justChangedState = true;
        _timeStamp = 0;
    }
}