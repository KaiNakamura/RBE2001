#pragma once

#include "subsystems/claw-gripper/ClawGripper.h"
#include "command/Command.h"

class OpenClawGripperCommand: public Command {
  public:
    OpenClawGripperCommand();
    void execute();
    bool isFinished();
    void end();
  private:
    ClawGripper *clawGripper;
};
