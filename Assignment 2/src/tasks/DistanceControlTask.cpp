#include <Arduino.h>
#include "tasks/DistanceControlTask.h"
#include "tasks/DistanceControlTask.h"
#include "config.h"

#define OPEN 180
#define CLOSED 0

DistanceControlTask::DistanceControlTask(ProximitySensor *proxSensor, ServoMotor *gate, ControllerTask *controllerTask){
    _proxSensor = proxSensor;
    _gate = gate;
    _controllerTask = controllerTask;
    _gateOpened = false;
}

void DistanceControlTask::tick(){
    switch (state){
    case ENTERING:
        if(!_gateOpened){
            _gate->setAngle(OPEN);
            _gateOpened = true;
        }

        _distance = _proxSensor->getDistance();
        int currentTime = millis() - _firstTimeRegisteredMinDist;
        if(!_alreadyPassedDist && _distance < MINDIST){
            _alreadyPassedDist = true;
            _firstTimeRegisteredMinDist = millis();
        } else{
            if(_distance > MINDIST){
                _alreadyPassedDist = false;
            } else if(currentTime >= N2) {
                setActive(false);
                setState(LEAVING);
                _controllerTask->setState(READY_TO_WASH);
            }
        }
        break;
    
    case LEAVING:
        if (!_gateOpened) {
            _gate->setAngle(OPEN);
            _gateOpened = true;
        }

        _distance = _proxSensor->getDistance();
        int currentTime = millis() - _firstTimeRegisteredMinDist;
        if (!_alreadyPassedDist && _distance < MINDIST) {
            _alreadyPassedDist = true;
            _firstTimeRegisteredMinDist = millis();
        }
        else {
            if (_distance < MAXDIST) {
                _alreadyPassedDist = false;
            } else if (currentTime >= N4) {
                setActive(false);
                setState(LEAVING);
                _controllerTask->setState(READY_TO_WASH);
            }
        }
        break;
    }
}