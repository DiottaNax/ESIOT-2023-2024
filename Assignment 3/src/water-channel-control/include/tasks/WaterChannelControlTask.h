#include "TaskWithState.h"
#include "devices/WaterValve.h"
#include "config.h"

class WaterChannelControlTask : public TaskWithState {

    private:
    WaterValve waterValve;

    public:
    WaterChannelControlTask();
    void init();
    void tick();
}