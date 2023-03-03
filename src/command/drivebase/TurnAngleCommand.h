#pragma once

#include "subsystems/drivebase/Drivebase.h"
#include "command/Command.h"

class TurnAngleCommand: public Command {
  public:
    TurnAngleCommand(double angle, double speed);
    void execute();
    bool isFinished();
    void end();
  private:
    Drivebase *drivebase;
    double angle, speed, start, target, effort;
    bool hasStarted = false;
};
