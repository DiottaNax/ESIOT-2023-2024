#include "tasks/ConsoleTask.h"
#include "config.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include "serial/MsgService.h"
#include "tasks/WaterChannelControlTask.h"

// Constructor
ConsoleTask::ConsoleTask(WaterChannelControlTask* ptrWaterChannelControlTask) {
    this->periodic = true;
    this->period = 150;
    // Assign the pointer to the WaterChannelControlTask object
    this->waterChannelControlTask = ptrWaterChannelControlTask;
}

// Initialization function
void ConsoleTask::init() {
    this->waterChannelControlTask->setState(AUTOMATIC); // Set the initial state to AUTOMATIC
    lcdDisplay.initialize();
    this->lcdDisplay.clear();
    this->lcdDisplay.print("AUTOMATIC", 0 , 0); // Set initial display message
    Serial.println("start");
}

// Task execution function
void ConsoleTask::tick() {
    // Check if the button was pressed
    //Serial.println("tick"); // DEBUG
    if (button.wasPressed()) {

        if(this->waterChannelControlTask->getState() != MANUAL){
            // Switch to MANUAL state
            this->waterChannelControlTask->setState(MANUAL);
            MsgService.sendMsg("MODE:MANUAL");
            // Clear the LCD display and print MANUAL mode
            this->lcdDisplay.clear();
            this->lcdDisplay.print("MANUAL", 0 , 0);
        }
        else{
            // Switch to AUTOMATIC state
            this->waterChannelControlTask->setState(AUTOMATIC);
            // Clear the LCD display and print AUTOMATIC mode
            MsgService.sendMsg("MODE:AUTO");
            this->lcdDisplay.clear();
            this->lcdDisplay.print("AUTOMATIC", 0 , 0);
        }
    }
}
