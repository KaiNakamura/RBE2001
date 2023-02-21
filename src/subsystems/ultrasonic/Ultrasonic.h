#pragma once

#include "subsystems/Subsystem.h"

class Ultrasonic: public Subsystem {
public:
  Ultrasonic();
  void setup();
  void update();
  void reset();
  float findDistance();
  

private:
  static const int TRIG_PIN = 12;
  static const int ECHO_PIN = 0;
};