package smart.car.washing.controller;

import java.util.StringTokenizer;

import smart.car.washing.gui.Dashboard;
import smart.car.washing.serial.ChannelMonitor;

public class ControllerImpl implements Controller {
    private final Dashboard gui;
    private final ChannelMonitor channelMonitor;
    

    public ControllerImpl(final Dashboard gui, final ChannelMonitor channelMonitor) {
        this.gui = gui;
        this.channelMonitor = channelMonitor;
    }
    
    public void notifyEvent(final String msgEvent) {
        StringTokenizer tokenizer = new StringTokenizer(msgEvent, ":");
            switch(tokenizer.nextToken()){
                case "TEMP": 
                    this.gui.updateTemperature(Integer.parseInt(tokenizer.nextToken()));
                    break;

                case "STATE":
                    final String state = tokenizer.nextToken();
                    this.gui.updateState(state);
                    break;

                case "NUMBER":
                    this.gui.updateWashingNumber(Integer.parseInt(tokenizer.nextToken()));
                    break;
                    
                case "MAINTENANCE":
                    String msg = tokenizer.nextToken();
                    this.channelMonitor.sendMessage(msg);
                    break;
        }
    }
}
