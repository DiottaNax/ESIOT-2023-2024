package smart.car.washing.gui;

/**
* Enumeration representing the states in a car washing process.
* Each state is associated with a numerical value and a corresponding state name.
*/
public enum CarWashingState {
    CAR_WAITING(0, "Waiting for a car"),
    WELCOME(1, "Car arrived"),
    GATE_OPENING(2, "Gate Opening"),
    READY_TO_WASH(3, "Ready to Wash"),
    CAR_WASHING(4, "Car Washing"),
    WASHING_COMPLETED(5, "Washing Completed"),
    MAINTENANCE(6, "Maintenance");

    private final int value;
    private final String stateName;
    
    /**
     * Constructor for CarWashingState.
     *
     * @param value     The numerical value of the state.
     * @param stateName The name of the state.
     */
    CarWashingState(int value, String stateName) {
        this.value = value;
        this.stateName = stateName;
    }

    /**
     * Get the name of the state.
     *
     * @return The name of the state.
     */
    public String getStateName() {
        return stateName;
    }

    /**
     * Get the state enum based on the numerical value.
     *
     * @param value The numerical value of the state.
     * @return The corresponding CarWashingState name.
     */
    public static CarWashingState fromValue(int value) {
        for (CarWashingState state : values()) {
            if (state.value == value) {
                return state;
            }
        }
        return null;
    }
}
