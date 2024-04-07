#include "TaskWithState.h"
#include "devices/WaterValve.h"

class WaterChannelControlTask : public TaskWithState {
    enum State {
        REMOTE,     //State for Remote mode
        MANUAL,     //State for Manual mode
        AUTOMATIC   //State for Automatic mode
    };

    private:
    WaterValve waterValve;

    public:
    WaterChannelControlTask();
    void init();
    void tick();
}