#include "Scheduler.h"

Scheduler *Scheduler::instance = 0;

Scheduler::Scheduler() {
}

Scheduler *Scheduler::getInstance() {
  if (!instance) {
    instance = new Scheduler();
  }
  return instance;
}

void Scheduler::setup() {
  reset();
}

void Scheduler::reset() {
  // End all commands
  for (size_t i = 0; i < commands.size(); i++) {
    Command *command = commands.at(i);
    command->end();
    delete command;
  }

  commands.clear();
}

void Scheduler::update() {
  for (size_t i = 0; i < commands.size(); i++) {
    Command *command = commands.at(i);
    if (command->isFinished()) {
      command->end();
      Serial.print("Removing command, ");
      commands.remove(i);
      delete command;
      Serial.print("num commands: ");
      Serial.println(commands.size());
    } else {
      command->execute();
    }
  }
}

void Scheduler::schedule(Command *command) {
  Serial.print("Scheduling command, ");
  commands.push_back(command);
  Serial.print("num commands: ");
  Serial.println(commands.size());
}
