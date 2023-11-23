#ifndef __BLINKING_TASK__
#define __BLINKING_TASK__

#include "devices/Led.h"
#include "Task.h"

class BlinkingTask: public Task {
private:
  Led* led;
  enum { ON, OFF} state;

public:
  using Task::Task; 
  void init(int pin);  
  void tick();
  void changePeriod(int period); 
};

#endif