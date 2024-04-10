#ifndef __MQTT_MANAGER__
#define __MQTT_MANAGER__

#define MSG_BUFFER_SIZE  50

#include <WiFi.h>
#include <PubSubClient.h>
#include "SonarTask.h"


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

class MqttManager {
  private:

  public:
    MqttManager();
    void init();
    void setup_wifi();
    static void callback(char* topic, byte* payload, unsigned int length);
    void reconnect(); 
    void send_message(SonarTask *sonar);
};

#endif