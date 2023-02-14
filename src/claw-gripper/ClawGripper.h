#pragma once

#include "Constants.h"

class ClawGripper {
public:
  ClawGripper();
  void setup();
  void reset();

private:
  static const int SERVO_PIN = 5;
};