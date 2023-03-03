#include "subsystems/robot/Robot.h"
#include "BlueMotorSetEffortCommand.h"

BlueMotorSetEffortCommand::BlueMotorSetEffortCommand(double effort) {
  blueMotor = Robot::getInstance()->getBlueMotor();
  this->effort = effort;
}

void BlueMotorSetEffortCommand::execute() {
  blueMotor->setEffort(effort);
}

bool BlueMotorSetEffortCommand::isFinished() {
  return false;
}

void BlueMotorSetEffortCommand::end() {
  blueMotor->setEffort(0);
}