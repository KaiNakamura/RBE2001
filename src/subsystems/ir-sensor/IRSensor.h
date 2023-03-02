#pragma once

#include <IRdecoder.h>
#include "Constants.h"
#include "subsystems/Subsystem.h"

class IRSensor: public Subsystem {
public:
  IRSensor();
  void setup();
  void update();
  void reset();
  int16_t getCode();

private:
};