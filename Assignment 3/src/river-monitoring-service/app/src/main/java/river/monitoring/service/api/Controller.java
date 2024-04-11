package river.monitoring.service.api;

public interface Controller {
    void updateWaterLevel();

    void updateAlarmLevel();
    
    void updateValveOpening();

    void updateDashboard();
    
    void processData();
}
