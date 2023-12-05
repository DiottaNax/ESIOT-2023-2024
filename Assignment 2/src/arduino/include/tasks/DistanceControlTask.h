#ifndef DISTANCECONTROLTASK
#define DISTANCECONTROLTASK

#include "TaskWithState.h"
#include "devices/ServoMotor.h"
#include "devices/ProximitySensor.h"
#include "model/Bridge.h"
#include "config.h"

/**
 * @brief A task responsible for distance control using a proximity sensor and a servo motor.
 *
 * The DistanceControlTask class manages the interaction between a proximity sensor,
 * a servo motor (acting as a gate), and a controller task. It monitors the distance
 * to an object using the proximity sensor and controls the gate (servo motor) based on
 * the detected distance.
 */
class DistanceControlTask : public TaskWithState {
    enum State {
        ENTERING, // State when an object is entering the monitored area.
        LEAVING   // State when an object is leaving the monitored area.
    };

private:
    long firstTimeRegisteredMinDist; // Timestamp of the first time a minimum distance was registered.
    bool gateOpened;                 // Flag indicating whether the gate is open.
    bool alreadyPassedDist;          // Flag indicating if the object has already passed the minimum distance.
    
    ProximitySensor *proxSensor; // Pointer to the proximity sensor for distance measurement.
    Bridge *bridge;  // Pointer to the bridge for coordination.
    ServoMotor *gate; // Pointer to the gate
    /**
     * @brief Handles the operations related to the gate.
     *
     * This function ensures that the gate is opened if it's not already open.
     */
    void handleGate();
    /**
     * @brief Handles the distance-related operations based on specified conditions.
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
     * @param bridge Pointer to the bridge.
     */
    DistanceControlTask(Bridge *bridge);
    /**
     * @brief Initializes the DistanceControlTask.
     *
     * Resets flags, sets the initial state to ENTERING, turns on the gate, and closes it.
     */
    void init();
    /**
     * @brief Executes the distance control task logic in each tick.
     */
    void tick();
};

#endif
