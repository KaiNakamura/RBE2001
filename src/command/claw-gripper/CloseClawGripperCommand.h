#pragma once

#include "subsystems/claw-gripper/ClawGripper.h"
#include "command/Command.h"

class CloseClawGripperCommand: public Command {
  public:
    CloseClawGripperCommand();
    void execute();
    bool isFinished();
    void end();
  private:
    ClawGripper *clawGripper;
};
