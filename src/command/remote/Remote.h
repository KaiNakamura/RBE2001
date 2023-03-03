#pragma once

#include "command/scheduler/Scheduler.h"
#include "subsystems/ir-sensor/IRSensor.h"

class Remote {
protected:
  Remote();
  static Remote *instance;

public:
  static Remote *getInstance();
  void setup();
  void update();
  void reset();
  int16_t getCode();
  bool isPaused();

private:
  Scheduler *scheduler;
  IRSensor *irSensor;
  bool paused;
};