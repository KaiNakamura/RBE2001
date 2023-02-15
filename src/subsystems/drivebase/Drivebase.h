#pragma once

#include <Arduino.h>
#include "subsystems/Subsystem.h"
#include "Constants.h"

class Drivebase: public Subsystem {
public:
  Drivebase();
  void setup();
  void update();
  void reset();

private:
};