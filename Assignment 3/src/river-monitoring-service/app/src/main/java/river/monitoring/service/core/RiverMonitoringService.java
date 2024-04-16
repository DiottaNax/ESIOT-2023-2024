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
            var newAlarm = Optional.of(SystemState.getFromWaterLevel(this.waterLevel.get()));
            if (!this.alarmLevel.equals(newAlarm)) {
                this.alarmLevel = newAlarm;
                this.newDataToProcess = true;
            }
        }
    }

    @Override
    public void updateValveOpening() {
        final var mode = modeHandler.getCurrentMode();
        Optional<Integer> nextValveOpening = Optional.empty();
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
        
        if (!nextValveOpening.equals(this.valveOpening) && nextValveOpening.isPresent()) {
            this.valveOpening = nextValveOpening;
            this.newDataToProcess = true;
        }
    }

    @Override
    public void updateDashboard() {
        var optionals = List.of(this.alarmLevel, this.valveOpening, this.waterLevel);
        // Update dashboard only if all values are present
        if (optionals.stream().allMatch(Optional::isPresent)) {
            var data = new DataPoint(this.modeHandler.getCurrentMode(),
                    this.waterLevel.get(),
                    this.valveOpening.get(),
                    this.alarmLevel.get());
            this.dashboardComm.updateData(Optional.of(data));
        }
    }

    @Override
    public void processData() {
        // Send new data to arduino, esp and dashboard only if there are new datas
        if (newDataToProcess) {
            this.valveOpening.ifPresent(this.arduinoComm::setValveOpening);
            this.alarmLevel.ifPresent(a -> this.espComm.setFrequence(a.getFrequency()));
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
