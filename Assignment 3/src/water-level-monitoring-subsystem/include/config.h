#ifndef __CONFIG__
#define __CONFIG__

#include <WiFi.h>
#include <PubSubClient.h>

#define MSG_BUFFER_SIZE  50

/* wifi network info */
const char* ssid = "palladipelo";   // Specifies the SSID of the Wi-Fi network.
const char* password = "12345678";  // Specifies the password of the Wi-Fi network.

/* MQTT client management */
WiFiClient espClient;               // Represents the Wi-Fi client for ESP32/ESP8266.
PubSubClient client(espClient);     // Represents the MQTT client instance.

/* MQTT server address */
const char* mqtt_server = "broker.mqtt-dashboard.com"; // Represents the MQTT client instance.

char msg[MSG_BUFFER_SIZE];          // Buffer for storing MQTT messages.

/* MQTT topic */
const char* water_topic = "water_level";    // Indicates the MQTT topic for water level.
const char* frequency_topic = "frequency";  // Indicates the MQTT topic for frequency.
float frequency = 5000;                     // Default value for frequency.

#endif