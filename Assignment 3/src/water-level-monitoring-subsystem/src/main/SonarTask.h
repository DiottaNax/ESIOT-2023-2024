#ifndef __SONAR_TASK__
#define __SONAR_TASK__

const int trigSonar = 12;
const int echoSonar = 11;
const float vs = 331.5 + 0.6*20;

class SonarTask {
  private:
    float distance = 0.0;

  public:
    SonarTask();
    void init();
    float get_distance();
};

#endif