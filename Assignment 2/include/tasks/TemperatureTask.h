#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "devices/LM35Sensor.h"
#include "model/Bridge.h"
#include "Task.h"
#define MAXTEMP 20

class TemperatureTask : public Task {

public:
  TemperatureTask(int period, Bridge *bridge);  
  void init(int pin);  
  void tick();

private:
  LM35Sensor *sensor;
  Bridge *bridge;
  
};

#endif