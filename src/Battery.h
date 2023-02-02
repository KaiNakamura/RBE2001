#include <stdint.h>

#pragma once

class Battery{
  public:
    static bool isBatteryLow();
    static void stopIfBatteryIsLow();
  private:
    static const uint16_t MIN_BATTERY_MILLIVOLTS = 6000;
};
