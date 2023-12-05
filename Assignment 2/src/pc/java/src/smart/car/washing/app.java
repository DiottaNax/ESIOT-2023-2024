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
    private static int connectionAttempts = 0;

    private final static int MAX_ATTEMPTS = 3;

    /**
     * The main entry point of the application.
     *
     * @param args The command-line arguments.
     */
    public static void main(String[] args) {
        // Check if a serial port is provided as a command-line argument
        if (args.length == 0) {
            // If no serial port is provided, log an error and exit the program
            DashboardLogger.showAndLogError(new IllegalArgumentException("No Port passed as argument, exiting program."),
                    "No Port passed as argument", Level.SEVERE);

            // Sleep for 5s allowing to see the error message
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.exit(-1);
        }

        dashboard = new SmartCarWashingDashboard();
        boolean connectionEstablished = false;
        
        // Attempt to establish a connection to the specified serial port
        while (!connectionEstablished) {
            try {
                // Initialize the ChannelMonitor and attach the controller
                channelMonitor = new ChannelMonitor(new SerialCommChannel(args[0], 9600));
                channelMonitor.attachController(controller);
                connectionEstablished = true;
            } catch (Exception e) {
                connectionAttempts++;
                // If the program failed to connect to the port for MAX_ATTEMPTS times, log an error and exit
                if (connectionAttempts > MAX_ATTEMPTS) {
                    DashboardLogger.showAndLogError(
                            new Exception("Connection to " + args[0] + " failed for " + connectionAttempts
                                    + " times, exiting program."),
                            "Connection to " + args[0] + " failed." + connectionAttempts, Level.SEVERE);
                } else {
                    connectionEstablished = false;
                    e.printStackTrace();
                    // If the connection failed log an error and try to reconnect
                    DashboardLogger.showAndLogError(e,
                            "Connection to " + args[0] + " failed, attempt N." + connectionAttempts, Level.WARNING);
                }

                // Sleep for 5s allowing the user to connect the cable and read the error messages
                try {
                    Thread.sleep(5000);
                } catch (InterruptedException e1) {
                    e1.printStackTrace();
                }
            }
        }

        // Start a separate thread for the ChannelMonitor
        channelMonitorThread = new Thread(channelMonitor);

        // Initialize the Controller, attach it to the ChannelMonitor and the Dashboard
        controller = new ControllerImpl(dashboard, channelMonitor);
        channelMonitor.attachController(controller);
        dashboard.attachController(controller);

        channelMonitorThread.start();
    }
}
