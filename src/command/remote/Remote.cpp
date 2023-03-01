#include <ir_codes.h>
#include "subsystems/robot/Robot.h"
#include "command/wait-command/WaitCommand.h"
#include "command/line-sensor/FollowLineCommand.h"
#include "command/line-sensor/WaitForLineCommand.h"
#include "command/drivebase/SetMotorsCommand.h"
#include "command/sequential-command-group/SequentialCommandGroup.h"
#include "command/parallel-command-group/ParallelCommandGroup.h"
#include "command/parallel-race-command-group/ParallelRaceCommandGroup.h"
#include "Remote.h"

Remote *Remote::instance = 0;

Remote::Remote() {
  scheduler = Scheduler::getInstance();
  irSensor = Robot::getInstance()->getIRSensor();
}

Remote *Remote::getInstance() {
  if (!instance) {
    instance = new Remote();
  }
  return instance;
}

void Remote::setup() {
}

void Remote::update() {
  int16_t code = irSensor->getCode();

  if (code != -1) {
    Serial.print("Code: ");
    Serial.println(code);
  }

  switch (code) {
    case PLAY_PAUSE:
      break;
    case STOP_MODE:
      scheduler->reset();
      break;
    case NUM_0_10:
      break;
    case NUM_1:
      Serial.println("NUM_1");
      scheduler->schedule(new WaitCommand(1000));
      break;
    case NUM_2:
      Serial.println("NUM_2");
      scheduler->schedule(new SequentialCommandGroup(
        new WaitCommand(1000),
        new WaitCommand(2000)
      ));
      break;
    case NUM_3:
      Serial.println("NUM_3");
      scheduler->schedule(new ParallelCommandGroup(
        new WaitCommand(1000),
        new WaitCommand(2000)
      ));
      break;
    case NUM_4:
      Serial.println("NUM_4");
      scheduler->schedule(new WaitCommand(1000));
      scheduler->schedule(new WaitCommand(1000));
      break;
    case NUM_5:
      Serial.println("NUM_5");
      scheduler->schedule(new SequentialCommandGroup(
        new WaitCommand(1000),
        new WaitCommand(2000)
      ));
      scheduler->schedule(new SequentialCommandGroup(
        new WaitCommand(1000),
        new WaitCommand(2000)
      ));
      break;
    case NUM_6:
      break;
    case NUM_7:
      break;
    case NUM_8:
      break;
    case NUM_9:
      break;
    default:
      break;
  }
}

void Remote::reset() {
}
