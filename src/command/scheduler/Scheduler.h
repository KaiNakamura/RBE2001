#pragma once

#include "command/Command.h"
#include "Constants.h"
#include <Array.h>

class Scheduler {
protected:
  Scheduler();
  static Scheduler *instance;

public:
  static Scheduler *getInstance();
  void setup();
  void update();
  void reset();
  void schedule(Command *command);

private:
  Array<Command *, MAX_COMMANDS> *commands;
};