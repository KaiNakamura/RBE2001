#pragma once

#include "subsystems/drivebase/Drivebase.h"
#include "command/Command.h"

class SetMotorsCommand: public Command {
  public:
    SetMotorsCommand(double left, double right);
    SetMotorsCommand(double both);
    void execute();
    bool isFinished();
    void end();
  private:
    Drivebase drivebase;
    double left, right;
};
