#pragma once

#include <Arduino.h>
#include <Servo32u4.h>
#include "subsystems/Subsystem.h"
#include "Constants.h"

class LinearGripper: public Subsystem {
public:
  LinearGripper();
  void setup();
  void update();
  void reset();
  void open();
  void close();
  double getPosition();
  void setEffort(double effort);
  bool moveTo(double target);

private:
  static const int POTENTIOMETER_PIN = A0;
  static constexpr double OPEN_SETPOINT = 700;
  static constexpr double CLOSED_SETPOINT = 200;
  static constexpr double MIN_MOVE_SPEED = 0;
  static constexpr double MOVE_TO_TOLERANCE = 50;
  static constexpr double MOVE_TO_K_P = 50;
  static const int SERVO_DOWN = 1300;
  static const int SERVO_UP = 1700;
  static const int SERVO_STOP = 1490;
  Servo32U4Pin6 linearServo;
};