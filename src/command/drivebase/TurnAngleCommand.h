#pragma once

#include "subsystems/drivebase/Drivebase.h"
#include "command/Command.h"

class TurnAngleCommand: public Command {
  public:
    TurnAngleCommand(double left, double right);
    TurnAngleCommand(double both);
    void execute();
    bool isFinished();
    void end();
  private:
    Drivebase *drivebase;
    double angle, speed, start, target, effort;
};
