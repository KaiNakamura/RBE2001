#include <Romi32U4.h>
#include "subsystems/robot/Robot.h"
#include "command/scheduler/Scheduler.h"
#include "command/wait-command/WaitCommand.h"
#include "command/parallel-command-group/ParallelCommandGroup.h"
#include "command/sequential-command-group/SequentialCommandGroup.h"
#include "Constants.h"
#include <Servo32u4.h>

Scheduler *scheduler;
Robot *robot;

Romi32U4ButtonA buttonA;
Romi32U4ButtonB buttonB;
Romi32U4ButtonC buttonC;

void setup() {
  Serial.begin(9600);

  scheduler = Scheduler::getInstance();
  robot = Robot::getInstance();

  scheduler->setup();
  robot->setup();
}

void loop() {
  scheduler->update();
  robot->update();

  // Emergency stop
  if (buttonA.getSingleDebouncedPress()) {
    while (!buttonA.getSingleDebouncedRelease());

    while (!buttonA.getSingleDebouncedPress()) ;
  }
}
