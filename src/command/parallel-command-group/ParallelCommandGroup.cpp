#include "ParallelCommandGroup.h"

ParallelCommandGroup::ParallelCommandGroup(Command *commands[], size_t numCommands) {
  for (size_t i = 0; i < numCommands; i++) {
    this->commands.push_back(commands[i]);
  }
}

// TODO: Find a way to do constructors with arbitrarily long commands
ParallelCommandGroup::ParallelCommandGroup(Command *command1, Command *command2) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
}

ParallelCommandGroup::ParallelCommandGroup(Command *command1, Command *command2, Command *command3) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
  this->commands.push_back(command3);
}

void ParallelCommandGroup::execute() {
  for (size_t i = 0; i < commands.size(); i++) {
    commands.at(i)->execute();
  }
}

bool ParallelCommandGroup::isFinished() {
  // For each command that has finished, call end and remove it
  for (size_t i = 0; i < commands.size(); i++) {
    Command *command = commands.at(i);
    if (command->isFinished()) {
      command->end();
      commands.remove(i);
      delete command;
    }
  }

  // Group is finished if there are no commands left
  return commands.size() == 0;
}

void ParallelCommandGroup::end() {
  // End all commands that haven't finished yet
  for (size_t i = 0; i < commands.size(); i++) {
    Command *command = commands.at(i);
    command->end();
    commands.remove(i);
    delete command;
  }
}