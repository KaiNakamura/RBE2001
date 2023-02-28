#pragma once

#include "subsystems/drivebase/Drivebase.h"
#include "subsystems/line-sensor/LineSensor.h"
#include "command/Command.h"

class FollowLineUntilLineCommand: public Command {
  public:
    FollowLineUntilLineCommand();
    void execute();
    bool isFinished();
    void end();
  private:
};
