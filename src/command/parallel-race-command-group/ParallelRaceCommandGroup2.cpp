#include "ParallelRaceCommandGroup2.h"

// TODO: Come up with something cleaner, temp fix to save memory
ParallelRaceCommandGroup2::ParallelRaceCommandGroup2(Command *command1, Command *command2) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
}

void ParallelRaceCommandGroup2::execute() {
  for (size_t i = 0; i < commands.size(); i++) {
    commands.at(i)->execute();
  }
}

bool ParallelRaceCommandGroup2::isFinished() {
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

void ParallelRaceCommandGroup2::end() {
  // End all commands that haven't finished yet
  for (size_t i = 0; i < commands.size(); i++) {
    Command *command = commands.at(i);
    command->end();
    commands.remove(i);
    delete command;
  }
}