#pragma once

#include "subsystems/Subsystem.h"
#include "subsystems/battery/Battery.h"
#include "subsystems/drivebase/Drivebase.h"
#include "subsystems/blue-motor/BlueMotor.h"
#include "subsystems/claw-gripper/ClawGripper.h"
#include "subsystems/linear-gripper/LinearGripper.h"
#include "subsystems/ultrasonic/Ultrasonic.h"
#include "subsystems/line-sensor/LineSensor.h"
#include <Array.h>

class Robot: public Subsystem {
protected:
  Robot();
  static Robot *instance;

public:
  static Robot *getInstance();
  void setup();
  void update();
  void reset();
  void stop();
  Battery *getBattery();
  Drivebase *getDrivebase();
  BlueMotor *getBlueMotor();
  ClawGripper *getClawGripper();
  LinearGripper *getLinearGripper();
  Ultrasonic *getUltrasonic();
  LineSensor *getLineSensor();

private:
  static const int NUM_SUBSYSTEMS = 7;
  Array<Subsystem *, NUM_SUBSYSTEMS> subsystems;
  Battery battery;
  Drivebase drivebase;
  BlueMotor blueMotor;
  ClawGripper clawGripper;
  LinearGripper linearGripper;
  Ultrasonic ultrasonic;
  LineSensor lineSensor;
};