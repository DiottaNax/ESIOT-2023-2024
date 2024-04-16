package river.monitoring.service.api;

/**
 * Interface defining the control operations necessary for managing a river monitoring system.
 * <p>This interface provides methods to update system states and process relevant data.
 */
public interface Controller {

    /**
     * <p>Updates the water level measurement in the system.
     * <p>This method should be called to refresh the current water level based on new data,
     * which may come from sensors or external data sources.
     */
    void updateWaterLevel();

    /**
     * <p>Updates the alarm level status in the system.
     * <p>This method should be called to adjust the alarm level settings based on the current
     * water level.
     */
    void updateAlarmLevel();
    
    /**
     * <p>Updates the valve opening status.
     * <p>This method should adjust the valve opening based on the current system needs,
     * which could be automatically calculated or manually set depending on the system mode.
     */
    void updateValveOpening();

    /**
     * <p>Updates the information displayed on the system's dashboard.
     * <p>This method should refresh the dashboard to reflect the latest data and system status,
     * including water level, valve status, and system state.
     */
    void updateDashboard();
    
    /**
     * <p>Processes the collected data to make operational decisions.
     * <p>This method involves analyzing the sensor and input data to determine necessary actions,
     * such as adjusting valve openings or updating alarms, and should ensure that the system
     * reacts appropriately to new datas.
     */
    void processData();
}
