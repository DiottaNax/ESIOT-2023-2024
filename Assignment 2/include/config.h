#ifndef __CONFIG__
#define __CONFIG__

#define PRESENCE_SENSOR 2
#define PIN_LED1 11
#define PIN_LED2 12
#define PIN_LED3 13

#define N1 1
#define N2 2000
#define N3 3
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