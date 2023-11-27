package smart.car.washing.gui;

import javax.swing.JPanel;

import java.awt.Color;
import java.awt.Graphics;

/**
 * JPanel subclass representing a graphical representation of temperature.
 * The temperature is displayed as a vertical bar within the panel, with
 * a color indicating whether it exceeds a specified threshold.
 */
class TemperaturePanel extends JPanel {
    
    private int temperature;

    /**
     * Sets the temperature value and triggers a repaint of the panel.
     *
     * @param temperature The temperature value to be displayed.
     */
    public void setTemperature(int temperature) {
        this.temperature = temperature;
        repaint();
    }

    /**
     * Overrides the paintComponent method to customize the appearance of the panel.
     *
     * @param g The Graphics object used for painting.
     */
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        int width = getWidth();
        int height = getHeight();
        g.setColor(Color.BLACK);
        g.fillRoundRect(width / 2 - 10, 50, 20, height - 100, 20, 20);
        if (temperature > 27) {
            g.setColor(Color.RED);
        } else {
            g.setColor(Color.GREEN);
        }

        int temperatureHeight = (int) ((height - 100) * (temperature / 100.0));
        g.fillRoundRect(width / 2 - 10, height - 50 - temperatureHeight, 20, temperatureHeight, 20, 20);

        g.setColor(Color.BLACK);
        g.drawString(temperature + "°C", width / 2 - 20, height -60);
    }
}
