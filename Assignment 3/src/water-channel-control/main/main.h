#include "tasks/ConsoleTask.h"
#include "tasks/WaterChannelControlTask.h"

class main {
    
    private:
    ConsoleTask consoleTask;
    WaterChannelControlTask waterChannelControlTask;

    public:
    void setup();
    void loop();
}