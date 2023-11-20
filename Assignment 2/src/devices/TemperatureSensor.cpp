#include "ITemperatureSensor.h"

class TemperatureSensor : ITemperatureSensor {
    private:
        int pin;
    
    public:
    TemperatureSensor(int pin) {
        this->pin = pin;
        pinMode(this->pin,INPUT);
    }

    int getTemp() {
        int val = analogRead(this->pin);
        val = (val*(5000/1024))*0.1;
        return val;
    }
};