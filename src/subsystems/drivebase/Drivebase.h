#pragma once

#include <Chassis.h>
#include "subsystems/Subsystem.h"
#include "Constants.h"

class Drivebase: public Subsystem {
public:
  Drivebase();
  void setup();
  void update();
  void reset();

private:
  Chassis chassis;
};