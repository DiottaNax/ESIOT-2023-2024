package smart.car.washing.gui;

import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

/**
 * Utility class for logging errors and displaying error messages on the dashboard.
 */
public final class DashboardLogger {

    private static final Logger logger = Logger.getLogger("SmartCarWasgingLogger");

    /**
     * Private constructor to prevent instantiation of the utility class.
     */
    private DashboardLogger() {
    }

    /**
     * Displays an error message on the dashboard and logs the error.
     *
     * @param e The exception for which the error message is displayed.
     * @param level The logging level for the error.
     */
    public static void showAndLogError(final Exception e, final String title, final Level level) {
        SwingUtilities.invokeLater(() -> {
            JOptionPane.showMessageDialog(null, e.getMessage(), title, JOptionPane.ERROR_MESSAGE);
        });

        logger.log(level, e.getMessage(), e);
    }
}
