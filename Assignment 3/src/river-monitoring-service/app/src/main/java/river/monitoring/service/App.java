/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package river.monitoring.service;

import river.monitoring.service.core.RiverMonitoringService;
import river.monitoring.service.core.SystemModeHandlerImpl;

public class App {

    public static void main(String[] args) throws Exception {
        new RiverMonitoringService(args[0]).run();
    }
}
