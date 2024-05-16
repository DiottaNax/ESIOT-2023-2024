package river.monitoring.service.mqtt;

import java.util.Optional;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.netty.util.CharsetUtil;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;
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
                connectResult -> {
                    if (connectResult.succeeded()) {
                        log("Frequency publisher connected");

                        // Subscribe to the water level topic
                        frequencyPublisher.subscribe(FREQUENCY_TOPIC, 0); // QoS level 0
                    } else {
                        log("Failed to connect Frequency publisher: " + connectResult.cause().getMessage());
                    }
                });
        // Connect a subscriber for receiving water level readings
        this.waterLevelSubscriber.connect(1883, BROKER_ADDRESS,
                connectResult -> {
                    if (connectResult.succeeded()) {
                        log("Water Level subscriber connected");

                        // Subscribe to the water level topic
                        waterLevelSubscriber.subscribe(WATER_LEVEL_TOPIC, 0); // QoS level 0

                        // Handle incoming water level messages
                        waterLevelSubscriber.publishHandler(this::hanldeNewWaterLevel);
                    } else {
                        log("Failed to connect Water Level subscriber :" + connectResult.cause().getMessage());
                    }
                });
    }

    // Handler for new water level measurement in water level topic
    private void hanldeNewWaterLevel(final MqttPublishMessage message) {
        try {
            var wLevel = Double.parseDouble(message.payload().toString(CharsetUtil.US_ASCII));
            this.waterLevel = Optional.of(wLevel);
            //log("Parsed new water level: " + waterLevel.get());
        } catch (NumberFormatException e) {
            this.waterLevel = Optional.empty();
            //log("Failed to parse double, message was:" + message.payload().toString(CharsetUtil.US_ASCII));
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
}
