#ifndef __BLINKING_TASK__
#define __BLINKING_TASK__

#include "devices/Led.h"
#include "Task.h"

class BlinkingTask: public Task {
private:
  Led* led;
  enum { ON, OFF} state;

public:
  BlinkingTask() : Task(){}
  void changePeriod(int period);  
  void init(int pin);  
  void tick();
};

#endif