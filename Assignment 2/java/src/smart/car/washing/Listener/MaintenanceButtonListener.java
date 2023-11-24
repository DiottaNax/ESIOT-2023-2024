package Listener;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import smart.car.washing.controller.Controller;

public class MaintenanceButtonListener implements ActionListener{
    Controller controller;

    public MaintenanceButtonListener(Controller controller) {
        this.controller = controller;
    }

    public void action() {
        this.controller.notifyEvent("MAINTENANCE");
    }
}
