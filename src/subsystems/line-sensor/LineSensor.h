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
  double lerp(double value, double min, double max);
  static const uint8_t LEFT_0_PIN = A3;
  static const uint8_t LEFT_1_PIN = A4;
  static const uint8_t RIGHT_0_PIN = A1;
  static const uint8_t RIGHT_1_PIN = A2;
  static const int LEFT_BLACK = 570;
  static const int LEFT_WHITE = 290;
  static const int RIGHT_BLACK = 1580;
  static const int RIGHT_WHITE = 1010;
  static const int READ_TIME = 50; // ms
  long lastTime;
  double left0Raw, left1Raw, right0Raw, right1Raw, leftValue, rightValue;
};