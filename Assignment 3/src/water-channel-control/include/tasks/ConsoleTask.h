#ifndef __CONSOLE_TASK_H__
#define __CONSOLE_TASK_H__

#include "Task.h"
#include "../devices/ButtonImpl.h"
#include "../devices/LCDDisplay.h"
#include "WaterChannelControlTask.h"
#include "../config.h"

/**
 * @brief The ConsoleTask class represents a task responsible for user interaction through a button and an LCD display.
 */
class ConsoleTask : public Task {
    
private:
    ButtonImpl button = ButtonImpl(BUTTON_PIN); /**< The button object for user input */
    LCDDisplay lcdDisplay = LCDDisplay(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN); /**< The LCD display object for visual feedback */
    WaterChannelControlTask *waterChannelControlTask; /**< Pointer to the WaterChannelControlTask for coordinating actions */

public:
    /**
     * @brief Constructs a new ConsoleTask object.
     * 
     * @param ptrWaterChannelControlTask Pointer to the WaterChannelControlTask object.
     */
    ConsoleTask(WaterChannelControlTask* ptrWaterChannelControlTask);

    /**
     * @brief Initializes the ConsoleTask object.
     * 
     * This function initializes the button, LCD display, and other necessary components.
     */
    void init();

    /**
     * @brief Performs the periodic operations of the ConsoleTask.
     * 
     * This function is called periodically to handle user input and update the LCD display.
     */
    void tick();
};

#endif // __CONSOLE_TASK_H__