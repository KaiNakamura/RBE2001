#include "subsystems/robot/Robot.h"
#include "BlueMotorMoveToCommand.h"

BlueMotorMoveToCommand::BlueMotorMoveToCommand(double setpoint, Units units) {
  blueMotor = Robot::getInstance()->getBlueMotor();
  this->setpoint = setpoint;
  this->units = units;
}

void BlueMotorMoveToCommand::execute() {
  blueMotor->moveTo(setpoint, units);
}

bool BlueMotorMoveToCommand::isFinished() {
  return blueMotor->isAtTarget();
}

void BlueMotorMoveToCommand::end() {
}