#include <Arduino.h>
#include <stdlib.h>
#include "tasks/MqttManager.h"
#include "config.h"
#include "devices/Sonar.h"

void MqttManager :: setup_wifi() {
    delay(10);
    neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0); // Set red led #F00 ==> rgb(F, 0, 0)
    Serial.println(String("Connecting to ") + ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    // Tries to connect to wifi until it succeeds
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(WiFi.status());
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    neopixelWrite(RGB_BUILTIN, 0, RGB_BRIGHTNESS, 0); // Set green led #0F0 ==> rgb(0, F, 0)
}

void MqttManager :: callback(char* topic, byte* payload, unsigned int length) {
    Serial.println(String("Message arrived on [") + topic + "] len: " + length);
    char buffer[length + 1]; 
    memcpy(buffer, payload, length); // Copy message into the buffer
    buffer[length] = '\0'; // Set end character
    Serial.print("Payload: ");
    Serial.println(buffer);
    float f_temp = atof(buffer); // Convert string to float to find frequency
    frequency = f_temp; // set frequency

    Serial.print("Frequenza arrivata: ");
    Serial.println(frequency);
}

void MqttManager :: reconnect() {
  neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0); // Red
  while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      
      String clientId = String("esiot-2122-client-")+String(random(0xffff), HEX);

      if (client.connect(clientId.c_str())) {
        Serial.println("connected");
        client.subscribe(frequency_topic); // Attempt to connect to frequency topic
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
      
      delay(5000);
    }
  }
  neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // Green
}

void MqttManager :: send_message(Sonar *sonar) {
  for (;;) {
    if (!client.connected()) {
      reconnect(); // Try to reconnect if not already connected
    }
    client.loop();
    String message = String(sonar->get_distance());
    message.toCharArray(msg, MSG_BUFFER_SIZE);
    Serial.println(String("Publishing message: ") + msg);
    
    client.publish(water_topic, msg); // Publish water opening level on water topic
    vTaskDelay(pdMS_TO_TICKS(frequency)); // Wait
  }  
}

void MqttManager :: init() {
  digitalWrite(RGB_BUILTIN, HIGH);
  setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); // Set action on message receive
}
