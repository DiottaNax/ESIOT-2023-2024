package smart.car.washing.serial;

import java.util.logging.Level;
import smart.car.washing.controller.Controller;
import smart.car.washing.gui.DashboardLogger;

/**
 * Monitors the communication channel for incoming messages and notifies the attached controller.
 */
public class ChannelMonitor implements Runnable {
    private final CommChannel commChannel;
    private Controller controller;

    /**
     * Constructs a ChannelMonitor with the specified communication channel.
     *
     * @param commChannel The communication channel to monitor.
     */
    public ChannelMonitor(final CommChannel commChannel) {
        this.commChannel = commChannel;
    }

    /**
     * Sends a message through the communication channel.
     *
     * @param msg The message to be sent.
     */
    public void sendMessage(final String msg) {
        commChannel.sendMsg(msg);
    }

    /**
     * Attaches a controller to be notified of incoming messages.
     *
     * @param controller The controller to attach.
     */
    public void attachController(final Controller controller) {
        this.controller = controller;
    }

    @Override
    public void run() {
        // Wait for Arduino to reboot
        System.out.println("Waiting Arduino for rebooting...");
		try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
            DashboardLogger.showAndLogError(e, "Thread sleep failed",Level.SEVERE);
        }
        System.out.println("Ready.");
        
        //Listening for serial events
        while (true) {
            if (commChannel.isMsgAvailable()) {
                try {
                    String msg = commChannel.receiveMsg();
                    System.out.println("\t" + msg);
                    this.controller.notifyEvent(msg);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    DashboardLogger.showAndLogError(e, "Failed to receive message", Level.SEVERE);
                }
            }
            // Sleep for a short duration to avoid high CPU usage
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
                DashboardLogger.showAndLogError(e, "Thread sleep failed",Level.SEVERE);
            }
        }
    }

}