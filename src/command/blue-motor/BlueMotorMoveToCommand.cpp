#include "subsystems/robot/Robot.h"
#include "BlueMotorMoveToCommand.h"

BlueMotorMoveToCommand::BlueMotorMoveToCommand(double setpoint, Units units) {
  blueMotor = Robot::getInstance()->getBlueMotor();
  this->setpoint = setpoint;
  this->units = units;
}

BlueMotorMoveToCommand::BlueMotorMoveToCommand(double rotations) {
  blueMotor = Robot::getInstance()->getBlueMotor();
  this->setpoint = rotations;
  this->units = ROTATIONS;
}

void BlueMotorMoveToCommand::execute() {
  // Serial.println("BlueMotorMoveToCommand");
  double error = setpoint - blueMotor->getPosition(units);
  blueMotor->setEffort(K_P * error);
}

bool BlueMotorMoveToCommand::isFinished() {
  return blueMotor->isAtPosition(setpoint, units);
}

void BlueMotorMoveToCommand::end() {
  blueMotor->setEffort(0);
}