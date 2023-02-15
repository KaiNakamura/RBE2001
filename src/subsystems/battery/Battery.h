#pragma once

#include "subsystems/Subsystem.h"
#include <stdint.h>

class Battery: public Subsystem {
  public:
    void setup();
    void update();
    void reset();
  private:
    static const uint16_t MIN_BATTERY_MILLIVOLTS = 6000;
    static bool isBatteryLow();
};
