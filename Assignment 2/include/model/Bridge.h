#ifndef __BRIDGE__
#define __BRIDGE__
#include "config.h"

/**
 * @brief Represents a bridge that tracks the state and elapsed time in the car washing process.
 *
 * The Bridge class is designed to manage the state of a car washing process and track the elapsed
 * time spent in each state. 
 */
class Bridge {
public:
    /**
     * @brief Default constructor for the Bridge class.
     *
     * Initializes the Bridge with an initial state.
     */
    Bridge();
    /**
     * @brief Get the current state of the car washing process.
     *
     * @return The current state represented by the CarWashingState enum.
     */
    CarWashingState getState();
    /**
     * @brief Set the current state of the car washing process.
     *
     * @param state The new state to set.
     */
    void setState(CarWashingState);
    /**
     * @brief Get the elapsed time in the current state.
     *
     * This function calculates and returns the time elapsed (in milliseconds)
     * since the last state transition.
     *
     * @return The elapsed time in the current state.
     */
    long elapsedTimeInState();
private:
    CarWashingState currentState; //The current state of the car washing process.
    long stateTimestamp;      //The timestamp of the current state transition.
    long lastStateTimeStamp;  //The timestamp of the last state transition.
};

#endif