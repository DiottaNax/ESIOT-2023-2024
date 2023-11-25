package smart.car.washing.controller;

import java.util.StringTokenizer;

import smart.car.washing.gui.ConsoleGui;

public class ControllerImpl implements Controller {
    private final ConsoleGui gui;

    public ControllerImpl(final ConsoleGui gui) {
        this.gui = gui;
    }
    
    public void notifyEvent(final String msgEvent) {
            StringTokenizer tokenizer = new StringTokenizer(msgEvent,":");
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
        }
    }
}
