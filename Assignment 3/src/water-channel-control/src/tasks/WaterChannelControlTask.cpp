#include "tasks/WaterChannelControlTask.h"
#include "config.h"
#include "devices/WaterValve.h"
#include "serial/MsgService.h"

WaterChannelControlTask::WaterChannelControlTask() : waterValve(VALVE_PIN){
    // Creation of objects for each hardware component
}

void WaterChannelControlTask::init() {
    // Initialization of hardware components
    waterValve.on(); // Turn on the water valve
    waterValve.setAngle(0); // Set the valve angle at 0 at the start
}

void WaterChannelControlTask::tick() {
    switch(this->getState()) {
        case AUTOMATIC:     // In automatic mode, the valve angle is controlled by a message-system
            if(MsgService.isMsgAvailable()){
                Msg *msg = MsgService.receiveMsg();
                if(msg->getContent().startsWith("VALVE_OPENING:")){
                    // If a message related to valve opening is available
                    String content = msg->getContent();
                    int valveOpening = content.substring(14).toInt(); // Extract the valve opening value from the message
                    waterValve.setAngle(valveOpening); // Set the valve angle
                }
                delete(msg); // Free the memory allocated for the message object
            }
            break;
        case MANUAL:        // In manual mode, control the valve angle using a potentiometer
            int potValue = analogRead(POT_PIN); // Read the potentiometer value
            int angle = map(potValue, 0, 1023, 0, 180); // Map the potentiometer value to the desired angle range
            waterValve.setAngle(angle); // Set the valve angle
            break;
    }
}
