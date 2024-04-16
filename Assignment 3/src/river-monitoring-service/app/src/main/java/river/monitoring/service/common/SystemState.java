package river.monitoring.service.common;

/**
 * Enum representing the states of a river monitoring system.
 * This enum defines various system states, each with a corresponding data frequency and valve opening level.
 */
public enum SystemState {

    ALARM_TOO_LOW(2000, 0), 
    NORMAL(5000, 45), 
    PRE_ALARM_TOO_HIGH(3000, 45), 
    ALARM_TOO_HIGH(2500, 90), 
    ALARM_TOO_HIGH_CRITIC(1500, 180);

    private final int frequency;
    private final int valveOpening;

    private SystemState(final int frequency,final int valveOpening) {
        this.frequency = frequency;
        this.valveOpening = valveOpening;
    }

    /**
     * Retrieves the data frequency associated with the system state.
     *
     * @return the data frequency in milliseconds.
     */
    public int getFrequency() {
        return this.frequency;
    }

    /**
     * Retrieves the valve opening level associated with the system state.
     *
     * @return the valve opening level.
     */
    public int getValveOpening() {
        return this.valveOpening;
    }

    /**
     * Determines the system state based on the water level.
     *
     * @param wLevel the water level measurement.
     * @return the corresponding SystemState based on the water level.
     */
    public static SystemState getFromWaterLevel(final double wLevel) {
        if (wLevel <= 0.06) {
            return ALARM_TOO_LOW;
        } else if(wLevel > 0.06 && wLevel <= 0.16) {
            return NORMAL;
        } else if (wLevel > 0.16 && wLevel <= 0.22) {
            return PRE_ALARM_TOO_HIGH;
        } else if(wLevel > 0.22 && wLevel <= 0.3) {
            return ALARM_TOO_HIGH;
        } else {
            return ALARM_TOO_HIGH_CRITIC;
        }
    }

    @Override
    public String toString() {
        return this.name();
    }
}
