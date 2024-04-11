#ifndef __SONAR__
#define __SONAR__

const int trigSonar = 12;
const int echoSonar = 11;
const float temperature = 20;
const float vs = 331.5 + 0.6*temperature;

class Sonar {
  private:
    float distance = 0.0;

  public:
    Sonar();
    void init();
    float get_distance();
};

#endif