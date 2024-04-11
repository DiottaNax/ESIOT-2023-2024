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

    public RiverMonitoringService(final String serialPort) throws Exception {
        this.modeHandler = new SystemModeHandlerImpl();
        this.arduinoComm = new SerialArduinoComm(new SerialCommChannel(serialPort, 9600), this.modeHandler);
        this.espComm = new MqttEspComm();
        this.dashboardComm = new HttpDashboardComm(modeHandler);
    }

    @Override
    public void updateWaterLevel() {
        this.waterLevel = this.espComm.getWaterLevel();
    }

    @Override
    public void updateAlarmLevel() {
        if (this.waterLevel.isPresent()) {
            this.alarmLevel = Optional.of(SystemState.getFromWaterLevel(this.waterLevel.get()));
        }
    }

    @Override
    public void updateValveOpening() {
        final var mode = modeHandler.getCurrentMode();
        switch(mode) {
            case AUTO:
                if (alarmLevel.isPresent()) {
                    this.valveOpening = Optional.of(alarmLevel.get().getValveOpening());
                }
                break;
            case MANUAL:
                this.valveOpening = arduinoComm.getValveOpening();
                break;
            case REMOTE:
                this.valveOpening = dashboardComm.getValveOpening();
                break;
        }
    }

    @Override
    public void updateDashboard() {
        var optionals = List.of(this.alarmLevel, this.valveOpening, this.waterLevel);
        if (optionals.stream().noneMatch(Optional::isPresent)) {
            var data = new DataPoint(this.modeHandler.getCurrentMode(),
                    this.waterLevel.get(),
                    this.valveOpening.get(),
                    this.alarmLevel.get());
            this.dashboardComm.updateData(Optional.of(data));
        } else {
            this.dashboardComm.updateData(Optional.empty());
        }
    }

    @Override
    public void processData() {
        this.valveOpening.ifPresent(this.arduinoComm::setValveOpening);
    }

    @Override
    public void run() {
        while (true) {
            updateWaterLevel();
            updateAlarmLevel();
            updateValveOpening();
            updateDashboard();

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
