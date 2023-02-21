#pragma once

#include <IRdecoder.h>
#include "subsystems/Subsystem.h"

class IRSensor: public Subsystem {
public:
  IRSensor();
  void setup();
  void update();
  void reset();

private:
  static const int PIN = 3;
  IRDecoder irSensor = IRDecoder(PIN);
};