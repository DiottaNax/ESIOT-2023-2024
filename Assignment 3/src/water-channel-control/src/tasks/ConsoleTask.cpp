#include "tasks/ConsoleTask.h"
#include "config.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include "serial/MsgService.h"
#include "WaterChannelControlTask.h"
#include "config.h"

ConsoleTask::ConsoleTask(WaterChannelControlTask* ptrWaterChannelControlTask): waterChannelControlTask(ptrWaterChannelControlTask){
    // Creazione degli oggetti per ciascun componente hardware
    this->button(BUTTON_PIN);
    this->lcdDisplay(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
    this->waterChannelControlTask = &ptrWaterChannelControlTask();
}

void ConsoleTask::init() {
    // Inizializzazione dei componenti hardware
    waterChannelControlTask.setActive(true);
    this->waterChannelControlTask.setState(AUTOMATIC);
    waterChannelControlTask.setActive(false);
    button.begin();
    lcdDisplay.initialize();
    this->lcdDisplay.clear();
    this->lcdDisplay.print("MANUAL");
}

void ConsoleTask::tick() {
    if (button.isPressed()) {
        waterChannelControlTask.setActive(true);
        if(waterChannelControlTask.getState() != MANUAL){
            this->waterChannelControlTask.setState(MANUAL);
            MsgService.sendMsg("MODE:MANUAL");
            this->lcdDisplay.clear();
            this->lcdDisplay.print("MANUAL");
        }
        else{
            this->waterChannelControlTask.setState(AUTOMATIC);
            this->lcdDisplay.clear();
            this->lcdDisplay.print("MANUAL");
        }
        waterChannelControlTask.setActive(false);
    }
}