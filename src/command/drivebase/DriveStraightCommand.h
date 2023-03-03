#pragma once

#include "subsystems/drivebase/Drivebase.h"
#include "command/Command.h"

class DriveStraightCommand: public Command {
  public:
    DriveStraightCommand(double distance, double speed);
    void execute();
    bool isFinished();
    void end();
  private:
    Drivebase *drivebase;
    double distance, speed, start, target;
    bool hasStarted = false;
};
