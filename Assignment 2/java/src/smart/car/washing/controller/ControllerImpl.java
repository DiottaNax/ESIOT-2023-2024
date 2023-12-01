package smart.car.washing.controller;

import java.util.StringTokenizer;

import smart.car.washing.gui.Dashboard;
import smart.car.washing.serial.ChannelMonitor;

/**
 * Implementation of the {@link Controller} interface for handling events in a smart car washing system.
 *
 * The ControllerImpl class processes and responds to events within the system
 * by updating the associated GUI (Dashboard) and sending messages through the
 * ChannelMonitor based on the event type.
 */
public class ControllerImpl implements Controller {
    private final Dashboard gui;
    private final ChannelMonitor channelMonitor;
    
    /**
     * Constructor for ControllerImpl.
     *
     * @param gui The Dashboard for updating the user interface.
     * @param channelMonitor The ChannelMonitor for sending messages.
     */
    public ControllerImpl(final Dashboard gui, final ChannelMonitor channelMonitor) {
        this.gui = gui;
        this.channelMonitor = channelMonitor;
    }
    
    /**
     * Notifies the controller about an event in the smart car washing system.
     *
     * @param msgEvent A string representing the event message or identifier.
     */
    public void notifyEvent(final String msgEvent) {
        StringTokenizer tokenizer = new StringTokenizer(msgEvent, ":");
        if (tokenizer.hasMoreTokens()) {
            switch (tokenizer.nextToken()) {
                case "TEMP":
                    this.gui.updateTemperature(Integer.parseInt(tokenizer.nextToken()));
                    break;

                case "STATE":
                    final int state = Integer.parseInt(tokenizer.nextToken());
                    this.gui.updateState(CarWashingState.fromValue(state));
                    break;

                case "NUMBER":
                    this.gui.updateWashingNumber(Integer.parseInt(tokenizer.nextToken()));
                    break;

                case "DONE":
                    this.channelMonitor.sendMessage("DONE");
                    break;
            }
        }
    }

    /**
    * Enumeration representing the states in a car washing process.
    * Each state is associated with a numerical value and a corresponding state name.
    */
    private enum CarWashingState {
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
        private String getStateName() {
            return stateName;
        }
    
        /**
         * Get the state enum based on the numerical value.
         *
         * @param value The numerical value of the state.
         * @return The corresponding CarWashingState name.
         */
        public static String fromValue(int value) {
            for (CarWashingState state : values()) {
                if (state.value == value) {
                    return state.getStateName();
                }
            }
            return null;
        }
    }
    
}
