#include "subsystems/Subsystem.h"
#include <stdint.h>

#pragma once

class Battery: public Subsystem {
  public:
    void update();
  private:
    static const uint16_t MIN_BATTERY_MILLIVOLTS = 6000;
    static bool isBatteryLow();
};
