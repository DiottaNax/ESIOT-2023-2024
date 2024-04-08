package river.monitoring.service.common;

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

    int getFrequency() {
        return this.frequency;
    }

    int getValveOpening() {
        return this.valveOpening;
    }

    SystemState getFromWaterLevel(final double wLevel) {
        if (wLevel <= 6.0) {
            return ALARM_TOO_LOW;
        } else if(wLevel > 6.0 && wLevel <= 10.0) {
            return NORMAL;
        } else if (wLevel > 10.0 && wLevel <= 12.5) {
            return PRE_ALARM_TOO_HIGH;
        } else if(wLevel > 12.5 && wLevel <= 15.0) {
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
