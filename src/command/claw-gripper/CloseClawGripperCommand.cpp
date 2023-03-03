#include "subsystems/robot/Robot.h"
#include "CloseClawGripperCommand.h"

CloseClawGripperCommand::CloseClawGripperCommand() {
  clawGripper = Robot::getInstance()->getClawGripper();
}

void CloseClawGripperCommand::execute() {
}

bool CloseClawGripperCommand::isFinished() {
  return true;
}

void CloseClawGripperCommand::end() {
  clawGripper->close();
}