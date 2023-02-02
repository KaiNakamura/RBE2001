#include "Romi32U4.h"
#include <Chassis.h>
#include "Battery.h"

Chassis chassis;

void setup() {
  Serial.begin(9600);
  chassis.init();
}

void loop() {
  Battery::stopIfBatteryIsLow();

  chassis.setMotorEfforts(100, 100);
  delay(2000);
  chassis.setMotorEfforts(0, 0);
  delay(2000);
}
