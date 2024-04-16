package river.monitoring.service.http;

import java.util.Optional;
//import java.util.Random; // FOR TESTING

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.CorsHandler;
import river.monitoring.service.api.DashboardCommunicator;
import river.monitoring.service.api.SystemModeHandler;
import river.monitoring.service.common.DataPoint;
import river.monitoring.service.common.SystemMode;
//import river.monitoring.service.common.SystemState; //FOR TESTING

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

        // Mount the CORS handler
        //router.route().handler(BodyHandler.create());
        router.route().handler(CorsHandler.create("*")); // Allow requests from any origin
        // Mount the handler for incoming http request by the dashboard
        router.route("/api/data").handler(this::handleGetData);
        router.route("/api/mode").handler(this::handleRemoteControlRequest);
        router.route("/api/valve").handler(this::setValveOpening);

        log("creating http server");
        // Create the HTTP server
        vertx.createHttpServer()
                // Handle every request using the router
                .requestHandler(router)
                // Start listening
                .listen(PORT)
                // Print the port
                .onSuccess(server -> log("HTTP server started on port " + server.actualPort()));
    }

    private void handleGetData(final RoutingContext context) {
        // FOR TESTING WITHOUT ARDUINO OR ESP DECOMMENT BELOW
        /*double wLevel = new Random().nextDouble(1.7, 30.0);
        var testData = new DataPoint(this.modeHandler.getCurrentMode(), wLevel,
                SystemState.NORMAL.getValveOpening(), SystemState.NORMAL);
        var data = Optional.of(testData);*/

        // Check if data is present
        if (data.isPresent()) {
            // Process data if present
            context.response()
                    .putHeader("content-type", "api/json")
                    .end(data.get().asJson().encodePrettily());
        } else {
            // Return error if data is not present
            context.response().setStatusCode(STATUS_RESOURCE_NOT_FOUND).end(); // Set error code 404, data not found
        }
    }
    
    private void handleRemoteControlRequest(final RoutingContext context) {
        // Get the next mode to set, if the current is AUTO the next is REMOTE and vice-versa 
        final SystemMode nextMode = modeHandler.getCurrentMode().equals(SystemMode.REMOTE)
                ? SystemMode.AUTO
                : SystemMode.REMOTE;
 
        final boolean success = modeHandler.changeMode(nextMode);
        // If mode is changed successfully then 200(ok) is setted as status code, otherwise 403(forbidden) is setted
        final int statusCode = success ? STATUS_OK : STATUS_FORBIDDEN;
        log(this.modeHandler.getCurrentMode().asJson().encodePrettily());
        // End the request with the correct status code and the current system mode wrapped into a json
        context.response()
                .setStatusCode(statusCode)
                .end(this.modeHandler.getCurrentMode().asJson().encodePrettily());
    }
    
    private void setValveOpening(final RoutingContext context) {
        log("trying to set valve, message content: " + context.request().body());
        var body = context.body().asJsonObject();
        if (body != null && body.containsKey("VALVE_OPENING")) {
            this.valveOpening = Optional.of(body.getInteger("VALVE_OPENING"));
        } else {
            log("Errore: Parametro VALVE_OPENING mancante nella richiesta.");
        }
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
