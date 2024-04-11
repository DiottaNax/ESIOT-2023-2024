package river.monitoring.service.api;

import java.util.Optional;

public interface ArduinoCommunicator {
    Optional<Integer> getValveOpening();

    void setValveOpening(int valveOpening);
}
