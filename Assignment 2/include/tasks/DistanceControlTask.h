#ifndef __DISTANCE_CONTROL_TASK__
#define __DISTANCE_CONTROL_TASK__

#include "TaskWithState.h"
#include "devices/ProximitySensor.h"
#include "devices/ServoMotor.h"
#include "ControllerTask.h"

/**
 * @brief A task responsible for distance control using a proximity sensor and a servo motor.
 *
 * The DistanceControlTask class manages the interaction between a proximity sensor,
 * a servo motor (acting as a gate), and a controller task. It monitors the distance
 * to an object using the proximity sensor and controls the gate (servo motor) based on
 * the detected distance.
 */
class DistanceControlTask : TaskWithState
{
    enum State {
        ENTERING, // State when an object is entering the monitored area.
        LEAVING   // State when an object is leaving the monitored area.
    };

private:
    long _firstTimeRegisteredMinDist; // Timestamp of the first time a minimum distance was registered.
    bool _gateOpened;                 // Flag indicating whether the gate is open.
    bool _alreadyPassedDist;          // Flag indicating if the object has already passed the minimum distance.
    ServoMotor *_gate;                // Pointer to the servo motor controlling the gate.
    ProximitySensor *_proxSensor;     // Pointer to the proximity sensor for distance measurement.
    ControllerTask *_controllerTask;  // Pointer to the controller task for coordination.

    /**
     * @brief Handles the operations related to the gate.
     *
     * This function ensures that the gate is opened if it's not already open.
     */
    void handleGate();

    /**
     * @brief Handles the distance-related operations based on specified conditions.
     *
     * This function checks conditions related to the object's distance and time
     * to determine the appropriate actions. It is called within the `tick` method.
     *
     * @param distanceCondition A boolean indicating whether the distance condition is met.
     * @param timeCondition A boolean indicating for how much time the distance condition needs to be respected.
     * @param stateToSet The next state to set in the controller task if the specified conditions are met.
     */
    void handleDistance(bool distanceCondition, bool timeCondition, CarWashingState stateToSet);

public:
    /**
     * @brief Constructor for DistanceControlTask.
     *
     * @param proxSensor Pointer to the proximity sensor.
     * @param gate Pointer to the servo motor controlling the gate.
     * @param controllerTask Pointer to the controller task.
     */
    DistanceControlTask(ProximitySensor *proxSensor, ServoMotor *gate, ControllerTask *controllerTask);

    /**
     * @brief Executes the task logic.
     *
     * This method is called periodically to perform distance control based on
     * the readings from the proximity sensor.
     */
    void tick();
};

#endif
