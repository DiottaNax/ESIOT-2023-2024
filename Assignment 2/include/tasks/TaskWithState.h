#include <Arduino.h>
#ifndef __TASK_WITH_STATE__
#define __TASK_WITH_STATE__

#include "Task.h"

/**
 * @brief Represents a task with state that tracks the elapsed time in each state.
 *
 * The TaskWithState class is a specific implementation of the Task interface
 * that includes functionality for managing and tracking the state of the task
 * and the elapsed time spent in each state.
 */
class TaskWithState : public Task {
    
public:
  /**
   * @brief Default constructor for TaskWithState.
   *
   * Initializes the TaskWithState with default values.
   */
  TaskWithState() : Task(){}

  /**
   * @brief Set the current state of the task and update the state timestamp.
   *
   * @param state The new state to set.
   */
  void setState(int state){
      this->state = state;
      stateTimestamp = millis();
  }

  /**
   * @brief Get the current state of the task.
   *
   * @return The current state of the task.
   */
  int getState() {
    return this->state;
  }

  /**
   * @brief Get the elapsed time spent in the current state.
   *
   * @return The elapsed time (in milliseconds) in the current state.
   */
  long elapsedTimeInState(){
      return millis() - stateTimestamp;
  }
  
protected:

  int state;  //The current state of the task.
  long stateTimestamp; //The timestamp of the last state transition.
};

#endif