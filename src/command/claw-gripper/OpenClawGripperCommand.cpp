#include "subsystems/robot/Robot.h"
#include "OpenClawGripperCommand.h"

OpenClawGripperCommand::OpenClawGripperCommand() {
  clawGripper = Robot::getInstance()->getClawGripper();
}

void OpenClawGripperCommand::execute() {
}

bool OpenClawGripperCommand::isFinished() {
  return true;
}

void OpenClawGripperCommand::end() {
  clawGripper->open();
}