#include <Arduino.h>
#include "model/Bridge.h"
#include "kernel/Scheduler.h"
#include "tasks/ControllerTask.h"
#include "tasks/BlinkingTask.h"
#include "tasks/DistanceControlTask.h"
#include "tasks/TemperatureTask.h"
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

void setup() {
  Serial.begin(9600);

  bridge = new Bridge();
  
  blink = new BlinkingTask(100);
  tempController = new TemperatureTask(100, bridge);
  distanceController = new DistanceControlTask(bridge);
  userConsole = new UserConsoleTask(bridge, blink);

  controller = new ControllerTask(bridge, userConsole, tempController, distanceController);
  controller->init();

  scheduler = new Scheduler();
  scheduler->init(50);
  scheduler->addTask(controller);
  scheduler->addTask(blink);
  scheduler->addTask(tempController);
  scheduler->addTask(distanceController);
  scheduler->addTask(userConsole);

  pinMode(PIR_PIN,INPUT);
}

void loop() {
  scheduler->schedule(); 
}
