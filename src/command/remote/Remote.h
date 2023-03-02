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

private:
  Scheduler *scheduler;
  IRSensor *irSensor;
};