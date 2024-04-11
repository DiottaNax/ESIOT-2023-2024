package river.monitoring.service.api;

import river.monitoring.service.common.SystemMode;

public interface SystemModeHandler {
    boolean changeMode(final SystemMode mode);

    SystemMode getCurrentMode();
}
