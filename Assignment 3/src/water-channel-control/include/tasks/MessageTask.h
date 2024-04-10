#include "Task.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include "WaterChannelControlTask.h"
#include "config.h"

class MessageTask : public Task {
    
    private:
    Button button;
    LCDDisplay lcdDisplay;
    WaterChannelControlTask waterChannelControlTask;

    public:
    MessageTask();
    void init();
    void tick();
}