#ifndef __USER_CONSOLE_TASK__
#define __USER_CONSOLE_TASK__

#define SLIDING_PERIOD 1000
#define TICK_PERIOD 200

#define RS_PIN 2
#define ENABLE_PIN 3
#define D4_PIN 4
#define D5_PIN 5
#define D6_PIN 6
#define D7_PIN 7
#define BUTTON_PIN 10

#include "tasks/Task.h"
#include "tasks/BlinkingTask.h"
#include "model/Bridge.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include "devices/Button.h"
#include "devices/Led.h"

class UserConsoleTask : public Task {
private:
    short _timeStamp;
    bool _justChangedState;
    String _tooLongString;

    Bridge *_bridge;
    BlinkingTask *_tBlinking;

    LCDDisplay _display = LCDDisplay(RS_PIN, ENABLE_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);
    Button _button = Button(BUTTON_PIN);
    Led _leds[3] = {Led(PIN_LED1), Led(PIN_LED2), Led(PIN_LED3)};

    int getWashingPercentage();
    void makeTextScroll();

public:
    UserConsoleTask(Bridge *bridge, BlinkingTask* tBlinking);
    void init();
    void tick();
};

#endif