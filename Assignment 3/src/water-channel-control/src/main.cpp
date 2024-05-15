/**
 * ESIOT a.y. 2023/2024 - Assignment 3
 * .::Smart River Monitoring::.
 * 
 * Authors: Javid Ameri, Matilde D'Antino, Federico Diotallevi
 */

#include "tasks/ConsoleTask.h"
#include "tasks/WaterChannelControlTask.h"
#include "kernel/Scheduler.h"

Scheduler *scheduler;
WaterChannelControlTask *waterChannelControlTask;
ConsoleTask *consoleTask;

void setup() {
    Serial.begin(9600);

    waterChannelControlTask = new WaterChannelControlTask();
    consoleTask = new ConsoleTask(waterChannelControlTask);

    // Initialize the tasks
    consoleTask->init();
    waterChannelControlTask->init();

    consoleTask->setActive(true);
    waterChannelControlTask->setActive(true);
    
    // Create an instance of the scheduler and initialize it
    scheduler = new Scheduler();
    scheduler->init(100);

    scheduler->addTask(waterChannelControlTask);
    scheduler->addTask(consoleTask);
}

void loop() {
    // Run the scheduler to execute the tasks
    scheduler->schedule();
}
