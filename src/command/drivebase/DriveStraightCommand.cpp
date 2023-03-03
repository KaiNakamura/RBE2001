#include "subsystems/robot/Robot.h"
#include "DriveStraightCommand.h"

DriveStraightCommand::DriveStraightCommand(double distance, double speed) {
  drivebase = Robot::getInstance()->getDrivebase();
  this->distance = distance;
  this->speed = speed;
}

void DriveStraightCommand::execute() {

  drivebase->setMotors(speed, speed);
}

bool DriveStraightCommand::isFinished() {
  if (!hasStarted) {
    hasStarted = true;
    this->start = drivebase->getLeftPosition();
    this->target = speed > 0 ? start + distance : start - distance;
    Serial.print("Start: ");
    Serial.println(start);
  }

  double position = drivebase->getLeftPosition();
  // Serial.print("Position: ");
  // Serial.print(position);
  // Serial.print(", start: ");
  // Serial.print(start);
  // Serial.print(", target: ");
  // Serial.println(target);
  return (speed > 0) ? position > target : position < target;
}

void DriveStraightCommand::end() {
  drivebase->stop();
}