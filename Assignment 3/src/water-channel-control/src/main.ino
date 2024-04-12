/**
 * ESIOT a.y. 2023/2024 - Assignment 3
 *
 *    .::Smart River Monitoring::.
 *
 *  @authors Javid Ameri, Matilde D'Antino, Federico Diotallevi :3
 *
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
    consoleTask = new ConsoleTask(&waterChannelControlTask);
    consoleTask.init();
    waterChannelControlTask.init();
    scheduler = new Scheduler();
    scheduler->init(50);
    scheduler->addTask(waterChannelControlTask);
    scheduler->addTask(consoleTask);
}

void loop() {
    scheduler->schedule();
}

