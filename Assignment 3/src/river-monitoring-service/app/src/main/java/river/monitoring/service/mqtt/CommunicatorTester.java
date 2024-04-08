package river.monitoring.service.mqtt;

import io.vertx.core.AbstractVerticle;
import io.vertx.mqtt.MqttClient;

/*
 * MQTT Agent
 */
public class CommunicatorTester extends AbstractVerticle {
	
	private static final String BROKER_ADDRESS = "broker.mqtt-dashboard.com";
	private final static String TOPIC_NAME = "frequency-iot";

	@Override
	public void start() {
		MqttClient client = MqttClient.create(vertx);

		client.connect(1883, BROKER_ADDRESS, c -> {

			log("connected");

			log("subscribing...");
			client.publishHandler(s -> {
				System.out.println("There are new message in topic: " + s.topicName());
				System.out.println("Content(as string) of the message: " + s.payload().toString());
				System.out.println("QoS: " + s.qosLevel());
			})
					.subscribe(TOPIC_NAME, 2);

			log("publishing a msg");
		});
	}

	private void log(String msg) {
		System.out.println("[MQTT AGENT] "+msg);
	}

}