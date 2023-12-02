package smart.car.washing.controller;

import java.util.StringTokenizer;
import java.util.logging.Level;

import smart.car.washing.gui.CarWashingState;
import smart.car.washing.gui.Dashboard;
import smart.car.washing.gui.DashboardLogger;
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
        //The incoming message is in the format 'FIELD:VALUE'.
        StringTokenizer tokenizer = new StringTokenizer(msgEvent, ":");
        if (tokenizer.hasMoreTokens()) {
            try{
                //Update the GUI based on the FIELD with the VALUE
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
            } catch(NumberFormatException e){
                DashboardLogger.showAndLogError(e, "Failed to parse Dashboard Info", Level.WARNING);
            }
        }
    }
    
}
