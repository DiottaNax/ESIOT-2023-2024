package river.monitoring.service.core;

import river.monitoring.service.api.ArduinoCommunicator;
import river.monitoring.service.api.Controller;
import river.monitoring.service.api.DashboardCommunicator;
import river.monitoring.service.api.EspCommunicator;
import river.monitoring.service.api.SystemModeHandler;
import river.monitoring.service.common.DataPoint;
import river.monitoring.service.common.SystemState;
import river.monitoring.service.http.HttpDashboardComm;
import river.monitoring.service.mqtt.MqttEspComm;
import river.monitoring.service.serial.SerialArduinoComm;
import river.monitoring.service.serial.SerialCommChannel;

import java.lang.Runnable;
import java.util.Optional;
import java.util.List;

/**
 * <p>Represents the core functionality of a river monitoring service.
 * <p>This service integrates communication with various components such as Arduino,
 * ESP, and Dashboard, and provides methods to update and process data.
 * <p>Implements {@link Controller} and {@link Runnable}.
 */
public class RiverMonitoringService implements Controller, Runnable {

    private final static long PERIOD = 50; //milliseconds

    private final SystemModeHandler modeHandler;
    private final DashboardCommunicator dashboardComm;
    private final EspCommunicator espComm;
    private final ArduinoCommunicator arduinoComm;

    private Optional<Double> waterLevel = Optional.empty();
    private Optional<SystemState> alarmLevel = Optional.empty();
    private Optional<Integer> valveOpening = Optional.empty();
    private boolean newDataToProcess = true;

    /**
     * Constructs a RiverMonitoringService with the specified serial port for Arduino communication.
     *
     * @param serialPort the serial port to communicate with Arduino.
     * @throws Exception if an error occurs during initialization.
     */
    public RiverMonitoringService(final String serialPort) throws Exception {
        this.modeHandler = new SystemModeHandlerImpl();
        this.arduinoComm = new SerialArduinoComm(new SerialCommChannel(serialPort, 9600), this.modeHandler);
        this.dashboardComm = new HttpDashboardComm(modeHandler);
        this.espComm = new MqttEspComm();
    }

    @Override
    public void updateWaterLevel() {
        this.waterLevel = this.espComm.getWaterLevel();
    }

    @Override
    public void updateAlarmLevel() {
        if (this.waterLevel.isPresent()) {
            final var newAlarm = Optional.of(SystemState.getFromWaterLevel(this.waterLevel.get()));
            // To ensure that there's a new water level
            if (!this.alarmLevel.equals(newAlarm)) {
                this.alarmLevel = newAlarm;
                this.newDataToProcess = true; // New data are present
            }
        }
    }

    @Override
    public void updateValveOpening() {
        final var mode = modeHandler.getCurrentMode();
        Optional<Integer> nextValveOpening = Optional.empty();
        // Set the new valve opening level based on the system mode
        switch (mode) {
            case AUTO:
                if (alarmLevel.isPresent()) {
                    nextValveOpening = Optional.of(alarmLevel.get().getValveOpening());
                }
                break;
            case MANUAL:
                nextValveOpening = arduinoComm.getValveOpening();
                break;
            case REMOTE:
                nextValveOpening = dashboardComm.getValveOpening();
                break;
        }

        // To notify new data to process new valve opening must be different from the old and non empty
        if (!nextValveOpening.equals(this.valveOpening) && nextValveOpening.isPresent()) {
            this.valveOpening = nextValveOpening;
            this.newDataToProcess = true;
        }
    }

    @Override
    public void updateDashboard() {
        final var optionals = List.of(this.alarmLevel, this.valveOpening, this.waterLevel);
        // Update dashboard only if all values are present
        if (optionals.stream().allMatch(Optional::isPresent)) {
            final var data = new DataPoint(this.modeHandler.getCurrentMode(),
                    this.waterLevel.get(),
                    this.valveOpening.get(),
                    this.alarmLevel.get());
            this.dashboardComm.updateData(Optional.of(data));
        }
    }

    @Override
    public void processData() {
        // If there are new data send them to arduino, esp, and dashboard
        if (newDataToProcess) {
            this.valveOpening.ifPresent(this.arduinoComm::setValveOpening);
            this.alarmLevel.ifPresent(a -> this.espComm.setFrequency(a.getFrequency()));
            this.alarmLevel.ifPresent(a -> log("alarm is   " + a.name() + "  with freq " + a.getFrequency()));
        }

        newDataToProcess = false;
    }

    @Override
    public void run() {
        while (true) {
            updateWaterLevel();
            updateAlarmLevel();
            updateValveOpening();
            updateDashboard();
            processData();

            try {
                Thread.sleep(PERIOD);
            } catch (InterruptedException e) {
                log("Thread sleep failed");
            }
        }
    }

    private void log(final String message) {
        System.out.println("[SERVICE]: " + message);
    }
}
