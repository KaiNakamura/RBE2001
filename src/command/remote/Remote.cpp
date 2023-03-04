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
#include "command/linear-gripper/CloseLinearGripperCommand.h"
#include "command/linear-gripper/OpenLinearGripperCommand.h"
#include "command/sequential-command-group/SequentialCommandGroup.h"
#include "command/parallel-command-group/ParallelCommandGroup.h"
#include "command/parallel-race-command-group/ParallelRaceCommandGroup.h"
#include "command/parallel-race-command-group/ParallelRaceCommandGroup2.h"
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
      Serial.println("PLAY_PAUSE");
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
      scheduler->schedule(new ParallelRaceCommandGroup2(
        new BlueMotorSetEffortCommand(1),
        new WaitCommand(250)
      ));
      break;
    case DOWN_ARROW:
      Serial.println("DOWN_ARROW");
      scheduler->schedule(new ParallelRaceCommandGroup2(
        new BlueMotorSetEffortCommand(-1),
        new WaitCommand(250)
      ));
      break;
    case LEFT_ARROW:
      Serial.println("LEFT_ARROW");
      scheduler->schedule(new OpenLinearGripperCommand());
      break;
    case RIGHT_ARROW:
      Serial.println("RIGHT_ARROW");
      scheduler->schedule(new CloseLinearGripperCommand());
      break;
    case NUM_0_10:
      break;
    case NUM_1:
      Serial.println("NUM_1");
      // Move to and grab old solar panel from the 45 degree roof
      scheduler->schedule(new SequentialCommandGroup(
        new SequentialCommandGroup(
          new ParallelRaceCommandGroup2(
            new FollowLineCommand(0.125),
            new WaitForLineCommand()
          ),
          new DriveStraightCommand(6, 0.125),
          new TurnAngleCommand(-75, 0.125)
        ),
        new OpenLinearGripperCommand(),
        new BlueMotorMoveToCommand(BlueMotor::ROOF_45_DEGREE_SETPOINT),
        new ParallelRaceCommandGroup2(
          new FollowLineCommand(0.125),
          new WaitForDistanceCommand(14)
        ),
        new ParallelRaceCommandGroup2(
          new SetMotorsCommand(0.15),
          new WaitCommand(500)
        ),
        new CloseLinearGripperCommand()
      ));
      break;
    case NUM_2:
      Serial.println("NUM_2");
      // Take old solar panel to staging platform
      scheduler->schedule(new SequentialCommandGroup(
        new CloseLinearGripperCommand(),
        new BlueMotorMoveToCommand(BlueMotor::MAX_HEIGHT),
        new DriveStraightCommand(2, -0.125),
        new TurnAngleCommand(180, 0.125),
        new ParallelRaceCommandGroup2(
          new FollowLineCommand(0.125),
          new WaitForLineCommand()
        ),
        new DriveStraightCommand(7, 0.125),
        new SequentialCommandGroup(
          new TurnAngleCommand(90, 0.125),
          new ParallelRaceCommandGroup2(
            new FollowLineCommand(0.125),
            new WaitForDistanceCommand(7)
          ),
          new DriveStraightCommand(3, -0.125),
          new BlueMotorMoveToCommand(BlueMotor::STAGING_PLATFORM)
        )
      ));
      break;
    case NUM_3:
      Serial.println("NUM_3");
      // Release old solar panel
      scheduler->schedule(new SequentialCommandGroup(
          new OpenLinearGripperCommand(),
          new DriveStraightCommand(10, -0.15)
      ));
      break;
    case NUM_4:
      Serial.println("NUM_4");
      // Pick up new solar panel
      scheduler->schedule(new SequentialCommandGroup(
          new OpenLinearGripperCommand(),
          new BlueMotorMoveToCommand(BlueMotor::STAGING_PLATFORM),
          new ParallelRaceCommandGroup2(
            new SetMotorsCommand(0.15),
            new WaitCommand(3000)
          ),
          new CloseLinearGripperCommand()
      ));
      break;
    case NUM_5:
      Serial.println("NUM_5");
      // Take new solar panel to 45 degree roof
      scheduler->schedule(new SequentialCommandGroup(
        new BlueMotorMoveToCommand(BlueMotor::MAX_HEIGHT),
        new TurnAngleCommand(180, 0.125),
        new ParallelRaceCommandGroup2(
          new FollowLineCommand(0.125),
          new WaitForLineCommand()
        ),
        new DriveStraightCommand(6, 0.125),
        new TurnAngleCommand(-75, 0.125),
        new ParallelRaceCommandGroup2(
          new FollowLineCommand(0.125),
          new WaitForDistanceCommand(14)
        ),
        new BlueMotorMoveToCommand(BlueMotor::ROOF_45_DEGREE_SETPOINT)
          // new ParallelRaceCommandGroup2(
          //   new SetMotorsCommand(0.15),
          //   new WaitCommand(500)
          // )
      ));
      break;
    case NUM_6:
      Serial.println("NUM_6");
      // Release new solar panel
      scheduler->schedule(new SequentialCommandGroup(
          new OpenLinearGripperCommand(),
          new DriveStraightCommand(6, -0.15)
      ));
      break;
    case NUM_7:
      Serial.println("NUM_7");
      scheduler->schedule(new ParallelRaceCommandGroup2(
        new FollowLineCommand(0.15),
        new WaitForLineCommand()
      ));
      break;
    case NUM_8:
      Serial.println("NUM_8");
      scheduler->schedule(
        new ParallelRaceCommandGroup(
          new FollowLineCommand(0.15),
          new WaitForDistanceCommand(3)
        )
      );
      break;
    case NUM_9:
      Serial.println("NUM_9");
      scheduler->schedule(
        new ParallelRaceCommandGroup2(
          new FollowLineCommand(0.15),
          new WaitForDistanceCommand(3)
        )
      );
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