#include <Romi32U4.h>
#include "Battery.h"

void Battery::setup() {

}

void Battery::update() {
  if (isBatteryLow()) {
    Serial.println("WARNING: Low battery!");
  }
}

void Battery::reset() {

}

bool Battery::isBatteryLow() {
  return readBatteryMillivolts() < MIN_BATTERY_MILLIVOLTS;
}