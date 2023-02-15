#include <Romi32U4.h>
#include "subsystems/battery/Battery.h"
#include "subsystems/drivebase/Drivebase.h"
#include "subsystems/blue-motor/BlueMotor.h"
#include "subsystems/claw-gripper/ClawGripper.h"
#include "subsystems/linear-gripper/LinearGripper.h"
#include "Constants.h"
#include <servo32u4.h>

Drivebase drivebase;
BlueMotor blueMotor;
ClawGripper clawGripper;
LinearGripper linearGripper;

void placeOnRoof25Degrees() {
  blueMotor.moveToStartingSetpoint();
  delay(1000);
  clawGripper.open();
  delay(1000);
  clawGripper.close();
  delay(1000);
  blueMotor.moveToRoof25DegreeSetpoint();
  delay(1000);
  clawGripper.open();
  delay(1000);
  blueMotor.moveToStartingSetpoint();
  delay(1000);
}

void removeFrom25Degrees() {
  blueMotor.moveToStartingSetpoint();
  delay(1000);
  clawGripper.open();
  delay(1000);
  blueMotor.moveToRoof25DegreeSetpoint();
  delay(1000);
  clawGripper.close();
  delay(1000);
  blueMotor.moveToStartingSetpoint();
  delay(1000);
}

void placeOnRoof45Degrees() {
  blueMotor.moveToStartingSetpoint();
  delay(1000);
  clawGripper.open();
  delay(1000);
  clawGripper.close();
  delay(1000);
  blueMotor.moveToRoof45DegreeSetpoint();
  delay(1000);
  clawGripper.open();
  delay(1000);
  blueMotor.moveToStartingSetpoint();
  delay(1000);
}

void removeFrom45Degrees() {
  blueMotor.moveToStartingSetpoint();
  delay(1000);
  clawGripper.open();
  delay(1000);
  blueMotor.moveToRoof45DegreeSetpoint();
  delay(1000);
  clawGripper.close();
  delay(1000);
  blueMotor.moveToStartingSetpoint();
  delay(1000);
}

void setup() {
  Serial.begin(9600);
  drivebase.setup();
  clawGripper.setup();
  blueMotor.setup();
  linearGripper.setup();

  // placeOnRoof25Degrees();
  // removeFrom25Degrees();
  // placeOnRoof45Degrees();
  // removeFrom45Degrees();
}

void loop() {
  drivebase.update();
  clawGripper.update();
  blueMotor.update();
  linearGripper.update();
}
