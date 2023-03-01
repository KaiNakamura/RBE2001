#include "SequentialCommandGroup.h"

SequentialCommandGroup::SequentialCommandGroup(Command *commands[], size_t numCommands) {
  Serial.println("1 Constructor Start");
  this->commands = new Array<Command *, MAX_COMMANDS>;
  for (size_t i = 0; i < numCommands; i++) {
    this->commands->push_back(commands[i]);
  }
  Serial.println("Constructor End");
}

// TODO: Find a way to do constructors with arbitrarily long commands
SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2) {
  Serial.println("2 Constructor Start");
  commands = new Array<Command *, MAX_COMMANDS>;
  commands->push_back(command1);
  commands->push_back(command2);
  Serial.println("Constructor End");
}

SequentialCommandGroup::SequentialCommandGroup(Command *command1, Command *command2, Command *command3) {
  Serial.println("3 Constructor Start");
  commands = new Array<Command *, MAX_COMMANDS>;
  commands->push_back(command1);
  commands->push_back(command2);
  commands->push_back(command3);
  Serial.println("Constructor End");
}

void SequentialCommandGroup::execute() {
  commands->at(0)->execute();
}

bool SequentialCommandGroup::isFinished() {
  // If there is at least one command, check if it is finished
  if (commands->size() > 0) {
    Command *command = commands->at(0);
    if (command->isFinished()) {
      command->end();
      commands->remove(0);
    }
  }

  // Group is finished if there are no commands->left
  return commands->size() == 0;
}

void SequentialCommandGroup::end() {
  for (size_t i = 0; i < commands->size(); i++) {
    commands->at(i)->end();
  }
  commands->clear();
}