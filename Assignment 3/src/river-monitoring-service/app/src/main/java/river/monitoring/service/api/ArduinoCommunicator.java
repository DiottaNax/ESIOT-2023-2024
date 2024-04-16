package river.monitoring.service.api;

import java.util.Optional;

/**
 * Interface for communicating with an Arduino to control and monitor valve settings.
 */
public interface ArduinoCommunicator {

    /**
     * Retrieves the current opening level of the valve connected to the Arduino.
     * 
     * @return an {@link Optional} containing the current valve opening angle as an {@link Integer},
     *         or an empty {@link Optional} if the information is not available.
     */
    Optional<Integer> getValveOpening();

    /**
     * This method sends a command to the Arduino to adjust the valve to the specified opening level.
     * <p>The input should be a value representing the angle of valve opening (0-180).
     * 
     * @param valveOpening the new valve opening level as an angle (0-180).
     */
    void setValveOpening(int valveOpening);
}
