#pragma once

#include "command/Command.h"
#include "Constants.h"
#include <Array.h>

class ParallelCommandGroup: public Command {
  public:
    ParallelCommandGroup(Command *commands[], size_t numCommands);
    ParallelCommandGroup(Command *command1, Command *command2);
    ParallelCommandGroup(Command *command1, Command *command2, Command *command3);
    void execute();
    bool isFinished();
    void end();
  private:
    Array<Command *, MAX_COMMANDS> commands;
};
