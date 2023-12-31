#ifndef __USER_CONSOLE_TASK__
#define __USER_CONSOLE_TASK__

#define SLIDING_PERIOD 1000
#define TICK_PERIOD 100

#include "tasks/Task.h"
#include "tasks/BlinkingTask.h"
#include "model/Bridge.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include "devices/Button.h"
#include "devices/Led.h"

/**
 * @brief Represents a task for user interaction and display control.
 *
 * The UserConsoleTask class is a specific implementation of the Task interface
 * responsible for managing user interaction through buttons and displaying
 * relevant information on an LCD display. It also interacts with a BlinkingTask
 * to control blinking LEDs.
 */
class UserConsoleTask : public Task {
private:
    bool justChangedState; //A flag indicating whether the state has just changed.

    Bridge *bridge; //Pointer to the Bridge managing state and time.
    BlinkingTask *tBlinking; //Pointer to the BlinkingTask controlling blinking LED.

    LCDDisplay display = LCDDisplay(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN); //The LCD display object.
    Button button = Button(BUTTON_PIN); //The button object for user interaction.
    Led leds[3] = {Led(PIN_LED1), Led(PIN_LED2), Led(PIN_LED3)}; //Array of LED objects.

    /**
     * @brief Get the percentage of car washing completion.
     *
     * @return The percentage of car washing completion.
     */
    int getWashingPercentage();

public:
    /**
     * @brief Constructor for UserConsoleTask.
     *
     * Initializes the UserConsoleTask with the specified Bridge and BlinkingTask.
     *
     * @param bridge Pointer to the Bridge managing state and time.
     * @param tBlinking Pointer to the BlinkingTask controlling blinking LEDs.
     */
    UserConsoleTask(Bridge *bridge, BlinkingTask* tBlinking);
    /**
     * @brief Initialize the UserConsoleTask and associated devices.
     */
    void init();
    /**
     * @brief Perform a single iteration of the user console task.
     *
     * This function is called on each iteration of the task and manages user
     * interaction, updates the display, and controls the BlinkingTask.
     */
    void tick();
    /**
     * @brief Resets the UserConsoleTask by turning off LEDs and clearing the display.
     */
    void reset();
};

#endif