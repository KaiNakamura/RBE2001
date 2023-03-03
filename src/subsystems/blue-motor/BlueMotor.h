#pragma once

#include "subsystems/Subsystem.h"
#include "Constants.h"

class BlueMotor: public Subsystem {
public:
  BlueMotor();
  void setup();
  void update();
  void reset();
  double getTicks();
  double getRotations();
  double getDegrees();
  double getPosition(Units units);
  void setEffort(double effort);
  bool isAtPosition(double position, Units units);
  static constexpr double STARTING_SETPOINT = 0; // rotations
  static constexpr double STAGING_PLATFORM = 3; // rotations
  static constexpr double ROOF_45_DEGREE_SETPOINT = 12.5; // rotations
  static constexpr double PICKUP_ROOF_25_DEGREE_SETPOINT = 12.5; // rotations
  static constexpr double ABOVE_ROOF_25_DEGREE_SETPOINT = 16.5; // rotations
  static constexpr double PLACE_ROOF_25_DEGREE_SETPOINT = 18; // rotations
  static constexpr double MAX_HEIGHT = 19.5; // rotations

private:
  void setEffort(double effort, bool clockwise);
  static void isrA();
  static void isrB();
  static double toTicks(double position, Units units);
  static const uint8_t PWM_OUT_PIN = 11;
  static const uint8_t AIN2_PIN = 4;
  static const uint8_t AIN1_PIN = 13;
  static const uint8_t ENCA_PIN = 0;
  static const uint8_t ENCB_PIN = 1;
  static const int ENCODER_RESOLUTION = 540;
  static const int IS_AT_TARGET_TOLERANCE = 3; // ticks
};