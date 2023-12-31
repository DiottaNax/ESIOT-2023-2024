#ifndef __CONFIG__
#define __CONFIG__

#define PIR_PIN 2 //PIR PIN

//DISTANCE CONTROL TASK PIN
#define GATE_PIN 9
#define ECHO_PIN 10
#define TRIGGER_PIN 11

//USER CONSOLE TASK PIN
//DISPLAY PIN
#define RS_PIN 3
#define ENABLE_PIN 4
#define D4_PIN 5
#define D5_PIN 6
#define D6_PIN 7
#define D7_PIN 8
//BUTTON PIN
#define BUTTON_PIN 12
//LED PIN
#define PIN_LED1 17
#define PIN_LED2 18
#define PIN_LED3 19

//TEMPERATURE TASK PIN
#define DHT_PIN 13

//TIME INTERVALS
#define N1 5000
#define N2 2000
#define N3 6000
#define N4 2500

//DISTANCE VALUE
#define MINDIST 0.04
#define MAXDIST 0.08

//MAX TEMPERATURE VALUE
#define MAXTEMP 30

/**
 * @brief Enumeration representing the states in a car washing process.
 *
 * The CarWashingState enumeration defines the possible states in a car washing
 * process. Each state represents a specific phase, from the car waiting to washing 
 * completion.
 */
enum CarWashingState {
    CAR_WAITING,        //The initial state when the car is waiting.
    WELCOME,            // The state indicating the welcome phase, triggered when a car is detected by the motion sensor.
    GATE_OPENING,       // The state when the gate of the car wash is opening, and it closes when the car is at the correct distance.
    READY_TO_WASH,      // The state when the system is ready to start washing, waiting for the user to push the start button.
    CAR_WASHING,        // The state representing the active car washing process.
    WASHING_COMPLETED,  // The state indicating that the car washing is completed.
    MAINTENANCE         //The state called only if the temperature during washing exceeds a certain value, indicating the need for maintenance.
};

#endif