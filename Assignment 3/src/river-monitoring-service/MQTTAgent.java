package esiot.module_lab_3_2;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.buffer.Buffer;
import io.vertx.mqtt.MqttClient;

/*
 * MQTT Agent
 */
public class MQTTAgent extends AbstractVerticle {

    private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
    private static final String WATER_LEVEL_TOPIC = "water_level";
    private static final String FREQUENCY_TOPIC = "frequency";

    public MQTTAgent() {
    }

    @Override
    public void start() {
        MqttClient client = MqttClient.create(vertx);

        client.connect(1883, BROKER_ADDRESS, c -> {
            if (c.succeeded()) {
                System.out.println("Connected to MQTT broker");
                client.subscribe(WATER_LEVEL_TOPIC, 2);
                System.out.println("Subscribed to topic: " + WATER_LEVEL_TOPIC);
            } else {
                System.out.println("Failed to connect to MQTT broker");
            }

            client.publishHandler(s -> {
                System.out.println("There are new message in topic: " + s.topicName());
                System.out.println("Content(as string) of the message: " + s.payload().toString());
                System.out.println("QoS: " + s.qosLevel());

                if (s.topicName().equals(WATER_LEVEL_TOPIC)) {
                    float waterLevel = Float.parseFloat(s.payload().toString());
                    float frequency = calculateFrequency(waterLevel);
                    publishFrequency(client, frequency);
                }
            });
        });

    }

    private float calculateFrequency(float waterLevel) {
        // TODO
        return waterLevel + 100;
    }

    private void publishFrequency(MqttClient client, float frequency) {
        client.publish(FREQUENCY_TOPIC,
                Buffer.buffer(Float.toString(frequency)),
                MqttQoS.AT_LEAST_ONCE,
                false,
                false,
                ar -> {
                    if (ar.succeeded()) {
                        System.out.println("Published frequency: " + Buffer.buffer(Float.toString(frequency))
                                + " to topic: " + FREQUENCY_TOPIC);
                    } else {
                        System.out.println("Failed to publish frequency");
                    }
                });
    }

}