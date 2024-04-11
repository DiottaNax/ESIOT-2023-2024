#include "Task.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include "WaterChannelControlTask.h"
#include "config.h"

class ConsoleTask : public Task {
    
    private:
    Button button;
    LCDDisplay lcdDisplay;
    WaterChannelControlTask waterChannelControlTask;

    public:
    ConsoleTask();
    void init();
    void tick();
}