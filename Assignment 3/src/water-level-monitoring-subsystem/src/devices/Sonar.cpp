#include <Arduino.h>
#include "devices/Sonar.h"

Sonar::Sonar(){
    
}

void Sonar :: init() {
    pinMode(trigSonar, OUTPUT);
    pinMode(echoSonar, INPUT);
}

float Sonar :: get_distance() {
    digitalWrite(trigSonar, LOW);
    delayMicroseconds(3);
    digitalWrite(trigSonar, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigSonar, LOW);

    float tUS = pulseIn(echoSonar, HIGH);
    float t = tUS / 1000.0 / 1000.0 / 2;
    float d = t*vs;
    return d;
}
