#include "subsystems/robot/Robot.h"
#include "SetMotorsCommand.h"

SetMotorsCommand::SetMotorsCommand(double left, double right) {
  drivebase = Robot::getInstance()->getDrivebase();
  this->left = left;
  this->right = right;
}

SetMotorsCommand::SetMotorsCommand(double both) {
  SetMotorsCommand(both, both);
}

void SetMotorsCommand::execute() {
  drivebase->setMotors(left, right);
}

bool SetMotorsCommand::isFinished() {
  return false;
}

void SetMotorsCommand::end() {
  drivebase->stop();
}