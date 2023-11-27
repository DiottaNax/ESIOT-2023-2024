package smart.car.washing.gui;

import java.lang.Math;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.BorderLayout;
import java.awt.Toolkit;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import smart.car.washing.controller.Controller;

/**
 * The SmartCarWashingDashboard class represents the graphical user interface
 * for a smart car washing system. It displays temperature, washing number,
 * current state, and allows performing maintenance actions.
 */
public class SmartCarWashingDashboard extends JFrame implements Dashboard {
    private static int PROPORTION = 2;
    private JPanel mainPanel;
    private TemperaturePanel temp = new TemperaturePanel();
    private JLabel washingNumber = new JLabel();
    private JLabel state = new JLabel();
    private final JButton maintenanceButton;

    /**
     * Constructor for the SmartCarWashingDashboard.
     */
    public SmartCarWashingDashboard() {

        mainPanel = new JPanel();
        JPanel centerPanel = new JPanel();
        centerPanel.setBackground(Color.LIGHT_GRAY);
        centerPanel.setLayout(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;

        JPanel northPanel = new JPanel();
        northPanel.setLayout(new BoxLayout(northPanel, BoxLayout.Y_AXIS));
        northPanel.setBackground(Color.LIGHT_GRAY);

        mainPanel.setBackground(Color.BLACK);
        this.mainPanel.setLayout(new BorderLayout());

        EmptyBorder border = new EmptyBorder(10, 10, 10, 10);
        state.setText("Current State: CAR_WAITING");
        washingNumber.setText("Current Number: 0");
        state.setBorder(border);
        washingNumber.setBorder(border);

        this.setLayout(new GridLayout(1, 2));
        int sh = (int) Toolkit.getDefaultToolkit().getScreenSize().getHeight() / PROPORTION;
        int sw = (int) Toolkit.getDefaultToolkit().getScreenSize().getWidth() / (PROPORTION + 1);
        this.setSize(sw, sh);

        temp.setSize(new Dimension(sw / 3, sh));
        temp.setBackground(Color.DARK_GRAY);

        maintenanceButton = new JButton("Maintenance Done");
        maintenanceButton.setEnabled(false);
        maintenanceButton.setPreferredSize(new Dimension(sw / 3, sh / 10));
        this.mainPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));
        centerPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));
        this.mainPanel.add(centerPanel, BorderLayout.CENTER);
        this.mainPanel.add(northPanel, BorderLayout.NORTH);
        this.add(mainPanel);
        this.add(temp);
        centerPanel.add(maintenanceButton);
        northPanel.add(washingNumber, BorderLayout.NORTH);
        northPanel.add(state, BorderLayout.SOUTH);

        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLocation(new Point((int) Math.round(sw / 1.2), ((int) sh / 2)));
        this.setVisible(true);
    }

    /**
     * Updates the displayed temperature on the dashboard.
     *
     * @param temperature The current temperature reading from the system.
     */
    public void updateTemperature(final int temperature) {
        this.temp.setTemperature(temperature);
    }

    /**
     * Updates the displayed washing number on the dashboard.
     *
     * @param number The current washing number or identifier.
     */
    public void updateWashingNumber(final int number) {
        this.washingNumber.setText("Current Number: " + number);
    }

    /**
     * Updates the displayed state on the dashboard.
     *
     * @param state A string representing the current state of the car washing system.
     */
    public void updateState(final String state) {
        this.state.setText("Current State: " + state);
        if (state.equals("MAINTENANCE")) {
            this.maintenanceButton.setEnabled(true);
        }
    }

    /**
     * Attaches a controller to the dashboard for event handling.
     *
     * @param controller The controller to be attached for event handling.
     */
    public void attachController(final Controller controller) {
        maintenanceButton.addActionListener(e -> {
            controller.notifyEvent("MAINTENANCE:DONE");
            maintenanceButton.setEnabled(false);
        });
    }
}
