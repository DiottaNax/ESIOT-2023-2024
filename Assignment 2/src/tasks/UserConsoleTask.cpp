#include <Arduino.h>
#include "tasks/UserConsoleTask.h"
#include "devices/LCDDisplay.h"
#include "config.h"

UserConsoleTask::UserConsoleTask(Bridge *bridge) {
    _bridge = bridge;
}

void UserConsoleTask::init(){
    _display.initialize();
    _display.clear();
    for (int i = 0; i < 3; i++){
        _leds[i].turnOff();
    }
}

void UserConsoleTask::tick(){
    switch (_bridge->getState()) {
    case WELCOME:
        _display.clear();
        _display.print("Welcome", 0, 0);
        setActive(false);
        break;
    
    case GATE_OPENING:
        _display.clear();
        _display.print("Proceed to", 0, 0);
        _display.print("the Washing Area", 0, 1);
        setActive(false);
        break;

    case READY_TO_WASH:
        _display.clear();
        _display.print("Ready to Wash", 0, 0);
        setActive(false);
        break;

    default:
        _display.clear();
        break;
    }
}