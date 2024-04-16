package river.monitoring.service.mqtt;

import java.util.Optional;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.netty.util.CharsetUtil;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.AsyncResult;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;
import io.vertx.mqtt.messages.MqttConnAckMessage;
import io.vertx.mqtt.messages.MqttPublishMessage;

import river.monitoring.service.api.EspCommunicator;

/**
 * Handles communication with the ESP32 device via MQTT.
 * Implements {@link EspCommunicator} and extends {@link AbstractVerticle}.
 */
public class MqttEspComm extends AbstractVerticle implements EspCommunicator {

    // Broker address and topic names for MQTT communication
    private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
    private final static String WATER_LEVEL_TOPIC = "water_level";
    private final static String FREQUENCY_TOPIC = "frequency";

    // MQTT clients for publishing frequency and subscribing to water level
    private MqttClient waterLevelSubscriber;
    private MqttClient frequencyPublisher;
    private Optional<Double> waterLevel = Optional.empty();

    /**
     * Constructs and deploys an MqttEspComm with the specified Vertx instance.
     *
     * @param vertx the Vertx instance.
     */
    public MqttEspComm(final Vertx vertx) {
        this.frequencyPublisher = MqttClient.create(vertx);
        this.waterLevelSubscriber = MqttClient.create(vertx);
        vertx.deployVerticle(this);
    }

    /**
     * Constructs and deploys an MqttEspComm with the default Vertx instance.
     */
    public MqttEspComm() {
        this(Vertx.vertx());
    }

    @Override
    public void start() {
        // Connect a publisher for sending frequency updates
        this.frequencyPublisher.connect(1883, BROKER_ADDRESS,
                connectResult -> logConnectResult("Frequency publisher", connectResult));
        // Connect a subscriber for receiving water level readings
        this.waterLevelSubscriber.connect(1883, BROKER_ADDRESS,
                connectResult -> logConnectResult("Water level subscriber", connectResult));
    }

    // Handler for new water level measurement in water level topic
    private void hanldeNewWaterLevel(final MqttPublishMessage message) {
        try {
            var wLevel = Double.parseDouble(message.payload().toString(CharsetUtil.US_ASCII));
            this.waterLevel = Optional.of(wLevel);
            log("Parsed new water level: " + waterLevel.get());
        } catch (NumberFormatException e) {
            log("Failed to parse double");
        }
    }

    // Handler to publish a new frequency value to the ESP32 in frequency topic
    @Override
    public void setFrequency(final int frequence) {
        log("Sending message \"" + frequence + "\"");
        frequencyPublisher.publish(FREQUENCY_TOPIC,
                Buffer.buffer(Integer.toString(frequence), "ASCII"),
                MqttQoS.AT_LEAST_ONCE, false, false);
    }

    @Override
    public Optional<Double> getWaterLevel() {
        return this.waterLevel;
    }

    // Logging helper methods
    private void log(final String msg) {
        System.out.println("[MQTT COMMUNICATOR] " + msg);
    }

    private void logConnectResult(final String clientName, AsyncResult<MqttConnAckMessage> connectResult) {
        if (connectResult.succeeded()) {
            log(clientName + " connected");

            // Handle incoming water level messages
            waterLevelSubscriber.publishHandler(this::hanldeNewWaterLevel);

            // Subscribe to the water level topic
            waterLevelSubscriber.subscribe(WATER_LEVEL_TOPIC, 2); // QoS level 2
        } else {
            log("Failed to connect " + clientName + ": " + connectResult.cause().getMessage());
        }
    }
}
