#ifndef __PRESENCE_SENSOR__
#define __PRESENCE_SENSOR__

#include <Arduino.h>

class IPresenceDetector {
public:
    boolean isDetected;
};

#endif