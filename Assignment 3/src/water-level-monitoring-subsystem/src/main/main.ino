#include <Arduino.h>
#include "SonarTask.h"
#include "MqttManager.h"

MqttManager *mqtt;
SonarTask *sonar;
TaskHandle_t Task;

void taskCode(void *pvParameters) {
  mqtt->send_message(reinterpret_cast<SonarTask*>(pvParameters));
}

void setup() {
  Serial.begin(115200);
  mqtt = new MqttManager();
  mqtt->init();
  sonar = new SonarTask();
  sonar->init();
  xTaskCreatePinnedToCore(taskCode,"Task",10000,sonar,1,&Task,0);
}

void loop() {
}