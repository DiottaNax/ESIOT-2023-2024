#include <Arduino.h>
#include "model/Bridge.h"
#include "kernel/Scheduler.h"
#include "tasks/ControllerTask.h"
#include "tasks/BlinkingTask.h"
#include "tasks/DistanceControlTask.h"
#include "tasks/TemperatureTask.h"
#include "devices/PresenceDetectorImpl.h"
#include "devices/Gate.h"
#include "devices/UltrasonicSensor.h"
#include "tasks/UserConsoleTask.h"
#include "config.h"

#include <avr/sleep.h>

Bridge *bridge;
Scheduler *scheduler;

ControllerTask *controller;
BlinkingTask *blink;
TemperatureTask *tempController;
DistanceControlTask *distanceController;
UserConsoleTask *userConsole;

void changeState() {
  Serial.println("Movement detected");
}

void setup() {
  Serial.begin(9600);

  Gate *gate = new Gate(GATE_PIN);
  UltrasonicSensor *distanceSensor = new UltrasonicSensor(DISTANCE_ECHO_PIN, DISTANCE_TRIGGERED_PIN);

  bridge = new Bridge();
  
  blink = new BlinkingTask();
  tempController = new TemperatureTask(50, bridge);
  tempController->init(LM35_PIN);
  distanceController = new DistanceControlTask(distanceSensor, gate, bridge);
  distanceController->init();
  userConsole = new UserConsoleTask(bridge, blink);
  userConsole->init();

  controller = new ControllerTask(bridge, userConsole, tempController, distanceController);
  controller->init();
  controller->setActive(true);

  scheduler = new Scheduler();
  scheduler->init(10);
  scheduler->addTask(controller);
  scheduler->addTask(blink);
  scheduler->addTask(tempController);
  scheduler->addTask(distanceController);
  scheduler->addTask(userConsole);

  attachInterrupt(digitalPinToInterrupt(PIR_PIN), changeState, CHANGE);
}

void loop() {
  Serial.println(bridge->getState());
  scheduler->schedule();
}
