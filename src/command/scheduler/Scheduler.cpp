#include "Scheduler.h"

Scheduler *Scheduler::instance = 0;

Scheduler::Scheduler() {
  this->commands = new Array<Command *, MAX_COMMANDS>;
}

Scheduler *Scheduler::getInstance() {
  if (!instance) {
    instance = new Scheduler();
  }
  return instance;
}

void Scheduler::setup() {
  commands->clear();
}

void Scheduler::update() {
  for (size_t i = 0; i < commands->size(); i++) {
    Command *command = commands->at(i);
    if (command->isFinished()) {
      command->end();
      Serial.print("Removing command, ");
      commands->remove(i);
      Serial.print("Num commands-> ");
      Serial.println(commands->size());
    } else {
      command->execute();
    }
  }
}

void Scheduler::reset() {
  // End all commands
  for (size_t i = 0; i < commands->size(); i++) {
    commands->at(i)->end();
  }

  setup();
}

void Scheduler::schedule(Command *command) {
  Serial.print("Scheduling new command, ");
  Serial.print("Num commands->before: ");
  Serial.print(commands->size());
  commands->push_back(command);
  Serial.print(", Num commands->after: ");
  // Serial.print("Num commands-> ");
  Serial.println(commands->size());
}
