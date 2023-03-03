#include "subsystems/robot/Robot.h"
#include "OpenLinearGripperCommand.h"

OpenLinearGripperCommand::OpenLinearGripperCommand() {
  linearGripper = Robot::getInstance()->getLinearGripper();
}

void OpenLinearGripperCommand::execute() {
}

bool OpenLinearGripperCommand::isFinished() {
  return true;
}

void OpenLinearGripperCommand::end() {
  linearGripper->open();
}