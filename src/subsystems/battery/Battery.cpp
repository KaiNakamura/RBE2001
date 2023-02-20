#include <Romi32U4.h>
#include "Battery.h"

void Battery::setup() {

}

void Battery::update() {
  if (isBatteryLow()) {
    Serial.println("Stopping because of low battery, press button C to resume.");
    Romi32U4ButtonC buttonC;
    buttonC.waitForButton();
  }
}

void Battery::reset() {

}

bool Battery::isBatteryLow() {
  return readBatteryMillivolts() < MIN_BATTERY_MILLIVOLTS;
}