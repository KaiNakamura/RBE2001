#pragma once

#include "subsystems/line-sensor/LineSensor.h"
#include "command/Command.h"

class WaitForLineCommand: public Command {
  public:
    WaitForLineCommand();
    void execute();
    bool isFinished();
    void end();
  private:
    static constexpr double IS_ON_LINE_THRESHOLD = 0.85;
    LineSensor *lineSensor;
};
