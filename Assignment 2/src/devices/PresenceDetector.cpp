#include "IPresenceDetector.h"

class PresenceDetector : IPresenceDetector {
    private:
        int pin;
    
    public:
    PresenceDetector(int pin) {
        this->pin = pin;
        pinMode(this->pin,INPUT);
    }

    boolean isDetected() {
        boolean read = digitalRead(this->pin);
        if (read == HIGH) {
            return true;
        } else {
            return false;
        }
    }
};