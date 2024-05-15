package river.monitoring.service.http;

import java.util.Optional;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;
import river.monitoring.service.api.DashboardCommunicator;
import river.monitoring.service.api.SystemModeHandler;
import river.monitoring.service.common.DataPoint;
import river.monitoring.service.common.SystemMode;

/**
 * Handles communication with the dashboard via HTTP.
 * Implements {@link DashboardCommunicator} and extends {@link AbstractVerticle}.
 */
public class HttpDashboardComm extends AbstractVerticle implements DashboardCommunicator {
    private final static int STATUS_OK = 200;
    private final static int STATUS_FORBIDDEN = 403;
    private final static int STATUS_RESOURCE_NOT_FOUND = 404;
    private final static int PORT = 8080;

    private Optional<DataPoint> data = Optional.empty();
    private Optional<Integer> valveOpening = Optional.empty();

    private final SystemModeHandler modeHandler;

    /**
     * Constructs and deploys an HttpDashboardComm with the specified Vertx instance and mode handler.
     *
     * @param vertx       the Vertx instance.
     * @param modeHandler the system mode handler.
     */
    public HttpDashboardComm(final Vertx vertx, final SystemModeHandler modeHandler) {
        this.modeHandler = modeHandler;
        vertx.deployVerticle(this);
    }

    /**
     * Constructs and deploys an HttpDashboardComm with the default Vertx instance and mode handler.
     *
     * @param modeHandler the system mode handler.
     */
    public HttpDashboardComm(final SystemModeHandler modeHandler) {
        this(Vertx.vertx(), modeHandler);
    }

    @Override
    public void start() throws Exception {
        Router router = Router.router(vertx);

        router.route().handler(CorsHandler.create("*"));
        router.route().handler(BodyHandler.create());
        router.route("/api/data").handler(this::handleGetData);
        router.route("/api/mode").handler(this::handleRemoteControlRequest);
        router.route("/api/valve").handler(this::setValveOpening);

        vertx.createHttpServer()
                .requestHandler(router)
                .listen(PORT)
                .onSuccess(server -> log("HTTP server started on port " + server.actualPort()));
    }

    // Handler for data request from the dashboard at /api/data
    private void handleGetData(final RoutingContext context) {
        // Check if data is present
        if (this.data.isPresent()) {
            // Process data if present
            context.response()
                    .putHeader("content-type", "api/json")
                    .end(data.get().asJson().encodePrettily());
        } else {
            // Return error if data is not present
            context.response().setStatusCode(STATUS_RESOURCE_NOT_FOUND).end(); // Set error code 404, data not found
        }
    }

    // Handler for remote control requests at /api/mode
    private void handleRemoteControlRequest(final RoutingContext context) {
        // Get next mode
        final SystemMode nextMode = modeHandler.getCurrentMode().equals(SystemMode.REMOTE)
                ? SystemMode.AUTO
                : SystemMode.REMOTE;

        final boolean success = modeHandler.changeMode(nextMode); // If change mode is successfull
        final int statusCode = success ? STATUS_OK : STATUS_FORBIDDEN;

        context.response()
                .setStatusCode(statusCode)
                .end(this.modeHandler.getCurrentMode().asJson().encodePrettily()); // Send anyway current mode as json
    }

    // Handler for set valve opening request at /api/valve
    private void setValveOpening(final RoutingContext context) {
        log("setting valve, message content: " + context.body().asJsonObject());
        // Retrive the body of the request
        final var body = context.body().asJsonObject();
        // Ensure that the body contains VALVE_OPENING
        if (body != null && body.containsKey("VALVE_OPENING")) {
            // Parse int from the string passed by javascript
            try {
                final var openingPerc = Integer.parseInt(body.getString("VALVE_OPENING"));
                this.valveOpening = Optional.of(this.getAngleFromPerc(openingPerc));
            } catch (NumberFormatException e) {
                log("failed to cast valve opening");
            }
        } else {
            log("Error: VALVE_OPENING parameter missing in the request.");
        }
    }

    // Dashboard send a percentual which needs to be cast to an angle in order to set valve opening level
    private int getAngleFromPerc(int perc) {
        final var toAngle = 1.8; // Offset ==> angle = perc * 180 / 100
        return Math.toIntExact(Math.round(perc * toAngle));
    }

    @Override
    public Optional<Integer> getValveOpening() {
        return this.valveOpening;
    }

    @Override
    public void updateData(Optional<DataPoint> data) {
        this.data = data;
    }

    private void log(final String message) {
        System.out.println("[HTTP_COMMUNICATOR]: " + message);
    }
}
