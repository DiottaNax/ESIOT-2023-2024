package smart.car.washing.gui;

import java.util.logging.Level;
import java.util.logging.Logger;

import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;

public final class DashboardLogger {

    private static final Logger logger = Logger.getLogger("SmartCarWasgingLogger");

    private DashboardLogger() {
    }

    public static void showError(final Exception e, final Level level) {
        SwingUtilities.invokeLater(() -> {
            JOptionPane.showMessageDialog(null, e.getMessage(), "Errore", JOptionPane.ERROR_MESSAGE);
        });

        logger.log(level, e.getMessage(), e);
    }
}
