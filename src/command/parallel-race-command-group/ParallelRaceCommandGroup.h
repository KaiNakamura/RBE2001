#pragma once

#include "command/Command.h"
#include "Constants.h"
#include <Array.h>

class ParallelRaceCommandGroup: public Command {
  public:
    ParallelRaceCommandGroup(Command *commands[], size_t numCommands);
    ParallelRaceCommandGroup(Command *command1, Command *command2);
    ParallelRaceCommandGroup(Command *command1, Command *command2, Command *command3);
    void execute();
    bool isFinished();
    void end();
  private:
    Array<Command *, MAX_COMMANDS> commands;
};
