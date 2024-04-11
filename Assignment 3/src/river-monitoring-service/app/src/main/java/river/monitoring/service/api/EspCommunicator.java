package river.monitoring.service.api;

import java.util.Optional;

public interface EspCommunicator {
    Optional<Double> getWaterLevel();

    void setFrequence(int frequence);
}
