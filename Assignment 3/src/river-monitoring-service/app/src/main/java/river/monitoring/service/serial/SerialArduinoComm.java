package river.monitoring.service.serial;

import java.util.Optional;
import java.util.StringTokenizer;

import river.monitoring.service.api.ArduinoCommunicator;
import river.monitoring.service.api.SystemModeHandler;
import river.monitoring.service.common.SystemMode;

/**
 * Monitors the communication channel for incoming messages and notifies the attached controller.
 */
public class SerialArduinoComm implements Runnable, ArduinoCommunicator {
    private final CommChannel commChannel;
    private final SystemModeHandler modeHandler;

    private Optional<Integer> valveOpening = Optional.empty();

    /**
     * Constructs a ChannelMonitor with the specified communication channel.
     *
     * @param commChannel The communication channel to monitor.
     */
    public SerialArduinoComm(final CommChannel commChannel, final SystemModeHandler modeHandler) {
        this.commChannel = commChannel;
        this.modeHandler = modeHandler;

        // Wait for Arduino to reboot
        log("Waiting Arduino for rebooting...");
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
            log("Thread sleep failed");
        }
        log("Ready.");
    }

    /**
     * Sends a message through the communication channel.
     *
     * @param msg The message to be sent.
     */
    private void sendMessage(final String msg) {
        commChannel.sendMsg(msg);
    }


    @Override
    public void run() {

        //Listening for serial events
        while (true) {
            if (commChannel.isMsgAvailable()) {
                try {
                    final String msg = commChannel.receiveMsg();
                    final StringTokenizer tokenizer = new StringTokenizer(msg, ":");
                    log("\t" + msg);
                    switch (tokenizer.nextToken()) {
                        case "VALVE_OPENING":
                            if (tokenizer.hasMoreTokens()) {
                                try {
                                    final int vOpening = Integer.parseInt(tokenizer.nextToken());
                                    this.valveOpening = Optional.of(vOpening);
                                } catch (NumberFormatException e) {
                                    log("Failed to parse valve opening");
                                }
                            }
                            break;
                    
                        case "MODE":
                            if (tokenizer.hasMoreTokens()) {
                                switch (tokenizer.nextToken()) {
                                    case "AUTO":
                                        this.modeHandler.changeMode(SystemMode.AUTO);
                                        break;
                                
                                    case "MANUAL":
                                        this.modeHandler.changeMode(SystemMode.MANUAL);
                                        break;
                                }
                            }
                            break;
                    }
                    
                } catch (InterruptedException e) {
                    e.printStackTrace();
                    log("Failed to receive message");
                }
            }
            // Sleep for a short duration to avoid high CPU usage
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
                log("Thread sleep failed");
            }
        }
    }
    
    private void log(final String message) {
        System.out.println("[ARDUINO COMM]: " + message);
    }

    @Override
    public Optional<Integer> getValveOpening() {
        return this.valveOpening;
    }

    @Override
    public void setValveOpening(int valveOpening) {
        this.sendMessage("VALVE_OPENING" + valveOpening);
    }

}