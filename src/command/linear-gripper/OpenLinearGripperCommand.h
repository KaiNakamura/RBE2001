#pragma once

#include "subsystems/linear-gripper/LinearGripper.h"
#include "command/Command.h"

class OpenLinearGripperCommand: public Command {
  public:
    OpenLinearGripperCommand();
    void execute();
    bool isFinished();
    void end();
  private:
    LinearGripper *linearGripper;
};
