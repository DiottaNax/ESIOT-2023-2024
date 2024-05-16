#ifndef __MQTT_MANAGER__
#define __MQTT_MANAGER__

#include <Arduino.h>
#include "devices/Sonar.h"

/**
 * @brief Manages MQTT communication for the device.
 */
class MqttManager {
  private:
    /**
     * @brief Reconnects to the MQTT broker.
     */
    void reconnect();

    /**
     * @brief Sets up the Wi-Fi connection.
     */
    void setup_wifi();

    /**
     * @brief Callback function invoked when a message is received.
     *
     * @param topic The topic of the message.
     * @param payload The payload of the message.
     * @param length The length of the payload.
     */
    static void callback(char *topic, byte *payload, unsigned int length);

  public:

    /**
     * @brief Initializes the MQTT manager.
     */
    void init();

    /**
     * @brief Sends a message containing sonar data.
     * 
     * @param sonar A pointer to the Sonar object.
     */
    void send_message(Sonar *sonar);
};

#endif