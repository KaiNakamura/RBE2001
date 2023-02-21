#include "SequentialCommandGroup.h"

SequentialCommandGroup::SequentialCommandGroup(Command *commands[], size_t numCommands) {
  for (size_t i = 0; i < numCommands; i++) {
    this->commands.push_back(commands[i]);
  }
}

// TODO: Find a way to do constructors with arbitrarily long commands
SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
}

SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2, Command *command3) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
  this->commands.push_back(command3);
}

void SequentialCommandGroup::execute() {
  commands.at(0)->execute();
}

bool SequentialCommandGroup::isFinished() {
  // If there is at least one command, check if it is finished
  if (commands.size() > 0) {
    Command *command = commands.at(0);
    if (command->isFinished()) {
      command->end();
      commands.remove(0);
    }
  }

  // Group is finished if there are no commands left
  return commands.size() == 0;
}

void SequentialCommandGroup::end() {

}