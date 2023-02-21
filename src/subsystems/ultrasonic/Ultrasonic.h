#pragma once

#include "subsystems/Subsystem.h"

class Ultrasonic: public Subsystem {
public:
  Ultrasonic();
  void setup();
  void update();
  void reset();
  double getDistance();

private:
  static const int TRIG_PIN = 12;
  static const int ECHO_PIN = 0;
  static constexpr double DURATION_TO_CENTIMETERS = 0.017;
  double distance;
};