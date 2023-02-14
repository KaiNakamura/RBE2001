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
  blueMotor.moveToStartingSetpoint();
  delay(2000);
  blueMotor.moveToRoof45DegreeSetpoint();
  delay(2000);
  blueMotor.moveToRoof25DegreeSetpoint();
  delay(2000);
}
