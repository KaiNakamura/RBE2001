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
  commands.clear();
}

void Scheduler::update() {
  for (size_t i = 0; i < commands.size(); i++) {
    Command *command = commands.at(i);
    if (command->isFinished()) {
      command->end();
      commands.remove(i);
    } else {
      command->execute();
    }
  }
}

void Scheduler::schedule(Command *command) {
  commands.push_back(command);
}
