package river.monitoring.service.api;

import river.monitoring.service.common.SystemMode;

/**
 * Interface for managing the operational mode of a river monitoring system.
 */
public interface SystemModeHandler {

    /**
     * Attempts to change the operational mode of the system to the specified mode.
     *
     * @param mode the new system mode to set.
     * @return {@code true} if the mode was successfully changed, {@code false} otherwise.
     */
    boolean changeMode(final SystemMode mode);

    /**
     * Retrieves the current operational mode of the system.
     *
     * @return the current system mode.
     */
    SystemMode getCurrentMode();
}
