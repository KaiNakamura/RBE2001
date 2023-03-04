#include "subsystems/robot/Robot.h"
#include "OpenLinearGripperCommand.h"

OpenLinearGripperCommand::OpenLinearGripperCommand() {
  linearGripper = Robot::getInstance()->getLinearGripper();
}

void OpenLinearGripperCommand::execute() {
  if (!hasStarted) {
    hasStarted = true;
    linearGripper->open();
  }
}

bool OpenLinearGripperCommand::isFinished() {
  return linearGripper->isInOpenState();
}

void OpenLinearGripperCommand::end() {
}