#include "subsystems/robot/Robot.h"
#include "CloseLinearGripperCommand.h"

CloseLinearGripperCommand::CloseLinearGripperCommand() {
  linearGripper = Robot::getInstance()->getLinearGripper();
}

void CloseLinearGripperCommand::execute() {
  // Serial.println("CloseLinearGripperCommand");
  if (!hasStarted) {
    hasStarted = true;
    linearGripper->close();
  }
}

bool CloseLinearGripperCommand::isFinished() {
  return linearGripper->isInClosedState();
}

void CloseLinearGripperCommand::end() {
}