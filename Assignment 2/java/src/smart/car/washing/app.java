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

        if (args.length == 0) {
            DashboardLogger.showAndLogError(new Exception("No Port passed as argument, exiting program."),
                    "No Port passed as argument", Level.SEVERE);
            try {
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.exit(-1);
        }

        dashboard = new SmartCarWashingDashboard();
        boolean connectionEstablished = false;
        
        while (!connectionEstablished) {
            try {
                channelMonitor = new ChannelMonitor(new SerialCommChannel(args[0], 9600));
                channelMonitor.attachController(controller);
                connectionEstablished = true;
            } catch (Exception e) {
                connectionEstablished = false;
                e.printStackTrace();
                DashboardLogger.showAndLogError(e, "Connection to " + args[0] + " failed", Level.SEVERE);
                try {
                    Thread.sleep(5000);
                } catch (InterruptedException e1) {
                    e1.printStackTrace();
                }
            }
        }

        channelMonitorThread = new Thread(channelMonitor);
        controller = new ControllerImpl(dashboard, channelMonitor);
        channelMonitor.attachController(controller);
        dashboard.attachController(controller);
        channelMonitorThread.start();
    }
}
