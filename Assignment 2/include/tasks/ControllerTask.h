#ifndef __CONTROLLER_TASK__
#define __CONTROLLER_TASK__
#include "TaskWithState.h"
#include "tasks/UserConsoleTask.h"
#include "tasks/DistanceControlTask.h"
#include "tasks/TemperatureTask.h"
#include "model/Bridge.h"
#include "serial/MsgService.h"
#include "config.h"

#define PERIOD 200

/**
 * @brief Represents a controller task coordinating temperature, user console, and distance control tasks.
 *
 * The ControllerTask class is a specific implementation of the Task interface
 * responsible for coordinating the activities of temperature control, user console interaction,
 * and distance control. It acts as the central controller for the overall system.
 */
class ControllerTask : public Task {
public:
    /**
     * @brief Constructor for ControllerTask.
     *
     * Initializes the ControllerTask with the necessary tasks and bridge.
     *
     * @param bridge Pointer to the Bridge managing state and time.
     * @param userConsole Pointer to the UserConsoleTask for user interaction.
     * @param tempController Pointer to the TemperatureTask for temperature control.
     * @param distanceController Pointer to the DistanceControlTask for distance control.
     */
    ControllerTask(Bridge *bridge, UserConsoleTask *userConsole, TemperatureTask *tempController, DistanceControlTask *distanceController);
    /**
     * @brief Initialize the ControllerTask.
     *
     * This function initializes the ControllerTask and its associated tasks.
     */
    void init();
    /**
     * @brief Perform a single iteration of the controller task.
     *
     * This function is called on each iteration of the task and coordinates
     * the activities of temperature control, user console interaction, and distance control.
     * It activates or deactivates tasks based on the state of the bridge.
     */
    void tick();

private:
    TemperatureTask *tempController;    //Pointer to the temperature control task.
    UserConsoleTask *userConsole;       //Pointer to the user console interaction task.
    DistanceControlTask *distanceController; //Pointer to the distance control task.

    Bridge *bridge;     //Pointer to the bridge managing state and time in the car washing process.
    int washingNumber = 0;  //The current washing number.
    bool washingCompleted = false;
};

#endif