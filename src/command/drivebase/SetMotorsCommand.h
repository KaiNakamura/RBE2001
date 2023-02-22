#pragma once

#include "command/Command.h"

class SetMotorsCommand: public Command {
  public:
    SetMotorsCommand(unsigned long millis);
    SetMotorsCommand(int millis);
    void execute();
    bool isFinished();
    void end();
  private:
    unsigned long start = 0;
    unsigned long duration;
};
