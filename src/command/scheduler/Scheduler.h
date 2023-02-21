#pragma once

#include "command/Command.h"
#include "Constants.h"
#include <Array.h>

class Scheduler {
public:
  void setup();
  void update();
  void schedule(Command *command);

private:
  Array<Command *, MAX_COMMANDS> commands;
};