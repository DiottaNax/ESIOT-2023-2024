#include "tasks/WaterChannelControlTask.h"
#include "config.h"
#include "devices/WaterValve.h"
#include "serial/MsgService.h"

WaterChannelControlTask::WaterChannelControlTask(){
    // Creazione degli oggetti per ciascun componente hardware
    this->waterValve(VALVE_PIN);
}

void WaterChannelControlTask::init() {
    // Inizializzazione dei componenti hardware
    waterValve.on();
}

void WaterChannelControlTask::tick() {
    switch(this->getState()) {
        case AUTOMATIC:
            if(MsgService.isMsgAvailable()){
                Msg *msg = MsgService.receiveMsg();
                if(msg->getContent().startsWith("VALVE_OPENING:")){
                    String content = msg->getContent();
                    int valveOpening = content.substring(14).toInt(); // 14 è la lunghezza di "VALVE_OPENING:"
                    waterValve.setAngle(valveOpening);
                }
                delete(msg);
            }
            break;
        case MANUAL:
            int potValue = analogRead(potPin);
            int angle = map(potValue, 0, 1023, 0, 180);     // Map the potentiometer value (0-1023) to the desired angle range (0-180)
            waterValve.setAngle(angle);
            break;
    }
}