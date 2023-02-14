#include <Romi32U4.h>
#include <Chassis.h>
#include "battery/Battery.h"
#include "blue-motor/BlueMotor.h"
#include "claw-gripper/ClawGripper.h"
#include "Constants.h"
#include <servo32u4.h>

Chassis chassis;
BlueMotor blueMotor;
ClawGripper clawGripper;

void setup() {
  Serial.begin(9600);
  chassis.init();
  clawGripper.setup();
  blueMotor.setup();
}

void loop() {

}
