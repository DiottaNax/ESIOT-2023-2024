#ifndef __CONFIG__
#define __CONFIG__

#define N2 2000
#define N4 2000

#define MINDIST 0.05
#define MAXDIST 0.1

enum CarWashingState {
    CAR_WAITING,
    WELCOME,
    GATE_OPENING,
    READY_TO_WASH,
    CAR_WASHING,
    WASHING_COMPLETED,
    MANTEINANCE
};

#endif