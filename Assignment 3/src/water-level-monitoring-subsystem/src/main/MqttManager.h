#ifndef __MQTT_MANAGER__
#define __MQTT_MANAGER__

#include <Arduino.h>
#include "SonarTask.h"

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