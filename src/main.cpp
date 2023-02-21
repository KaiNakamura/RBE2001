#include <Romi32U4.h>
#include "command/scheduler/Scheduler.h"
#include "command/wait-command/WaitCommand.h"
#include "command/parallel-command-group/ParallelCommandGroup.h"
#include "command/sequential-command-group/SequentialCommandGroup.h"
#include "subsystems/battery/Battery.h"
#include "subsystems/drivebase/Drivebase.h"
#include "subsystems/blue-motor/BlueMotor.h"
#include "subsystems/claw-gripper/ClawGripper.h"
#include "subsystems/linear-gripper/LinearGripper.h"
#include "subsystems/ultrasonic/Ultrasonic.h"
#include "Constants.h"
#include <Servo32u4.h>

Scheduler scheduler;
Battery battery;
Drivebase drivebase;
BlueMotor blueMotor;
ClawGripper clawGripper;
LinearGripper linearGripper;
Ultrasonic ultrasonic;

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
  battery.setup();
  drivebase.setup();
  clawGripper.setup();
  blueMotor.setup();
  linearGripper.setup();
  ultrasonic.setup();
}

void loop() {
  scheduler.update();
  battery.update();
  drivebase.update();
  clawGripper.update();
  blueMotor.update();
  linearGripper.update();
  ultrasonic.update();
  Serial.println(ultrasonic.getDistance());
}
