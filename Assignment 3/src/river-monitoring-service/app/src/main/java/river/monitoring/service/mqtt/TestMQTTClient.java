package river.monitoring.service.mqtt;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;

public class TestMQTTClient extends AbstractVerticle {
	
	public static void main(String[] args) throws Exception {		
		Vertx vertx = Vertx.vertx();
		CommunicatorTester agent = new CommunicatorTester();
		vertx.deployVerticle(agent);
		MQTTCommunicator communicator = new MQTTCommunicator();
		vertx.deployVerticle(communicator);

		Thread.sleep(3000);
		for (int i = 0; i < 5; i++) {
			communicator.setFrequence(i * 1000);
			Thread.sleep(2000);
		}
	}
}
