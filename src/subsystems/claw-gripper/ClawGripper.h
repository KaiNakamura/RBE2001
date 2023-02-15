#pragma once

#include <Arduino.h>
#include "subsystems/Subsystem.h"
#include "Constants.h"

class ClawGripper: public Subsystem {
public:
  ClawGripper();
  void setup();
  void update();
  void reset();
  void open();
  void close();
  double getPosition();

private:
  static const int SERVO_PIN = 5;
  static const int ENCODER_PIN = A0;
  static const int OPEN_SETPOINT = 2000; // ms
  static const int CLOSE_SETPOINT = 1000; // ms
  enum State { OPEN, CLOSED, OPENING, CLOSING };
};