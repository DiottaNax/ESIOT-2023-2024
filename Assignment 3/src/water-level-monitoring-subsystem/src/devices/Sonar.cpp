#include <Arduino.h>
#include "devices/Sonar.h"

void Sonar :: init() {
    pinMode(trigSonar, OUTPUT);
    pinMode(echoSonar, INPUT);
}

float Sonar :: get_distance() {
    digitalWrite(trigSonar, LOW);
    delayMicroseconds(3);
    digitalWrite(trigSonar, HIGH); // Send sound
    delayMicroseconds(5);
    digitalWrite(trigSonar, LOW);

    float tUS = pulseIn(echoSonar, HIGH); // Time measured in micros
    float t = tUS / 1000.0 / 1000.0 / 2; // Time converted in millis, it is dived by 2 because the sound reaches the obstacle and gets back
    float d = t*vs; // Distance (d) = time (t) * sound speed (vs)
    return d;
}
