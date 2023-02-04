#pragma once

#include "Constants.h"

class BlueMotor {
public:
  BlueMotor();
  void setup();
  void reset();
  double getTicks();
  double getRotations();
  double getDegrees();
  double getPosition(Units units);
  void setEffort(double effort);
  bool moveTo(double position, Units units);
  bool moveToByTicks(double ticks);
  bool moveToByRotations(double rotations);
  bool moveToByDegrees(double degrees);

private:
  void setEffort(double effort, bool clockwise);
  static void isrA();
  static void isrB();
  static double toTicks(double position, Units units);
  static const int PWM_OUT_PIN = 11;
  static const int AIN2_PIN = 4;
  static const int AIN1_PIN = 13;
  static const int ENCA_PIN = 0;
  static const int ENCB_PIN = 1;
  static const int ENCODER_RESOLUTION = 540;
  static constexpr double MOVE_TO_K_P = 6;
  static const int MOVE_TO_TOLERANCE = 3; // ticks
};