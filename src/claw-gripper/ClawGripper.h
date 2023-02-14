#pragma once

#include "Constants.h"

class ClawGripper {
public:
  ClawGripper();
  void setup();
  void reset();
  void open();
  void close();

private:
  static const int SERVO_PIN = 5;
  static const int OPEN_SETPOINT = 2000; // ms
  static const int CLOSE_SETPOINT = 1000; // ms
};