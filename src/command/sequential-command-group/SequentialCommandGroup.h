#pragma once

#include "command/Command.h"
#include "Constants.h"
#include <Array.h>

class SequentialCommandGroup: public Command {
  public:
    // TODO: Find a way to do constructors with arbitrarily long commands
    SequentialCommandGroup(Command *commands[], size_t numCommands);
    SequentialCommandGroup(Command *command1, Command *command2);
    SequentialCommandGroup(Command *command1, Command *command2, Command *command3);
    SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4);
    SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4, Command *command5);
    SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4, Command *command5, Command *command6);
    SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4, Command *command5, Command *command6, Command *command7);
    SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4, Command *command5, Command *command6, Command *command7, Command *command8);
    void execute();
    bool isFinished();
    void end();
  private:
    Array<Command *, MAX_COMMANDS> commands;
};
