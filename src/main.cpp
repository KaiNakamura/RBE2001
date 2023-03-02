#include <Romi32U4.h>
#include "subsystems/robot/Robot.h"
#include "command/scheduler/Scheduler.h"
#include "command/wait-command/WaitCommand.h"
#include "command/line-sensor/FollowLineCommand.h"
#include "command/line-sensor/WaitForLineCommand.h"
#include "command/drivebase/SetMotorsCommand.h"
#include "command/blue-motor/BlueMotorMoveToCommand.h"
#include "command/sequential-command-group/SequentialCommandGroup.h"
#include "command/parallel-command-group/ParallelCommandGroup.h"
#include "command/parallel-race-command-group/ParallelRaceCommandGroup.h"
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

  scheduler->schedule(new ParallelRaceCommandGroup(
    new SetMotorsCommand(0.25, 0.25),
    new WaitCommand(1000)
  ));

  // scheduler->schedule(new SequentialCommandGroup(
  //   new ParallelRaceCommandGroup(
  //     new FollowLineCommand(0.1),
  //     new WaitForLineCommand()
  //   ),
  //   new ParallelRaceCommandGroup(
  //     new SetMotorsCommand(0.25, -0.25),
  //     new WaitCommand(2000)
  //   )
  //   // new BlueMotorMoveToCommand(BlueMotor::ROOF_45_DEGREE_SETPOINT, Units::ROTATIONS)
  // ));

  while (!buttonC.getSingleDebouncedRelease());
}

void loop() {
  scheduler->update();
  robot->update();

  // Emergency stop
  if (buttonA.getSingleDebouncedPress()) {
    while (!buttonA.getSingleDebouncedRelease());
    robot->stop();
    while (!buttonA.getSingleDebouncedPress());
  }
}
