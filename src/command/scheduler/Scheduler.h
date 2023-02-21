#pragma once

#include "command/Command.h"
#include <Array.h>

class Scheduler {
public:
  void setup();
  void update();
  void schedule(Command *command);

private:
  static const unsigned int MAX_COMMANDS = 256;
  Array<Command *, MAX_COMMANDS> commands;
};