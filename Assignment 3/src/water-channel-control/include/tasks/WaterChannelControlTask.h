#ifndef WATER_CHANNEL_CONTROL_TASK_H
#define WATER_CHANNEL_CONTROL_TASK_H

#include "TaskWithState.h"
#include "../devices/WaterValve.h"
#include "../config.h"

/**
 * @brief The WaterChannelControlTask class represents a task responsible for controlling a water channel.
 */
class WaterChannelControlTask : public TaskWithState {
private:
    WaterValve waterValve; /**< The water valve object used for controlling the water flow */

public:
    /**
     * @brief Constructs a new WaterChannelControlTask object.
     * 
     * Initializes the water valve object.
     */
    WaterChannelControlTask();

    /**
     * @brief Initializes the WaterChannelControlTask object.
     * 
     * This function initializes the water valve.
     */
    void init();

    /**
     * @brief Performs the periodic operations of the WaterChannelControlTask.
     * 
     * This function is called periodically to handle control logic for the water channel.
     */
    void tick();
};

#endif // WATER_CHANNEL_CONTROL_TASK_H
