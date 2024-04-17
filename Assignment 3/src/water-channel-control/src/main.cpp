/**
 * ESIOT a.y. 2023/2024 - Assignment 3
 * .::Smart River Monitoring::.
 * 
 * Authors: Javid Ameri, Matilde D'Antino, Federico Diotallevi
 */

#include "tasks/ConsoleTask.h"
#include "tasks/WaterChannelControlTask.h"
#include "kernel/Scheduler.h"

Scheduler *scheduler; // Pointer to the scheduler object
WaterChannelControlTask *waterChannelControlTask; // Pointer to the water channel control task object
ConsoleTask *consoleTask; // Pointer to the console task object

void setup() {
    Serial.begin(9600); // Initialize serial communication at 9600 baud

    // Create instances of the water channel control task and console task
    waterChannelControlTask = new WaterChannelControlTask();
    consoleTask = new ConsoleTask(waterChannelControlTask);

    // Initialize the tasks
    consoleTask->init();
    waterChannelControlTask->init();
    
    // Create an instance of the scheduler and initialize it with a base period of 50 milliseconds
    scheduler = new Scheduler();
    scheduler->init(50);

    // Add the tasks to the scheduler
    scheduler->addTask(waterChannelControlTask);
    scheduler->addTask(consoleTask);
}

void loop() {
    // Run the scheduler to execute the tasks
    scheduler->schedule();
}
