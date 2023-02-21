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
  void setEffortWithoutDB(double effort);
  bool moveTo(double position, Units units);
  bool moveToByTicks(double ticks);
  bool moveToByRotations(double rotations);
  bool moveToByDegrees(double degrees);
  void moveToSetpoint(double setpoint, Units units);
  void moveToStartingSetpoint();
  void moveToRoof25DegreeSetpoint();
  void moveToRoof45DegreeSetpoint();

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
  static const int MOVE_TO_TOLERANCE = 3; // ticks
  static constexpr double MOVE_UP_DB = 163;
  static constexpr double MOVE_DOWN_DB = 151;
  static constexpr double MOVE_TO_K_P = 50;
  static constexpr double STARTING_SETPOINT = 0; // rotations
  static constexpr double ROOF_45_DEGREE_SETPOINT = 12; // rotations
  static constexpr double ROOF_25_DEGREE_SETPOINT = 18; // rotations
};