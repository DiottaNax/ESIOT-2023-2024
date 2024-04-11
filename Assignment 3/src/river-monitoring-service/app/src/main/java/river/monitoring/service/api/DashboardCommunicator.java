package river.monitoring.service.api;

import java.util.Optional;

import river.monitoring.service.common.DataPoint;

public interface DashboardCommunicator {
    void updateData(Optional<DataPoint> data);

    Optional<Integer> getValveOpening();
}
