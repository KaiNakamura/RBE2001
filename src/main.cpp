#include <Romi32U4.h>
#include <Chassis.h>
#include "battery/Battery.h"
#include "blue-motor/BlueMotor.h"
#include "Constants.h"

Chassis chassis;
BlueMotor blueMotor;

void setup() {
  Serial.begin(9600);
  chassis.init();
  blueMotor.setup();
}

void loop() {
  while (!blueMotor.moveToByRotations(1));
  Serial.println("Reached 1 rotations");
  delay(1000);
  while (!blueMotor.moveToByRotations(0));
  Serial.println("Reached 0 rotations");
  delay(1000);
}
