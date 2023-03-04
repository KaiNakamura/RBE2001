#pragma once

#include "command/Command.h"
#include "Constants.h"
#include <Array.h>

class ParallelRaceCommandGroup2: public Command {
  public:
    ParallelRaceCommandGroup2(Command *command1, Command *command2);
    void execute();
    bool isFinished();
    void end();
  private:
    Array<Command *, 2> commands;
};
