#ifndef __BLINKING_TASK__
#define __BLINKING_TASK__

#include "devices/Led.h"
#include "Task.h"

/**
 * @brief Represents a task for blinking an LED with variable period.
 *
 * The BlinkingTask class is a specific implementation of the Task interface
 * for blinking an LED with variable period. 
 */
class BlinkingTask: public Task {
private:

  Led* led; //Pointer to the LED object controlled by this task.
  enum { ON, OFF} state; //Internal state to track whether the LED is ON or OFF.

public:

  /**
   * @brief Constructor for BlinkingTask.
   *
   * Inherits the base class constructor (Task).
   *
   * @param period The initial blinking period in milliseconds.
   */
  using Task::Task;
  
  /**
   * @brief Initialize the BlinkingTask with the specified LED pin.
   *
   * @param pin The pin number to which the LED is connected.
   */
  void init(int pin); 

  /**
   * @brief Perform a single iteration of the blinking task.
   *
   * This function is called on each iteration of the task and updates
   * the LED state based on the current state and period.
   */ 
  void tick();

  /**
   * @brief Change the blinking period.
   *
   * @param period The new blinking period in milliseconds.
   */
  void changePeriod(int period); 
};

#endif