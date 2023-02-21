#pragma once

#include <Chassis.h>
#include "subsystems/Subsystem.h"

class Drivebase: public Subsystem {
public:
  Drivebase();
  void setup();
  void update();
  void reset();

private:
  Chassis chassis;
};