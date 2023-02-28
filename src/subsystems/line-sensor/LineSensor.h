#pragma once

#include <Arduino.h>
#include "subsystems/Subsystem.h"

class LineSensor: public Subsystem {
public:
  LineSensor();
  void setup();
  void update();
  void reset();
  double getLeftValue();
  double getRightValue();
  double getValue();

private:
  static double lerp(double value, double min, double max);
  static const uint8_t LEFT_PIN = A3;
  static const uint8_t RIGHT_PIN = A1;
  static const int LEFT_WHITE = 370;
  static const int LEFT_BLACK = 941;
  static const int RIGHT_WHITE = 449;
  static const int RIGHT_BLACK = 556;
  static const int MAX_NUM_READS = 10;
  int numReads;
  long lastTime;
  double leftRaw, rightRaw, leftValue, rightValue;
};