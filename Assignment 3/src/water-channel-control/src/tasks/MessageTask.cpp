#include "tasks/MessageTask.h"
#include "config.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include "serial/MsgService.h"
#include "WaterChannelControlTask.h"

MessageTask::MessageTask(){
    // Creazione degli oggetti per ciascun componente hardware
    this->button(BUTTON_PIN);
    this->lcdDisplay(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
    this->waterChannelControlTask();
}

void MessageTask::init() {
    // Inizializzazione dei componenti hardware
    button.begin();
    lcdDisplay.initialize();
}

void MessageTask::tick() {
    if(MsgService.isMsgAvailable()){
        Msg *msg = MsgService.receiveMsg();
        if(msg->getContent().equals("STATE:AUTOMATIC")){
            this->waterChannelControlTask.setState(AUTOMATIC)
        }
        if(msg->getContent().equals("STATE:REMOTE")){
            this->waterChannelControlTask.setState(REMOTE)
        }
        delete(msg);
    }
    if (button.isPressed()) {
        if(waterChannelControlTask.getState() != MANUAL){
            this->waterChannelControlTask.setState(MANUAL);
        }
        else{
            this->waterChannelControlTask.setState(AUTOMATIC);
        }
    }
}