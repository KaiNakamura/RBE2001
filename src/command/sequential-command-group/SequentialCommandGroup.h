#pragma once

#include "command/Command.h"
#include "Constants.h"
#include <Array.h>

class SequentialCommandGroup: public Command {
  public:
    SequentialCommandGroup(Command *commands[], size_t numCommands);
    SequentialCommandGroup(Command *command1, Command *command2);
    SequentialCommandGroup(Command *command1, Command *command2, Command *command3);
    void execute();
    bool isFinished();
    void end();
  private:
    Array<Command *, MAX_COMMANDS> commands;
};
