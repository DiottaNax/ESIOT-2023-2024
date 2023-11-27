package smart.car.washing.controller;

/**
 * Interface representing a controller for handling events in a system.
 */
public interface Controller {

    /**
     * Notifies the controller about an event in the system.
     *
     * @param msgEvent A string representing the event message or identifier.
     */
    void notifyEvent(String msgEvent);
    
}
