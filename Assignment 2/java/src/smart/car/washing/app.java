package smart.car.washing;

import java.util.logging.Level;

import smart.car.washing.controller.Controller;
import smart.car.washing.controller.ControllerImpl;
import smart.car.washing.gui.Dashboard;
import smart.car.washing.gui.DashboardLogger;
import smart.car.washing.gui.SmartCarWashingDashboard;
import smart.car.washing.serial.ChannelMonitor;
import smart.car.washing.serial.SerialCommChannel;

/**
 * The main application class for the smart car washing system.
 * Initializes and coordinates the components of the system, including the dashboard,
 * channel monitor, and controller.
 */
public class app {

    private static ChannelMonitor channelMonitor;
    private static Thread channelMonitorThread;
    private static Controller controller;
    private static Dashboard dashboard; 
    
    /**
     * The main entry point of the application.
     *
     * @param args The command-line arguments.
     */
    public static void main(String[] args) {
        dashboard = new SmartCarWashingDashboard();
        
        try {
            channelMonitor = new ChannelMonitor(new SerialCommChannel("COM9", 9600));
            channelMonitor.attachController(controller);
        } catch (Exception e) {
            e.printStackTrace();
            DashboardLogger.showError(e, Level.SEVERE);
        }

        channelMonitorThread = new Thread(channelMonitor);
        controller = new ControllerImpl(dashboard, channelMonitor);
        channelMonitor.attachController(controller);
        dashboard.attachController(controller);
        channelMonitorThread.start();
    }
}
