#include "kernel/Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

// Timer interrupt handler function
void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(short basePeriod){
  this->period = basePeriod;
  timerFlag = false;
  long period = 1000l*basePeriod; // Convert base period to milliseconds
  Timer1.initialize(period);
  Timer1.attachInterrupt(timerHandler);
  nTasks = 0;
}

void Scheduler::addTask(Task* task){
  if (nTasks < MAXTASKS-1){
    this->tasks[nTasks] = task;
    nTasks++;
  }
}
  
void Scheduler::schedule(){   
  while (!timerFlag){}  // Wait for the timer flag to be set
  timerFlag = false;    // Reset the timer flag

  // Iterate through the tasks and execute them if active
  for (int i = 0; i < nTasks; i++){
    if (this->tasks[i]->isActive()){
      if (this->tasks[i]->isPeriodic()){
        // Check if it's time to execute a periodic task
        if (this->tasks[i]->updateAndCheckTime(this->period)){
          this->tasks[i]->tick(); // Execute the task
        }
      } else {
        // Execute the non-periodic task
        this->tasks[i]->tick();
      }
    }
  }
}
