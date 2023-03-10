#pragma once

#include "subsystems/blue-motor/BlueMotor.h"
#include "command/Command.h"
#include "Constants.h"

class BlueMotorMoveToCommand: public Command {
  public:
    BlueMotorMoveToCommand(double setpoint, Units units);
    BlueMotorMoveToCommand(double rotations);
    void execute();
    bool isFinished();
    void end();
  private:
    BlueMotor *blueMotor;
    double setpoint;
    Units units;
    static constexpr double K_P = 50;
};
