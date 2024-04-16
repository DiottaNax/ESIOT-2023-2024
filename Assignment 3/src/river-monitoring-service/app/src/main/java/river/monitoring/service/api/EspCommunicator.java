package river.monitoring.service.api;

import java.util.Optional;

/**
 * Interface for communication with an ESP device in a river monitoring system.
 */
public interface EspCommunicator {

    /**
     * Retrieves the current water level measurement from the ESP device.
     * 
     * @return an {@link Optional} containing the current water level as a {@link Double},
     *         or an empty {@link Optional} if the data is not available or cannot be retrieved.
     */
    Optional<Double> getWaterLevel();

    /**
     * This method adjusts the frequency at which the ESP device transmits data to the monitoring system,
     * allowing for control over the rate at which new water level measurements are sent.
     *
     * @param frequency the new frequency of data transmission in milliseconds to the ESP device.
     */
    void setFrequency(int frequency);
}
