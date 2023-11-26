package smart.car.washing.gui;

import java.lang.Math;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Point;
import java.awt.BorderLayout;
import java.awt.Toolkit;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import smart.car.washing.controller.Controller;

public class SmartCarWashingDashboard extends JFrame implements Dashboard {
    private static int PROPORTION = 2;
    private JPanel mainPanel;
    private JLabel temp = new JLabel();
    private JLabel washingNumber = new JLabel();
    private JLabel state = new JLabel();
    private final JButton maintenanceButton;

    public SmartCarWashingDashboard() {
        mainPanel = new JPanel();
        JPanel centerPanel = new JPanel();
        centerPanel.setBackground(Color.LIGHT_GRAY);
        centerPanel.setLayout(new FlowLayout());
        JPanel northPanel = new JPanel();
        northPanel.setLayout(new FlowLayout());
        northPanel.setBackground(Color.LIGHT_GRAY);
        JPanel southPanel = new JPanel();
        southPanel.setLayout(new FlowLayout());
        southPanel.setBackground(Color.LIGHT_GRAY);

        int sh = (int) Toolkit.getDefaultToolkit().getScreenSize().getHeight() / PROPORTION;
        int sw = (int) Toolkit.getDefaultToolkit().getScreenSize().getWidth() / PROPORTION;
        mainPanel.setSize(sw, sh);
        mainPanel.setBackground(Color.BLACK);
        this.mainPanel.setLayout(new BorderLayout());

        washingNumber.setText("Current Number: 0");
        temp.setText("Current Temperature: -");

        state.setText("Current State: CAR_WAITING");

        maintenanceButton = new JButton("Maintenance Done");
        maintenanceButton.setEnabled(false);

        this.mainPanel.add(southPanel, BorderLayout.SOUTH);
        this.mainPanel.add(centerPanel, BorderLayout.CENTER);
        this.mainPanel.add(northPanel, BorderLayout.NORTH);
        this.add(mainPanel);
        southPanel.add(maintenanceButton);
        centerPanel.add(temp);
        northPanel.add(washingNumber);
        northPanel.add(state);
        this.setSize(sw, sh);
        /**
         * Comment this.pack() to have a bigger gui
         */
        this.pack();
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLocation(new Point((int)Math.round(sw / 1.2), ((int) sh / 2)));
        this.setVisible(true);
    }

    public void updateTemperature(final int temperature) {
        this.temp.setText("Current Temperrature: "+temperature);
    }

    public void updateWashingNumber(final int number) {
        this.washingNumber.setText("Current Number: "+number);
    }

    public void updateState(final String state) {
        this.state.setText("Current State: " + state);
        if (state.equals("MAINTENANCE")) {
            this.maintenanceButton.setEnabled(true);
        }
    }

    public void attachController(final Controller controller) {
        maintenanceButton.addActionListener(e -> {
            controller.notifyEvent("MAINTENANCE:DONE");
            maintenanceButton.setEnabled(false);
        });
    }
}
