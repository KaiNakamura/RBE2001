#include "ParallelRaceCommandGroup.h"

ParallelRaceCommandGroup::ParallelRaceCommandGroup(Command *commands[], size_t numCommands) {
  for (size_t i = 0; i < numCommands; i++) {
    this->commands.push_back(commands[i]);
  }
}

// TODO: Find a way to do constructors with arbitrarily long commands
ParallelRaceCommandGroup::ParallelRaceCommandGroup(Command *command1, Command *command2) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
}

ParallelRaceCommandGroup::ParallelRaceCommandGroup(Command *command1, Command *command2, Command *command3) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
  this->commands.push_back(command3);
}

void ParallelRaceCommandGroup::execute() {
  for (size_t i = 0; i < commands.size(); i++) {
    commands.at(i)->execute();
  }
}

bool ParallelRaceCommandGroup::isFinished() {
  // If any commands have finished, call end and remove it, then race is done
  for (size_t i = 0; i < commands.size(); i++) {
    Command *command = commands.at(i);
    if (command->isFinished()) {
      command->end();
      commands.remove(i);
      delete command;
      return true;
    }
  }

  return false;
}

void ParallelRaceCommandGroup::end() {
  // End all commands that haven't finished yet
  for (size_t i = 0; i < commands.size(); i++) {
    Command *command = commands.at(i);
    command->end();
    commands.remove(i);
    delete command;
  }
}