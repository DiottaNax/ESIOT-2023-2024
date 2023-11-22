#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "devices/LM35Sensor.h"
#include "tasks/ControllerTask.h"
#include "Task.h"
#define MAXTEMP 20

class TemperatureTask: public Task {
private:
  LM35Sensor *sensor;
  ControllerTask *controller;

public:
  TemperatureTask(int period, ControllerTask *controller);  
  void init(int pin);  
  void tick();
};

#endif