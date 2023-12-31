#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "DHT.h"
#include "model/Bridge.h"
#include "Task.h"
#include "config.h"

#define DHTTYPE DHT11

/**
 * @brief Represents a task for monitoring temperature using an LM35 sensor.
 *
 * The TemperatureTask class is a specific implementation of the Task interface
 * responsible for monitoring temperature using a DHT sensor. It periodically
 * reads the temperature and updates the state in the provided Bridge only if necessary
 */
class TemperatureTask : public Task {
public:
  /**
   * @brief Constructor for TemperatureTask.
   *
   * Initializes the TemperatureTask with the specified period and Bridge.
   *
   * @param period The period at which the task should run (in milliseconds).
   * @param bridge Pointer to the Bridge managing state and time.
   */
  TemperatureTask(int period, Bridge *bridge);  
  /**
   * @brief Initialize the TemperatureTask.
   */
  void init();  
  /**
   * @brief Perform a single iteration of the temperature monitoring task.
   *
   * This function is called on each iteration of the task and is responsible for
   * reading the temperature using the DHT sensor and updating the state in the
   * Bridge only if necessary.
   */
  void tick();

private:
  Bridge *bridge;     //Pointer to the Bridge managing state and time.
  DHT dhtSens = DHT(DHT_PIN, DHTTYPE); //DHT sensor for temperature and humidity measurements.
};

#endif