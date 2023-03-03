#pragma once

#include "subsystems/blue-motor/BlueMotor.h"
#include "command/Command.h"
#include "Constants.h"

class BlueMotorSetEffortCommand: public Command {
  public:
    BlueMotorSetEffortCommand(double effort);
    void execute();
    bool isFinished();
    void end();
  private:
    BlueMotor *blueMotor;
    double effort;
};
