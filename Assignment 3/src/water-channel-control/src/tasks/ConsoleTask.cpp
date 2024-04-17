#include "tasks/ConsoleTask.h"
#include "config.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include "serial/MsgService.h"
#include "tasks/WaterChannelControlTask.h"

// Constructor
ConsoleTask::ConsoleTask(WaterChannelControlTask* ptrWaterChannelControlTask){
    // Assign the pointer to the WaterChannelControlTask object
    this->waterChannelControlTask = ptrWaterChannelControlTask;
}

// Initialization function
void ConsoleTask::init() {
    // Initialize the hardware components
    this->waterChannelControlTask->setState(AUTOMATIC); // Set the initial state to AUTOMATIC
    button.begin(); // Initialize the button
    lcdDisplay.initialize(); // Initialize the LCD display
    this->lcdDisplay.clear(); // Clear the LCD display
    this->lcdDisplay.print("AUTOMATIC", 0 , 0); // Print message saying that the mode is initally set on AUTOMATIC
    Serial.println("start");
}

// Task execution function
void ConsoleTask::tick() {
    // Check if the button was pressed
    if (button.wasPressed()) {
        // Toggle between MANUAL and AUTOMATIC states
        if(this->waterChannelControlTask->getState() != MANUAL){
            // Switch to MANUAL state
            this->waterChannelControlTask->setState(MANUAL);
            Serial.println("manual");
            MsgService.sendMsg("MODE:MANUAL");
            // Clear the LCD display and print MANUAL mode
            this->lcdDisplay.clear();
            this->lcdDisplay.print("MANUAL", 0 , 0);
        }
        else{
            // Switch to AUTOMATIC state
            this->waterChannelControlTask->setState(AUTOMATIC);
            Serial.println("automatic");
            // Clear the LCD display and print AUTOMATIC mode
            this->lcdDisplay.clear();
            this->lcdDisplay.print("AUTOMATIC", 0 , 0);
        }
    }
}
