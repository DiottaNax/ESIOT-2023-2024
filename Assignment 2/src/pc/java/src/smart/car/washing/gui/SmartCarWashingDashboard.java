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
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
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
    private TemperaturePanel temperaturePanel = new TemperaturePanel();
    private JLabel washingNumber = new JLabel();
    private JLabel state = new JLabel();
    private final JButton maintenanceButton;
    private int criticTemp = 30;

    /**
     * Constructor for the SmartCarWashingDashboard.
     */
    public SmartCarWashingDashboard() {

        //Set Frame layout and dimension 
        this.setLayout(new GridLayout(1, 2));
        int sh = (int) Toolkit.getDefaultToolkit().getScreenSize().getHeight() / PROPORTION;
        int sw = (int) Toolkit.getDefaultToolkit().getScreenSize().getWidth() / (PROPORTION + 1);
        this.setSize(sw, sh);

        //Panel
        //Main Panel for northPanel and centerPanel
        mainPanel = new JPanel();
        mainPanel.setBackground(Color.BLACK);
        this.mainPanel.setLayout(new BorderLayout());
        //centerPanel for the maintenanceButton, use GridBagLayout in order to center the button
        JPanel centerPanel = new JPanel();
        centerPanel.setBackground(Color.LIGHT_GRAY);
        centerPanel.setLayout(new GridBagLayout()); 
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        maintenanceButton = new JButton("Maintenance Done");
        maintenanceButton.setEnabled(false);
        maintenanceButton.setPreferredSize(new Dimension(sw / 3, sh / 10));
        //northPanel for the number of washes performed and the washing status
        JPanel northPanel = new JPanel();
        northPanel.setLayout(new BoxLayout(northPanel, BoxLayout.Y_AXIS));
        northPanel.setBackground(Color.LIGHT_GRAY);
        EmptyBorder border = new EmptyBorder(10, 10, 10, 10);
        state.setText("State: ---");
        washingNumber.setText("Washing completed: ---");
        state.setBorder(border);
        washingNumber.setBorder(border);
        //temperaturePanel for the temperature bar
        temperaturePanel.setSize(new Dimension(sw / 3, sh));
        temperaturePanel.setBackground(Color.DARK_GRAY);

        this.mainPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));
        centerPanel.setBorder(BorderFactory.createLineBorder(Color.BLACK, 2));

        this.mainPanel.add(centerPanel, BorderLayout.CENTER);
        this.mainPanel.add(northPanel, BorderLayout.NORTH);
        this.add(mainPanel);
        this.add(temperaturePanel);
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
        this.temperaturePanel.setTemperature(temperature);
        if (temperature >= 30) {
            criticTemp = temperature;
        }
    }

    /**
     * Updates the displayed washing number on the dashboard.
     *
     * @param number The current washing number or identifier.
     */
    public void updateWashingNumber(final int number) {
        this.washingNumber.setText("Washing completed: " + number);
    }

    /**
     * Updates the displayed state on the dashboard.
     *
     * @param state A string representing the current state of the car washing system.
     */
    public void updateState(final CarWashingState state) {
        this.state.setText("State: " + state.getStateName());
        if (state.equals(CarWashingState.MAINTENANCE)) {
            this.maintenanceButton.setEnabled(true);
            // Display a warning message to inform about maintenance
            SwingUtilities.invokeLater(() -> {
                JOptionPane.showMessageDialog(this,
                        "During car washing a temperature of " + criticTemp
                                + "C° was detectd. \n Please control the washing area, maintenance is required.",
                        "Maintenance required", JOptionPane.WARNING_MESSAGE);
            });
        } else if (this.maintenanceButton.isEnabled()) {
            this.maintenanceButton.setEnabled(false);
        }

        if (!state.equals(CarWashingState.MAINTENANCE) || !state.equals(CarWashingState.CAR_WASHING)) {
            this.updateTemperature(0);
        }
    }

    /**
     * Attaches a controller to the dashboard for event handling.
     * Specifically used to handle the event when the maintenance button is pressed.
     *
     * @param controller The controller to be attached for event handling.
     */
    public void attachController(final Controller controller) {
        maintenanceButton.addActionListener(e -> {
            controller.notifyEvent("DONE");
            maintenanceButton.setEnabled(false);
        });
    }
}
