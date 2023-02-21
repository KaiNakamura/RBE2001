#pragma once

#include "command/Command.h"

class WaitCommand: public Command {
  public:
    WaitCommand(unsigned long millis);
    WaitCommand(int millis);
    void execute();
    bool isFinished();
    void end();
  private:
    unsigned long start = 0;
    unsigned long duration;
};
