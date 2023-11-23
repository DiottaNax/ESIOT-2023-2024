#ifndef __CONFIG__
#define __CONFIG__

#define PIR_PIN 2
#define PIN_LED1 14
#define PIN_LED2 15
#define PIN_LED3 16

#define N1 1000
#define N2 2000
#define N3 5000
#define N4 2000

#define MINDIST 0.04
#define MAXDIST 0.08

enum CarWashingState {
    CAR_WAITING,
    WELCOME,
    GATE_OPENING,
    READY_TO_WASH,
    CAR_WASHING,
    WASHING_COMPLETED,
    MAINTENANCE
};

#endif