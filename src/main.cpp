#include <Romi32U4.h>
#include "subsystems/robot/Robot.h"
#include "command/scheduler/Scheduler.h"
#include "command/remote/Remote.h"
#include "Constants.h"

Scheduler *scheduler;
Robot *robot;
Remote *remote;

Romi32U4ButtonB buttonB;
Romi32U4ButtonC buttonC;

void setup() {
  Serial.begin(9600);

  scheduler = Scheduler::getInstance();
  robot = Robot::getInstance();
  remote = Remote::getInstance();

  scheduler->setup();
  robot->setup();
  remote->setup();
}

void loop() {
  scheduler->update();
  robot->update();
  remote->update();

  // Emergency stop
  if (buttonC.getSingleDebouncedPress()) {
    while (!buttonC.getSingleDebouncedRelease());
    robot->stop();
    while (!buttonC.getSingleDebouncedPress());
  }
}
