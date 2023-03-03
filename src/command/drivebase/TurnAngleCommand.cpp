#include "subsystems/robot/Robot.h"
#include "TurnAngleCommand.h"

TurnAngleCommand::TurnAngleCommand(double angle, double speed) {
  drivebase = Robot::getInstance()->getDrivebase();
  this->angle = angle;
  this->speed = speed;
  this->effort = angle > 0 ? fabs(speed) : -fabs(speed);
}

void TurnAngleCommand::execute() {
  drivebase->setMotors(effort, -effort);
}

bool TurnAngleCommand::isFinished() {
  if (!hasStarted) {
    hasStarted = true;
    this->start = drivebase->getLeftRotations();
    double targetDistance = (fabs(angle) / 360) * Drivebase::WHEEL_TRACK / Drivebase::WHEEL_DIAMETER;
    this->target = angle > 0 ? start + targetDistance : start - targetDistance;
  }

  double rotations = drivebase->getLeftRotations();
  return (angle > 0) ? rotations > target : rotations < target;
}

void TurnAngleCommand::end() {
  drivebase->stop();
}