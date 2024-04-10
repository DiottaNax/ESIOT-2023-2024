package river.monitoring.service.mqtt;

import java.util.Optional;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;
import river.monitoring.service.api.ChannelObserver;

/*
 * MQTTCommunicator is responsible for handling MQTT communication for water level readings and frequency updates.
 */
public class MQTTCommunicator extends AbstractVerticle {

    // Broker address and topic names for MQTT communication
    private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
    private final static String WATER_LEVEL_TOPIC = "water-level-iot";
    private final static String FREQUENCY_TOPIC = "frequency-iot";

    // Observer for water level readings
    private Optional<ChannelObserver<Double>> observer = Optional.empty();

    // MQTT clients for publishing frequency and subscribing to water level
    private MqttClient waterLevelSubscriber;
    private MqttClient frequencyPublisher;

    @Override
    public void start() {
        // ------------------ Frequency Publisher Setup ------------------
        // Create and connect a publisher for sending frequency updates
        this.frequencyPublisher = MqttClient.create(vertx);
        this.frequencyPublisher.connect(1883, BROKER_ADDRESS, connectResult -> {
            if (connectResult.succeeded()) {
                log("Frequency publisher connected");
            } else {
                log("Failed to connect Frequency Publisher: " + connectResult.cause().getMessage());
            }
        });

        // ------------------ Water Level Subscriber Setup ------------------
        // Create and connect a subscriber for receiving water level readings
        this.waterLevelSubscriber = MqttClient.create(vertx);
        this.waterLevelSubscriber.connect(1883, BROKER_ADDRESS, connectResult -> {
            if (connectResult.succeeded()) {
                log("Water Level subscriber connected");

                // Handle incoming water level messages
                waterLevelSubscriber.publishHandler(m -> {
                    try {
                        // Parse water level value as a double
                        var waterLevel = Double.parseDouble(m.payload().toString("ASCII"));

                        // Notify the observer (if present)
                        observer.ifPresent(o -> o.notifyNewMessage(waterLevel));
                    } catch (NumberFormatException e) {
                        log("Failed to parse double in MQTTCommunicator");
                    }
                });

                // Subscribe to the water level topic
                waterLevelSubscriber.subscribe(WATER_LEVEL_TOPIC, 2); // QoS level 2
            } else {
                log("Failed to connect Water Level Subscriber: " + connectResult.cause().getMessage());
            }
        });
    }

    // Attach an observer to receive water level updates
    public void attachObserver(final ChannelObserver<Double> observer) {
        this.observer = Optional.of(observer);
    }

    // Publish a new frequency value to the ESP32
    public void setFrequence(final int frequence) {
        frequencyPublisher.publish(FREQUENCY_TOPIC,
                Buffer.buffer(Integer.toString(frequence), "ASCII"),
                MqttQoS.AT_LEAST_ONCE, false, false);
    }

    // Logging helper method
    private void log(String msg) {
        System.out.println("[MQTT COMMUNICATOR] " + msg);
    }
}
