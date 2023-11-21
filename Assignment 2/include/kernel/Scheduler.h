#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "tasks/Task.h"

#define MAXTASKS 20

/**
 * @brief A simple task scheduler for managing periodic tasks.
 *
 * The Scheduler class allows you to manage a set of tasks with different
 * execution periods. Tasks are added to the scheduler, and the scheduler
 * takes care of executing them at their specified intervals.
 */
class Scheduler
{
    // An array to store tasks.
    Task *tasks[MAXTASKS];
    //The current number of tasks in the scheduler.
    short nTasks;
    // The time period for task execution in milliseconds.
    short period;

public:
    /**
     * @brief Initializes the scheduler with a specified period.
     *
     * @param period The time period for task execution in milliseconds.
     */
    void init(short period);

    /**
     * @brief Adds a task to the scheduler.
     *
     * @param task A pointer to the Task object to be added.
     */
    void addTask(Task *task);

    /**
     * @brief Executes the scheduled tasks.
     *
     * This method should be called at regular intervals to execute the
     * scheduled tasks based on their specified periods.
     */
    void schedule();
};

#endif
