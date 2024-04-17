#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "../tasks/Task.h"

#define MAX_TASKS 50

/**
 * @brief The Scheduler class manages the scheduling of tasks in a real-time system.
 */
class Scheduler {
  
  int basePeriod; /**< The base period for task scheduling */
  int nTasks; /**< The number of tasks currently registered */
  Task* taskList[MAX_TASKS]; /**< An array to hold pointers to registered tasks */

public:
  /**
   * @brief Initializes the scheduler with the given base period.
   * 
   * @param basePeriod The base period for task scheduling in milliseconds.
   */
  void init(int basePeriod);  

  /**
   * @brief Adds a task to the scheduler.
   * 
   * @param task A pointer to the task object to be added.
   * @return true if the task was successfully added, false otherwise.
   */
  virtual bool addTask(Task* task);  

  /**
   * @brief Executes the scheduler, scheduling and executing tasks as per their respective periods.
   */
  virtual void schedule();
};

#endif // __SCHEDULER__
