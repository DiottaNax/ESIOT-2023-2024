package river.monitoring.service.common;

public enum SystemMode {
    AUTO("AUTO"), 
    MANUAL("MANUAL"), 
    REMOTE("REMOTE");

    final String mode;

    private SystemMode(final String mode) {
        this.mode = mode;
    }

    @Override
    public String toString() {
        return this.mode;
    }
}
