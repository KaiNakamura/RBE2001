#include "Battery.h"
#include <Romi32U4.h>

bool Battery::isBatteryLow() {
  return readBatteryMillivolts() < MIN_BATTERY_MILLIVOLTS;
}

void Battery::stopIfBatteryIsLow() {
  if (isBatteryLow()) {
    Serial.println("Stopping because of low battery, press button C to resume.");
    Romi32U4ButtonC buttonC;
    buttonC.waitForButton();
  }
}