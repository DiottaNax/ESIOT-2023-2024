#ifndef __BRIDGE__
#define __BRIDGE__
#include "config.h"

class Bridge {

private:
    CarWashingState currentState;
    long stateTimestamp;

public:
    Bridge();
    CarWashingState getState();
    void setState(CarWashingState);
    long elapsedTimeInState();
};

#endif