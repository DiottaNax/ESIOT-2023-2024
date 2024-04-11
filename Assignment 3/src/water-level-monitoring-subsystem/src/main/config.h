#ifndef __CONFIG__
#define __CONFIG__

#include <WiFi.h>
#include <PubSubClient.h>

#define MSG_BUFFER_SIZE  50

/* wifi network info */
const char* ssid = "palladipelo"; 
const char* password = "12345678";

/* MQTT client management */
WiFiClient espClient; 
PubSubClient client(espClient); 

/* MQTT server address */
const char* mqtt_server = "broker.mqtt-dashboard.com"; 

unsigned long lastMsgTime = 0; 
char msg[MSG_BUFFER_SIZE]; 

/* MQTT topic */
const char* water_topic = "water_level"; /*fatto*/
const char* frequency_topic = "frequency"; /*fatto*/
float frequency = 500;

#endif