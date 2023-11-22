#ifndef __USER_CONSOLE_TASK__
#define __USER_CONSOLE_TASK__

#include "tasks/Task.h"
#include "model/Bridge.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include "devices/Led.h"

class UserConsoleTask : public Task {
private:
    Bridge *_bridge;
    LCDDisplay *_display;
    Led *_leds[3];

public:
    UserConsoleTask(Bridge *bridge, LCDDisplay *display);
    void init();
    void tick();
};

#endif