package smart.car.washing.gui;

import smart.car.washing.controller.Controller;

/**
 * Interface representing the dashboard of a smart car washing system.
 *
 * The Dashboard interface defines methods for updating and displaying
 * information on the user interface. 
 */
public interface Dashboard {

    /**
     * Attaches a controller to the dashboard for event handling.
     *
     * @param controller The controller to be attached for event handling.
     */
    void attachController(final Controller controller);

    /**
     * Updates the displayed state on the dashboard.
     *
     * @param state A string representing the current state of the car washing system.
     */
    void updateState(final String state);

    /**
     * Updates the displayed washing number on the dashboard.
     *
     * @param number The current washing number or identifier.
     */
    void updateWashingNumber(final int number);

    /**
     * Updates the displayed temperature on the dashboard.
     *
     * @param temperature The current temperature reading from the system.
     */
    void updateTemperature(final int temperature);
}
