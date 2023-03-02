#pragma once

#include <Arduino.h>
#include "subsystems/Subsystem.h"

class Ultrasonic: public Subsystem {
public:
  Ultrasonic();
  void setup();
  void update();
  void reset();
  double getDistance();

private:
  static const uint8_t TRIG_PIN = 12;
  static const uint8_t ECHO_PIN = 2;
};