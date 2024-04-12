/**
 * ESIOT a.y. 2023/2024 - Assignment 3
 *
 *    .::Smart River Monitoring::.
 *
 *  @authors Javid Ameri, Matilde D'Antino, Federico Diotallevi :3
 *
 */

#include "main.h"
#include "tasks/ConsoleTask.h"
#include "tasks/WaterChannelControlTask.h"

main::main(){
  this->waterChannelControlTask();
  this->consoleTask(&waterChannelControlTask);
}

void main::setup() {
    consoleTask.init();
    waterChannelControlTask.init();
    
}

void main::loop() {
    consoleTask.tick();
    if(waterChannelControlTask.isActive()){
      waterChannelControlTask.tick();
    }
}

