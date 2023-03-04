#include "subsystems/robot/Robot.h"
#include "WaitForDistanceCommand.h"

WaitForDistanceCommand::WaitForDistanceCommand(double distance) {
  ultrasonic = Robot::getInstance()->getUltrasonic();
  this->distance = distance;
  numReadings = 0;
}

void WaitForDistanceCommand::execute() {
  double reading = ultrasonic->getDistance();
  if (reading > 0 && reading < distance) {
    numReadings++;
  }
}

bool WaitForDistanceCommand::isFinished() {
  return numReadings > MIN_NUM_READINGS;
}

void WaitForDistanceCommand::end() {
}