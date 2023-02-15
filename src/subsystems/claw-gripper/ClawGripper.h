#pragma once

#include <Arduino.h>
#include <Servo32u4.h>
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
  int getPosition();

private:
  static const int ENCODER_PIN = A0;
  static const int SERVO_OPEN = 2000; // us
  static const int SERVO_CLOSE = 1000; // us
  static const int OPEN_POSITION = 376; // ticks
  static const int CLOSED_POSITION = 195; // ticks
  static const int IS_AT_POSITION_TOLERANCE = 10; // ticks
  static constexpr double MAX_STUCK_TIME = 500; // ms
  enum State { OPEN, CLOSED, OPENING, CLOSING };
  State state;
  Servo32U4Pin5 servo;
  long lastTimeBeforeMoving;
  bool isAtPosition(int position);
  bool isOpen();
  bool isClosed();
  bool isStuck();
};