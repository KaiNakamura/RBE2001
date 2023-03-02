#pragma once

#include <Chassis.h>
#include "subsystems/Subsystem.h"

class Drivebase: public Subsystem {
public:
  Drivebase();
  void setup();
  void update();
  void reset();
  void setMotors(double left, double right);
  void stop();
  double getLeftPosition();
  double getRightPosition();
  double getLeftRotations();
  double getRightRotations();
  static constexpr double WHEEL_DIAMETER = 7.2; // cm
  static constexpr double TICKS_PER_REVOLUTION = 1440; // ticks
  static constexpr double WHEEL_TRACK = 14.7; // cm
  static constexpr double CM_PER_TICK = WHEEL_DIAMETER * M_PI / TICKS_PER_REVOLUTION;

private:
};