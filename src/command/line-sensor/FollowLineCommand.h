#pragma once

#include "subsystems/drivebase/Drivebase.h"
#include "subsystems/line-sensor/LineSensor.h"
#include "command/Command.h"

class FollowLineCommand: public Command {
  public:
    FollowLineCommand(double speed);
    void execute();
    bool isFinished();
    void end();
  private:
    static constexpr double K_P = 0.15;
    Drivebase *drivebase;
    LineSensor *lineSensor;
    double speed;
};
