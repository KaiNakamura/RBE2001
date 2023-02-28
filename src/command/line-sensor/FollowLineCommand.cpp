#include "subsystems/robot/Robot.h"
#include "FollowLineCommand.h"

FollowLineCommand::FollowLineCommand(double speed) {
  drivebase = Robot::getInstance()->getDrivebase();
  lineSensor = Robot::getInstance()->getLineSensor();
  this->speed = speed;
}

void FollowLineCommand::execute() {
  double output = K_P * lineSensor->getValue();
  drivebase->setMotors(speed - output, speed + output);
}

bool FollowLineCommand::isFinished() {
  return false;
}

void FollowLineCommand::end() {
  drivebase->stop();
}