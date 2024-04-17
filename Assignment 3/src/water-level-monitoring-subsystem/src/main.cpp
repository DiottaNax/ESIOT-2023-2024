#include <Arduino.h>
#include "devices/Sonar.h"
#include "tasks/MqttManager.h"

MqttManager *mqtt;  // MQTT manager object
Sonar *sonar;       // Sonar sensor object
TaskHandle_t Task;  // Task handle for the background task

/**
 * @brief Function executed by the background task.
 * 
 * @param pvParameters Pointer to the parameters passed to the task.
 */
void taskCode(void *pvParameters) {
  mqtt->send_message(sonar);
}

void setup() {
  Serial.begin(115200);
  mqtt = new MqttManager();
  mqtt->init();
  sonar = new Sonar();
  sonar->init();
  xTaskCreatePinnedToCore(taskCode,"Task",10000,sonar,1,&Task,0); // Create a background task
}

void loop() {
}