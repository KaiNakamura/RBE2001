#include "SequentialCommandGroup.h"

SequentialCommandGroup::SequentialCommandGroup(Command *commands[], size_t numCommands) {
  for (size_t i = 0; i < numCommands; i++) {
    this->commands.push_back(commands[i]);
  }
}

SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
}

SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2, Command *command3) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
  this->commands.push_back(command3);
}

SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
  this->commands.push_back(command3);
  this->commands.push_back(command4);
}

SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4, Command *command5) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
  this->commands.push_back(command3);
  this->commands.push_back(command4);
  this->commands.push_back(command5);
}

SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4, Command *command5, Command *command6) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
  this->commands.push_back(command3);
  this->commands.push_back(command4);
  this->commands.push_back(command5);
  this->commands.push_back(command6);
}

SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4, Command *command5, Command *command6, Command *command7) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
  this->commands.push_back(command3);
  this->commands.push_back(command4);
  this->commands.push_back(command5);
  this->commands.push_back(command6);
  this->commands.push_back(command7);
}

SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2, Command *command3, Command *command4, Command *command5, Command *command6, Command *command7, Command *command8) {
  this->commands.push_back(command1);
  this->commands.push_back(command2);
  this->commands.push_back(command3);
  this->commands.push_back(command4);
  this->commands.push_back(command5);
  this->commands.push_back(command6);
  this->commands.push_back(command7);
  this->commands.push_back(command8);
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
      delete command;
    }
  }

  // Group is finished if there are no commands left
  return commands.size() == 0;
}

void SequentialCommandGroup::end() {
  // End all commands that haven't finished yet
  for (size_t i = 0; i < commands.size(); i++) {
    Command *command = commands.at(i);
    command->end();
    commands.remove(i);
    delete command;
  }
}