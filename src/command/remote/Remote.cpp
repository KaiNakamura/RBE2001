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
  reset();
}

void Remote::update() {
  int16_t code = getCode();

  if (code != -1) {
    Serial.print("Code: ");
    Serial.println(code);
  }

  switch (code) {
    case PLAY_PAUSE:
      paused = !paused;
      break;
    case STOP_MODE:
      scheduler->reset();
      break;
    case SETUP_BTN:
      Serial.println("SETUP_BTN");
      Robot::getInstance()->getBlueMotor()->reset();
      break;
    case UP_ARROW:
      Serial.println("UP_ARROW");
      scheduler->schedule(new ParallelRaceCommandGroup(
        new BlueMotorSetEffortCommand(1),
        new WaitCommand(250)
      ));
      break;
    case DOWN_ARROW:
      Serial.println("DOWN_ARROW");
      scheduler->schedule(new ParallelRaceCommandGroup(
        new BlueMotorSetEffortCommand(-1),
        new WaitCommand(250)
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
      // Move to and grab old solar panel from the 25 degree roof
      scheduler->schedule(new SequentialCommandGroup(
        new SequentialCommandGroup(
          new ParallelRaceCommandGroup(
            new FollowLineCommand(0.1),
            new WaitForLineCommand()
          ),
          new DriveStraightCommand(6, 0.1),
          new TurnAngleCommand(90, 0.1)
        ),
        new OpenClawGripperCommand(),
        new BlueMotorMoveToCommand(BlueMotor::PICKUP_ROOF_25_DEGREE_SETPOINT),
        new ParallelRaceCommandGroup(
          new FollowLineCommand(0.1),
          new WaitForDistanceCommand(14)
        ),
        new ParallelRaceCommandGroup(
          new SetMotorsCommand(0.1),
          new WaitCommand(500)
        ),
        new WaitCommand(500),
        new CloseClawGripperCommand()
      ));
      break;
    case NUM_2:
      Serial.println("NUM_2");
      // Take old solar panel to staging platform
      scheduler->schedule(new SequentialCommandGroup(
        new CloseClawGripperCommand(),
        new BlueMotorMoveToCommand(BlueMotor::MAX_HEIGHT),
        new DriveStraightCommand(2, -0.1),
        new TurnAngleCommand(180, 0.1),
        new ParallelRaceCommandGroup(
          new FollowLineCommand(0.1),
          new WaitForLineCommand()
        ),
        new DriveStraightCommand(6, 0.1),
        new SequentialCommandGroup(
          new TurnAngleCommand(-75, 0.1),
          new ParallelRaceCommandGroup(
            new FollowLineCommand(0.1),
            new WaitForDistanceCommand(7)
          ),
          new BlueMotorMoveToCommand(BlueMotor::STAGING_PLATFORM)
        )
      ));
      break;
    case NUM_3:
      Serial.println("NUM_3");
      // Release old solar panel
      scheduler->schedule(new SequentialCommandGroup(
          new OpenClawGripperCommand(),
          new DriveStraightCommand(10, -0.1)
      ));
      break;
    case NUM_4:
      Serial.println("NUM_4");
      // Pick up new solar panel
      scheduler->schedule(new SequentialCommandGroup(
          new OpenClawGripperCommand(),
          new BlueMotorMoveToCommand(BlueMotor::STAGING_PLATFORM),
          new ParallelRaceCommandGroup(
            new FollowLineCommand(0.1),
            new WaitForDistanceCommand(6)
          ),
          new ParallelRaceCommandGroup(
            new SetMotorsCommand(0.1),
            new WaitCommand(500)
          ),
          new CloseClawGripperCommand()
      ));
      break;
    case NUM_5:
      Serial.println("NUM_5");
      // Take new solar panel to 25 degree roof
      scheduler->schedule(new SequentialCommandGroup(
        new CloseClawGripperCommand(),
        new DriveStraightCommand(2, -0.1),
        new BlueMotorMoveToCommand(BlueMotor::MAX_HEIGHT),
        new TurnAngleCommand(180, 0.1),
        new ParallelRaceCommandGroup(
          new FollowLineCommand(0.1),
          new WaitForLineCommand()
        ),
        new DriveStraightCommand(6, 0.1),
        new SequentialCommandGroup(
          new TurnAngleCommand(90, 0.1),
          new ParallelRaceCommandGroup(
            new FollowLineCommand(0.1),
            new WaitForDistanceCommand(18)
          ),
          new ParallelRaceCommandGroup(
            new FollowLineCommand(0.1),
            new SequentialCommandGroup(
              new BlueMotorMoveToCommand(BlueMotor::ABOVE_ROOF_25_DEGREE_SETPOINT),
              new WaitForDistanceCommand(7.5)
            )
          ),
          new WaitCommand(500),
          new BlueMotorMoveToCommand(BlueMotor::PLACE_ROOF_25_DEGREE_SETPOINT)
        )
      ));
      break;
    case NUM_6:
      Serial.println("NUM_6");
      // Release new solar panel
      scheduler->schedule(new SequentialCommandGroup(
          new BlueMotorMoveToCommand(BlueMotor::PLACE_ROOF_25_DEGREE_SETPOINT),
          new OpenClawGripperCommand(),
          new DriveStraightCommand(3, -0.1),
          new TurnAngleCommand(160, 0.08)
      ));
      break;
    case NUM_7:
      Serial.println("NUM_7");
      // Cross to other side of the field
      scheduler->schedule(new SequentialCommandGroup(
        new SequentialCommandGroup(
          new BlueMotorMoveToCommand(BlueMotor::STAGING_PLATFORM),
          new ParallelRaceCommandGroup(
            new FollowLineCommand(0.1),
            new WaitForLineCommand()
          ),
          new DriveStraightCommand(6, 0.1),
          new TurnAngleCommand(-75, 0.1),
          new ParallelRaceCommandGroup(
            new FollowLineCommand(0.1),
            new WaitForDistanceCommand(6)
          ),
          new TurnAngleCommand(-85, 0.08)
        ),
        new ParallelRaceCommandGroup(
          new SetMotorsCommand(0.1, 0.102),
          new WaitForLineCommand()
        ),
        new DriveStraightCommand(6, 0.1),
        new TurnAngleCommand(-90, 0.1)
      ));
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
  paused = false;
}

int16_t Remote::getCode() {
  return irSensor->getCode();
}

bool Remote::isPaused() {
  return paused;
}