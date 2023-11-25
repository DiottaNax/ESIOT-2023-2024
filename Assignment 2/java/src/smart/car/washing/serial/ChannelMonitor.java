package smart.car.washing.serial;

import java.util.Optional;

import smart.car.washing.controller.Controller;

public class ChannelMonitor implements Runnable {
    private Optional<SerialCommChannel> commChannel = Optional.empty();
    private final Controller controller;

    public ChannelMonitor(final String port, final Controller controller) {
        this.controller = controller;

        try {
            commChannel = Optional.of(new SerialCommChannel(port, 9600));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        if (commChannel.isPresent()) {
            if (commChannel.get().isMsgAvailable()) {
                try {
                    this.controller.notifyEvent(commChannel.get().receiveMsg());
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        try {
            Thread.sleep(10);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}