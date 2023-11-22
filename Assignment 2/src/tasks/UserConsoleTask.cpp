#include <Arduino.h>
#include "tasks/UserConsoleTask.h"
#include "config.h"

UserConsoleTask::UserConsoleTask(Bridge *bridge, LCDDisplay *display) {
    _bridge = bridge;
    _display = display;
    _leds[0] = new Led(PIN_LED1);
    _leds[1] = new Led(PIN_LED1);
    _leds[2] = new Led(PIN_LED1);
}

void UserConsoleTask::init(){
    _display->initialize();
    _display->clear();
    for (int i = 0; i < 3; i++){
        _leds[i]->turnOff();
    }
}

void UserConsoleTask::tick(){
    switch (_bridge->getState()) {
    case WELCOME:
        _display->clear();
        _display->print("Welcome", 0, 0);
        setActive(false);
        break;
    
    case GATE_OPENING:
        _display->clear();
        _display->print("Proceed to", 0, 0);
        _display->print("the Washing Area", 0, 1);
        setActive(false);
        break;
        
    default:
        _display->clear();
        break;
    }
}