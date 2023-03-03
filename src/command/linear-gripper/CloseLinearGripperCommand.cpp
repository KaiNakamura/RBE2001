#include "subsystems/robot/Robot.h"
#include "CloseLinearGripperCommand.h"

CloseLinearGripperCommand::CloseLinearGripperCommand() {
  linearGripper = Robot::getInstance()->getLinearGripper();
}

void CloseLinearGripperCommand::execute() {
}

bool CloseLinearGripperCommand::isFinished() {
  return true;
}

void CloseLinearGripperCommand::end() {
  linearGripper->close();
}