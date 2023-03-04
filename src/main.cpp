#include <Romi32U4.h>
#include <ir_codes.h>
#include "subsystems/robot/Robot.h"
#include "command/scheduler/Scheduler.h"
#include "command/remote/Remote.h"
#include "command/wait-command/WaitCommand.h"
#include "command/line-sensor/FollowLineCommand.h"
#include "command/line-sensor/WaitForLineCommand.h"
#include "command/drivebase/SetMotorsCommand.h"
#include "command/blue-motor/BlueMotorMoveToCommand.h"
#include "command/sequential-command-group/SequentialCommandGroup.h"
#include "command/parallel-command-group/ParallelCommandGroup.h"
#include "command/parallel-race-command-group/ParallelRaceCommandGroup.h"
#include "Constants.h"

Scheduler *scheduler;
Robot *robot;
Remote *remote;

Romi32U4ButtonB buttonB;
Romi32U4ButtonC buttonC;

void setup() {
  Serial.begin(9600);

  remote = Remote::getInstance();
  scheduler = Scheduler::getInstance();
  robot = Robot::getInstance();

  remote->setup();
  scheduler->setup();
  robot->setup();
}

void loop() {
  remote->update();

  // Serial.println(robot->getUltrasonic()->getDistance());
  // Serial.print(robot->getLineSensor()->getLeftValue());
  // Serial.print(", ");
  // Serial.println(robot->getLineSensor()->getRightValue());
  // Serial.println(robot->getUltrasonic()->getDistance());

  // Pausing
  if (remote->isPaused()) {
    robot->stop();
  } else {
    scheduler->update();
    robot->update();
  }

  // Emergency stop
  if (buttonC.getSingleDebouncedPress()) {
    while (!buttonC.getSingleDebouncedRelease());
    robot->stop();
    while (!buttonC.getSingleDebouncedPress());
  }
}
