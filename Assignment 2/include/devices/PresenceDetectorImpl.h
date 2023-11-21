#ifndef __PRESENCE_DETECTOR_IMPL__
#define __PRESENCE_DETECTOR_IMPL__

#include "IPresenceDetector.h"

class PresenceDetectorImpl : IPresenceDetector{
private:
    int pin;
public:
    PresenceDetectorImpl(int pin);
    boolean isDetected();
};

#endif