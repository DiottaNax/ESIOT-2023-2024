package river.monitoring.service.api;

import java.util.Optional;
import river.monitoring.service.common.DataPoint;

/**
 * <p>Interface for communication with the dashboard.
 */
public interface DashboardCommunicator {

    /**
     * <p>Updates the dashboard with a new or existing data point.
     * <p>This method is used to send data from the system to the dashboard, allowing
     * the dashboard to display the most current information available.
     *
     * @param data An {@link Optional} containing a {@link DataPoint} to update the dashboard.
     *             If the {@link Optional} is empty, it may indicate no new data is available or
     *             that an error has occurred in data collection.
     */
    void updateData(Optional<DataPoint> data);

    /**
     * <p>Retrieves the current opening angle of the valve as displayed or controlled by the dashboard.
     * <p>This method provides access to the latest valve opening data that might be adjusted by the user
     * through the dashboard or updated by automatic control mechanisms.
     *
     * @return an {@link Optional} containing the current valve opening as an {@link Integer}, representing
     *         the percentage of the valve opening, or an empty {@link Optional} if the data is not available
     *         or cannot be retrieved.
     */
    Optional<Integer> getValveOpening();
}
