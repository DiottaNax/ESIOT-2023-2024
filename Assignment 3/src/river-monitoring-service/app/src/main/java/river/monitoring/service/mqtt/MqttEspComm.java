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

/*
 * MQTTCommunicator is responsible for handling MQTT communication for water level readings and frequency updates.
 */
public class MqttEspComm extends AbstractVerticle implements EspCommunicator {

    // Broker address and topic names for MQTT communication
    private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
    private final static String WATER_LEVEL_TOPIC = "water-level-iot";
    private final static String FREQUENCY_TOPIC = "frequency-iot";

    // MQTT clients for publishing frequency and subscribing to water level
    private MqttClient waterLevelSubscriber;
    private MqttClient frequencyPublisher;
    private Optional<Double> waterLevel = Optional.empty();

	/**
	 * Creates a MQTTCommunicator instance using the specified vertx instance
	 */
	public MqttEspComm(final Vertx vertx) {
		this.frequencyPublisher = MqttClient.create(vertx);
		this.waterLevelSubscriber = MqttClient.create(vertx);
		vertx.deployVerticle(this);
	}

	/**
	 * Creates a MQTTCommunicator instance using a non clustered instance with default options
	 */
	public MqttEspComm() {
		this(Vertx.vertx());
	}

    @Override
    public void start() {
        // ------------------ Frequency Publisher Setup ------------------
        // Connect a publisher for sending frequency updates
        this.frequencyPublisher.connect(1883, BROKER_ADDRESS, connectResult -> {
            if (connectResult.succeeded()) {
                log("Frequency publisher connected");
            } else {
                log("Failed to connect Frequency Publisher: " + connectResult.cause().getMessage());
            }
        });

        // ------------------ Water Level Subscriber Setup ------------------
        // Connect a subscriber for receiving water level readings
        this.waterLevelSubscriber.connect(1883, BROKER_ADDRESS, connectResult -> {
            if (connectResult.succeeded()) {
                log("Water Level subscriber connected");

                // Handle incoming water level messages
                waterLevelSubscriber.publishHandler(this::hanldeNewWaterLevel);

                // Subscribe to the water level topic
                waterLevelSubscriber.subscribe(WATER_LEVEL_TOPIC, 2); // QoS level 2
            } else {
                log("Failed to connect Water Level Subscriber: " + connectResult.cause().getMessage());
            }
        });
    }

    private void hanldeNewWaterLevel(final MqttPublishMessage message) {
        try{
            var wLevel = Double.parseDouble(message.payload().toString(CharsetUtil.US_ASCII));
            this.waterLevel = Optional.of(wLevel);
        } catch (NumberFormatException e) {
            log("Failed to parse double");
        }
    }

    // Publish a new frequency value to the ESP32
    @Override
    public void setFrequence(final int frequence) {
        frequencyPublisher.publish(FREQUENCY_TOPIC,
                Buffer.buffer(Integer.toString(frequence), "ASCII"),
                MqttQoS.AT_LEAST_ONCE, false, false);
    }

    @Override
    public Optional<Double> getWaterLevel() {
        return this.waterLevel;
    }

    // Logging helper method
    private void log(String msg) {
        System.out.println("[MQTT COMMUNICATOR] " + msg);
    }
}
