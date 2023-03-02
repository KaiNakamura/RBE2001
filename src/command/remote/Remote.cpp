#include <ir_codes.h>
#include "subsystems/robot/Robot.h"
#include "subsystems/blue-motor/BlueMotor.h"
#include "command/wait-command/WaitCommand.h"
#include "command/line-sensor/FollowLineCommand.h"
#include "command/line-sensor/WaitForLineCommand.h"
#include "command/drivebase/SetMotorsCommand.h"
#include "command/drivebase/TurnAngleCommand.h"
#include "command/blue-motor/BlueMotorMoveToCommand.h"
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
      scheduler->schedule(new TurnAngleCommand(90, 0.1));
      break;
    case NUM_2:
      scheduler->schedule(new TurnAngleCommand(-90, 0.1));
      break;
    case NUM_3:
      break;
    case NUM_4:
      break;
    case NUM_5:
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
