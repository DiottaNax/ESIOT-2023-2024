#include <Arduino.h>
#include "model/Bridge.h"
#include "kernel/Scheduler.h"
#include "tasks/ControllerTask.h"
#include "tasks/BlinkingTask.h"
#include "tasks/DistanceControlTask.h"
#include "tasks/TemperatureTask.h"
#include "devices/PresenceDetectorImpl.h"
#include "config.h"

//#include <EnableInterrupt.h>
#include <avr/sleep.h>

Bridge *bridge;
Scheduler *scheduler;
ControllerTask *controller;
BlinkingTask *blink;
TemperatureTask *tempController;
PresenceDetectorImpl *presenceSensor;

void changeState() {
  Serial.println("Movement detected");
}

void setup() {
  Serial.begin(9600);
  bridge = new Bridge();
  scheduler = new Scheduler();
  blink = new BlinkingTask();
  tempController = new TemperatureTask(50, bridge);
  presenceSensor = new PresenceDetectorImpl(PIR_PIN);

  controller = new ControllerTask(bridge, blink, tempController, presenceSensor);
  controller->init();
  controller->setActive(true);
  scheduler->init(10);
  scheduler->addTask(controller);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), changeState, CHANGE);
}

void loop() {
  Serial.println(bridge->getState());
  scheduler->schedule();
}
