package river.monitoring.service.http;

import java.util.Optional;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.CorsHandler;
import river.monitoring.service.api.DashboardCommunicator;
import river.monitoring.service.api.SystemModeHandler;
import river.monitoring.service.common.DataPoint;
import river.monitoring.service.common.SystemMode;

public class HttpDashboardComm extends AbstractVerticle implements DashboardCommunicator {
    private final static int STATUS_OK = 200;
    private final static int STATUS_FORBIDDEN = 403;
    private final static int STATUS_RESOURCE_NOT_FOUND = 404;
    private final static int PORT = 8080;

    private Optional<DataPoint> data = Optional.empty();
    private Optional<Integer> valveOpening = Optional.empty();
    
    private final SystemModeHandler modeHandler;

    public HttpDashboardComm(final Vertx vertx, final SystemModeHandler modeHandler) {
        this.modeHandler = modeHandler;
        vertx.deployVerticle(this);
    }
    
    public HttpDashboardComm(final SystemModeHandler modeHandler) {
        this(Vertx.vertx(), modeHandler);
    }

    @Override
    public void start() throws Exception {
        // Create a Router
        Router router = Router.router(vertx);

        // CORS handler
        CorsHandler corsHandler = CorsHandler.create("*"); // Allow requests from any origin

        // Mount the CORS handler
        router.route().handler(corsHandler);

        // Mount the handler for all incoming requests at application/data for every HTTP request
        router.route("api/data").handler(this::handleGetData);

        router.route("api/mode").handler(this::handleRemoteControlRequest);

        router.route("api/valve").handler(this::setValveOpening);

        // Create the HTTP server
        vertx.createHttpServer()
                // Handle every request using the router
                .requestHandler(router)
                // Start listening
                .listen(PORT)
                // Print the port
                .onSuccess(server -> System.out.println("HTTP server started on port " + server.actualPort()));
    }

    public void addNewData(final DataPoint data) {
        this.data = Optional.of(data);
    }

    private void handleGetData(final RoutingContext context) {
        String address = context.request().connection().remoteAddress().toString();
        // Get the query parameter "name"
        log("REQUEST FROM: " + address);
        log("DATA: " + context.request().params());

        // Check if data is present
        if (data.isPresent()) {
            // Process data if present
            context.response()
                    .putHeader("content-type", "api/json")
                    .end(data.get().getAsJson().encodePrettily());
        } else {
            // Return error if data is not present
            context.fail(STATUS_RESOURCE_NOT_FOUND); // Set error code 404, data not found
        }
    }
    
    private void handleRemoteControlRequest(final RoutingContext context) {
        // Get the address of the request
        String address = context.request().connection().remoteAddress().toString();
        // Get the query parameter "name"
        log("REQUEST FROM: " + address);
        log("DATA: " + context.request().params());

        final boolean success = modeHandler.changeMode(SystemMode.REMOTE);
        final int statusCode = success ? STATUS_OK : STATUS_FORBIDDEN; // If mode is changed successfully then 200(ok) is setted as status code, otherwise 403(forbidden) is setted
        context.response().setStatusCode(statusCode).end();
    }
    
    private void setValveOpening(final RoutingContext context) {
        // Get the address of the request
        String address = context.request().connection().remoteAddress().toString();
        // Get the query parameter "name"
        log("REQUEST FROM: " + address);
        log("DATA: " + context.request().params());

        var body = context.body().asJsonObject();
        if (body != null && body.containsKey("VALVE_OPENING")) {
            this.valveOpening = Optional.of(body.getInteger("VALVE_OPENING"));
        } else {
            log("Errore: Parametro VALVE_OPENING mancante nella richiesta.");
        }
    }

    private void log(final String message) {
        System.out.println("[HTTP_COMMUNICATOR]: " + message);
    }

    @Override
    public Optional<Integer> getValveOpening() {
        return this.valveOpening;
    }

    @Override
    public void updateData(Optional<DataPoint> data) {
        this.data = data;
    }
}
