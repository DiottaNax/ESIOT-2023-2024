#include <Arduino.h>
#include "MqttManager.h"
#include "SonarTask.h"
#include <stdlib.h>

void MqttManager :: setup_wifi() {
    delay(10);
    Serial.println(String("Connecting to ") + ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(WiFi.status());
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void MqttManager :: callback(char* topic, byte* payload, unsigned int length) {
    Serial.println(String("Message arrived on [") + topic + "] len: " + length);
    char buffer[length + 1]; 
    memcpy(buffer, payload, length); 
    buffer[length] = '\0'; 
    Serial.print("Payload: ");
    Serial.println(buffer);
    float f_temp = atof(buffer);
    if(f_temp > 100.00) {
        frequency = f_temp;
    } else {
        frequency = 500;
    }

    Serial.print("Frequenza arrivata: ");
    Serial.println(frequency);
}

void MqttManager :: reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        
        String clientId = String("esiot-2122-client-")+String(random(0xffff), HEX);

        if (client.connect(clientId.c_str())) {
        Serial.println("connected");
        client.subscribe(frequency_topic);
        } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        
        delay(5000);
      }
    }
}

void MqttManager :: send_message(SonarTask *sonar) {
  for (;;) {
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    String message = String(sonar->get_distance());
    message.toCharArray(msg, MSG_BUFFER_SIZE);
    Serial.println(String("Publishing message: ") + msg);
    
    client.publish(water_topic, msg);
    vTaskDelay(pdMS_TO_TICKS(frequency));
  }  
}

void MqttManager :: init() {
    setup_wifi();
    randomSeed(micros());
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}
