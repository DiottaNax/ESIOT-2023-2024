#ifndef __TASK__
#define __TASK__

class Task {

public:
  Task(){
    active = false;
    periodic = false;
  }

  Task(int period){
      active = false;
      periodic = true;
      this->period = period;
  }

  void init() {
      active = true;
      timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool isActive() {
      return active;
  }

  void setActive(bool active) {
      this->active = active;
      timeElapsed = 0;
  }

  bool isPeriodic() {
      return periodic;
  }

private:
    bool active;
    bool periodic;
    int period;
    int timeElapsed;
};

#endif