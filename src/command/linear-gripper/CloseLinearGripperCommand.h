#pragma once

#include "subsystems/linear-gripper/LinearGripper.h"
#include "command/Command.h"

class CloseLinearGripperCommand: public Command {
  public:
    CloseLinearGripperCommand();
    void execute();
    bool isFinished();
    void end();
  private:
    LinearGripper *linearGripper;
};
