#include <Arduino.h>
#include "Sonar.h"
#include "MqttManager.h"

MqttManager *mqtt;
Sonar *sonar;
TaskHandle_t Task;

void taskCode(void *pvParameters) {
  mqtt->send_message(sonar);
}

void setup() {
  Serial.begin(115200);
  mqtt = new MqttManager();
  mqtt->init();
  sonar = new Sonar();
  sonar->init();
  xTaskCreatePinnedToCore(taskCode,"Task",10000,sonar,1,&Task,0);
}

void loop() {
}