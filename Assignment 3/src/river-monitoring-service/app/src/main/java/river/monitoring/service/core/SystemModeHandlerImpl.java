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

    private boolean canChange(final SystemMode mode) {
        
        return !( // Negate all the condition in which System Mode can't change
                    this.currentMode.equals(mode) // SystemMode can't change if new mode isn't different from the current
                    || (this.currentMode.equals(SystemMode.MANUAL) && !mode.equals(SystemMode.AUTO))  // SystemMode can't change if current mode is manual and new mode is not auto
                );
    }

    @Override
    public boolean changeMode(final SystemMode mode) {
        if (canChange(mode)) {
            this.currentMode = mode;
            return true;
        }

        return false;
    }

    @Override
    public SystemMode getCurrentMode() {
        return this.currentMode;
    }
}
