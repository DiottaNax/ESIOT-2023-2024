#ifndef __CONFIG__
#define __CONFIG__

//WATER VALVE PIN
#define VALVE_PIN 2
//DISPLAY PIN
#define RS_PIN 3
#define ENABLE_PIN 4
#define D4_PIN 5
#define D5_PIN 6
#define D6_PIN 7
#define D7_PIN 8
//BUTTON PIN
#define BUTTON_PIN 11
//POTENTIOMETER PIN
#define POT_PIN A0

enum State {
        MANUAL,     //State for Manual mode
        AUTOMATIC   //State for Automatic mode
    };

#endif