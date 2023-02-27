#pragma once

#include <Arduino.h>
#include "subsystems/Subsystem.h"

class LineSensor: public Subsystem {
public:
  LineSensor();
  void setup();
  void update();
  void reset();
  double getValue();

private:
  static const uint8_t LEFT_PIN = A4;
  static const uint8_t RIGHT_PIN = A3;
  static const uint8_t EMITTER_PIN = 2;
  static const int READ_TIME = 50; // ms
  long lastTime;
  double leftRaw, rightRaw, leftValue, rightValue;
};