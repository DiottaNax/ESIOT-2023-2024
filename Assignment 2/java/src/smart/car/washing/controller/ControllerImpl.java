package smart.car.washing.controller;

import java.util.StringTokenizer;

import smart.car.washing.controller.Controller;

public class ControllerImpl implements Controller {
    private SerialCommChannel channel;
    private ConsoleGui gui;

    ControllerImpl(SerialCommChannel channel,ConsoleGui gui) {
        this.channel = channel;
        this.gui = gui;
        this.gui.updateButtonListener(this);
    }
    void notifyEvent(String msgEvent) {
            StringTokenizer tokenizer = new StringTokenizer(msgEvent,":");
            switch(tokenizer.nextToken()){
                case "TEMP": 
                    this.gui.updateTemperature(String.parseInt(tokenizer.nextToken()));
                    break;
                case "STATE":
                    String state = tokenizer.nextToken();
                    this.gui.updateState(state);
                    if (state.compareTo("MAINTENANCE")) {
                        this.gui.updateButtonState(true);
                    } else if (state.compareTo("MAINTENANCE")) {
                        this.gui.updateButtonState(false);
                    }
                    break;
                case "NUMBER":
                    this.gui.updateWashingNumber(String.parseInt(tokenizer.nextToken()));
                    break;
                case "MAINTENANCE":
                    channel.sendMsg("MAINTENANCE");
                    break;
        }
    }
}
