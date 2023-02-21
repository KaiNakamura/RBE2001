#include <Romi32U4.h>
#include "command/scheduler/Scheduler.h"
#include "command/wait-command/WaitCommand.h"
#include "subsystems/battery/Battery.h"
#include "subsystems/drivebase/Drivebase.h"
#include "subsystems/blue-motor/BlueMotor.h"
#include "subsystems/claw-gripper/ClawGripper.h"
#include "subsystems/linear-gripper/LinearGripper.h"
#include "Constants.h"
#include <servo32u4.h>

Scheduler scheduler;
Battery battery;
Drivebase drivebase;
BlueMotor blueMotor;
ClawGripper clawGripper;
LinearGripper linearGripper;

Romi32U4ButtonA buttonA;
Romi32U4ButtonB buttonB;
Romi32U4ButtonC buttonC;

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
  scheduler.setup();
  scheduler.schedule(new WaitCommand(5000));

  battery.setup();
  drivebase.setup();
  clawGripper.setup();
  blueMotor.setup();
  linearGripper.setup();
}

void loop() {
  scheduler.update();
  // battery.update();
  drivebase.update();
  clawGripper.update();
  blueMotor.update();
  linearGripper.update();
}
