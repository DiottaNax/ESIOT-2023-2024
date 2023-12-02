package smart.car.washing.serial;

import java.util.logging.Level;
import smart.car.washing.controller.Controller;
import smart.car.washing.gui.DashboardLogger;

public class ChannelMonitor implements Runnable {
    private final CommChannel commChannel;
    private Controller controller;

    public ChannelMonitor(final CommChannel commChannel) {
        this.commChannel = commChannel;
    }

    public void sendMessage(final String msg) {
        commChannel.sendMsg(msg);
    }

    public void attachController(final Controller controller) {
        this.controller = controller;
    }

    @Override
    public void run() {
        System.out.println("Waiting Arduino for rebooting...");
		try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
            DashboardLogger.showAndLogError(e, "Thread sleep failed",Level.SEVERE);
        }
        System.out.println("Ready.");
        
        /**
         * Listening for serial events
         */
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

            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
                DashboardLogger.showAndLogError(e, "Thread sleep failed",Level.SEVERE);
            }
        }
    }

}