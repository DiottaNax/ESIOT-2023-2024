package river.monitoring.service.core;

import river.monitoring.service.api.SystemModeHandler;
import river.monitoring.service.common.SystemMode;

/**
 * Implementation of the {@link SystemModeHandler} interface.
 * This class manages the operational mode of the river monitoring system.
 */
public class SystemModeHandlerImpl implements SystemModeHandler {

    private SystemMode currentMode;

    /**
     * Constructs a SystemModeHandlerImpl with the specified initial mode.
     *
     * @param initialMode the initial operational mode.
     */
    public SystemModeHandlerImpl(final SystemMode initialMode) {
        this.currentMode = initialMode;
    }

    /**
     * Constructs a SystemModeHandlerImpl with the default mode (AUTO).
     */
    public SystemModeHandlerImpl() {
        this.currentMode = SystemMode.AUTO;
    }

    @Override
    public boolean changeMode(final SystemMode mode) {
        if (this.currentMode.equals(mode)) {
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
