#include "kernel/Scheduler.h"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler(void){
  timerFlag = true;
}

void Scheduler::init(short basePeriod){
  this->period = basePeriod;
  timerFlag = false;
  long period = 1000l*basePeriod;
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
  while (!timerFlag){}
  timerFlag = false;

  for (int i = 0; i < nTasks; i++){
    if (this->tasks[i]->isActive()){
      if (this->tasks[i]->isPeriodic()){
        if (this->tasks[i]->updateAndCheckTime(this->period)){
          this->tasks[i]->tick();
        }
      } else {
        this->tasks[i]->tick();
      }
    }
  }
}
