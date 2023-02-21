#pragma once

#include "command/Command.h"

class ParallelCommandGroup: public Command {
  public:
    ParallelCommandGroup();
    void execute();
    bool isFinished();
    void end();
  private:
};
