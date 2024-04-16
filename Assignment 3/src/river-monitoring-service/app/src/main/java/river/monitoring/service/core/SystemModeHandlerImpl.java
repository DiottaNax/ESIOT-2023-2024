package river.monitoring.service.core;

import river.monitoring.service.api.SystemModeHandler;
import river.monitoring.service.common.SystemMode;

public class SystemModeHandlerImpl implements SystemModeHandler{

    private SystemMode currentMode;

    public SystemModeHandlerImpl(final SystemMode initialMode) {
        this.currentMode = initialMode;
    }

    public SystemModeHandlerImpl() {
        this.currentMode = SystemMode.AUTO;
    }

    @Override
    public boolean changeMode(final SystemMode mode) {
        if(this.currentMode.equals(mode)){
            return false;
        } else if (this.currentMode.equals(SystemMode.MANUAL)) {
            if (!mode.equals(SystemMode.AUTO)) {
                return false;
            }
        }

        this.currentMode = mode;
        return true;
    }

    @Override
    public SystemMode getCurrentMode() {
        return this.currentMode;
    }
}
