#ifndef __TASK__
#define __TASK__

/**
 * @brief Represents a generic task in a time-based system.
 */
class Task {
public:
  /**
   * @brief Default constructor for a non-periodic task.
   */
  Task(){
    active = false;
    periodic = false;
  }

  /**
   * @brief Constructor for a periodic task with a specified period.
   * @param period The time period for the periodic task.
   */
  Task(int period){
      active = false;
      periodic = true;
      this->period = period;
  }

  /**
   * @brief Initializes the task, setting it to active and resetting elapsed time.
   */
  void init() {
      active = true;
      timeElapsed = 0;
  }

  /**
   * @brief Pure virtual function to be implemented by derived classes.
   */
  virtual void tick() = 0;

  /**
   * @brief Updates the elapsed time and checks if the task should execute based on its period.
   * @param basePeriod The base time period of the system.
   * @return True if the task should execute, false otherwise.
   */
  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= period){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  /**
   * @brief Checks if the task is currently active.
   * @return True if the task is active, false otherwise.
   */
  bool isActive() {
      return active;
  }

  /**
   * @brief Sets the activity status of the task and resets elapsed time.
   * @param active True to activate the task, false to deactivate.
   */
  void setActive(bool active) {
      this->active = active;
      timeElapsed = 0;
  }

  /**
   * @brief Checks if the task is periodic.
   * @return True if the task is periodic, false if it's non-periodic.
   */
  bool isPeriodic() {
      return periodic;
  }

protected:
    bool active;       /**< Indicates if the task is currently active. */
    bool periodic;     /**< Indicates if the task is periodic. */
    int period;        /**< The time period for the periodic task. */
    int timeElapsed;   /**< The time elapsed since the task was last executed. */
};

#endif