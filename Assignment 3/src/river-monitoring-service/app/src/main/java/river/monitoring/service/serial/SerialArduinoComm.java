package river.monitoring.service.serial;

import java.util.Optional;
import java.util.StringTokenizer;

import river.monitoring.service.api.ArduinoCommunicator;
import river.monitoring.service.api.SystemModeHandler;
import river.monitoring.service.common.SystemMode;

/**
 * Monitors the communication channel for incoming messages and notifies the attached controller.
 */
public class SerialArduinoComm implements ArduinoCommunicator {
    private final CommChannel commChannel;
    private final SystemModeHandler modeHandler;
    private final Thread communicationThread;

    private Optional<Integer> valveOpening = Optional.empty();

    /**
     * Constructs and reboots a SerialArduinoComm with the specified communication channel and mode handler.
     *
     * @param commChannel The communication channel to monitor.
     * @param modeHandler The mode handler to manage system modes.
     */
    public SerialArduinoComm(final CommChannel commChannel, final SystemModeHandler modeHandler) {
        this.commChannel = commChannel;
        this.modeHandler = modeHandler;
        this.communicationThread = new Thread(this::runCommunication);

        // Wait for Arduino to reboot
        log("Waiting for Arduino to reboot...");
        try {
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
            log("Thread sleep failed");
        }
        log("Ready.");

        this.communicationThread.start(); // Run communication in a dedicated thread
    }

    /**
     * Sends a message through the communication channel.
     *
     * @param msg The message to be sent.
     */
    private void sendMessage(final String msg) {
        log("sending " + msg);
        commChannel.sendMsg(msg);
    }

    private void runCommunication() {
        // Listening for serial events
        //log("Start communication with arduino"); //DEBUG
        while (true) {
            if (commChannel.isMsgAvailable()) {
                try {
                    final String msg = commChannel.receiveMsg();
                    final StringTokenizer tokenizer = new StringTokenizer(msg, ":"); // Message are made like "PREAMBLE:CONTENT"
                    //log("\t" + msg); //DEBUG
                    final var preamble = tokenizer.hasMoreTokens() ? tokenizer.nextToken() : ""; // Get the preamble if a string is present, empty string otherwise
                    //log("message arrived: " + msg); //DEBUG
                    switch (preamble) {
                        case "VALVE_OPENING":
                            // Parse valve opening
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
                        default:
                            break;
                    }

                } catch (InterruptedException e) {
                    e.printStackTrace();
                    log("Failed to receive message");
                }
            }
            // Sleep for a short duration to avoid high CPU usage
            try {
                Thread.sleep(20);
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
        this.sendMessage("VALVE_OPENING:" + valveOpening);
    }
}
