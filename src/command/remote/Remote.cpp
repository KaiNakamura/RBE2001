#include <ir_codes.h>
#include "subsystems/robot/Robot.h"
#include "subsystems/blue-motor/BlueMotor.h"
#include "command/wait-command/WaitCommand.h"
#include "command/line-sensor/FollowLineCommand.h"
#include "command/line-sensor/WaitForLineCommand.h"
#include "command/ultrasonic/WaitForDistanceCommand.h"
#include "command/drivebase/SetMotorsCommand.h"
#include "command/drivebase/DriveStraightCommand.h"
#include "command/drivebase/TurnAngleCommand.h"
#include "command/blue-motor/BlueMotorMoveToCommand.h"
#include "command/blue-motor/BlueMotorSetEffortCommand.h"
#include "command/claw-gripper/CloseClawGripperCommand.h"
#include "command/claw-gripper/OpenClawGripperCommand.h"
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
    case UP_ARROW:
      Serial.println("UP_ARROW");
      scheduler->schedule(new ParallelRaceCommandGroup(
        new BlueMotorSetEffortCommand(0.5),
        new WaitCommand(500)
      ));
      break;
    case DOWN_ARROW:
      Serial.println("DOWN_ARROW");
      scheduler->schedule(new ParallelRaceCommandGroup(
        new BlueMotorSetEffortCommand(-0.5),
        new WaitCommand(500)
      ));
      break;
    case LEFT_ARROW:
      Serial.println("LEFT_ARROW");
      scheduler->schedule(new OpenClawGripperCommand());
      break;
    case RIGHT_ARROW:
      Serial.println("RIGHT_ARROW");
      scheduler->schedule(new CloseClawGripperCommand());
      break;
    case NUM_0_10:
      break;
    case NUM_1:
      Serial.println("NUM_1");
      // Move to and grab old solar panel from the 45 degree roof
      scheduler->schedule(new SequentialCommandGroup(
        new OpenClawGripperCommand(),
        new BlueMotorMoveToCommand(BlueMotor::ROOF_45_DEGREE_SETPOINT),
        new ParallelRaceCommandGroup(
          new FollowLineCommand(0.1),
          new WaitForDistanceCommand(12.6)
        ),
        new WaitCommand(500),
        new CloseClawGripperCommand()
      ));
      break;
    case NUM_2:
      Serial.println("NUM_2");
      // Take old solar panel to staging platform
      scheduler->schedule(new SequentialCommandGroup(
        new DriveStraightCommand(20, -0.2),
        new TurnAngleCommand(180, 0.2),
        new ParallelRaceCommandGroup(
          new FollowLineCommand(0.2),
          new WaitForLineCommand()
        ),
        new TurnAngleCommand(-90, 0.2),
        new ParallelRaceCommandGroup(
          new FollowLineCommand(0.2),
          new WaitForDistanceCommand(5)
        ),
        new BlueMotorMoveToCommand(BlueMotor::STARTING_SETPOINT)
      ));
      break;
    case NUM_3:
      Serial.println("NUM_3");
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
