#include <Arduino.h>
#ifndef __TASK_WITH_STATE__
#define __TASK_WITH_STATE__

#include "Task.h"

class TaskWithState : public Task {
    
public:
  TaskWithState() : Task(){}

  void setState(int state){
      this->state = state;
      stateTimestamp = millis();
  }

  int getState() {
    return this->state;
  }

  long elapsedTimeInState(){
      return millis() - stateTimestamp;
  }
  
protected:
  int state;
  long stateTimestamp;
};

#endif