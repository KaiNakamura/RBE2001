#pragma once

#include "subsystems/Subsystem.h"
#include <Servo32u4.h>

class LinearGripper: public Subsystem {
public:
  LinearGripper();
  void setup();
  void update();
  void reset();
  void resetStuckCalculations(long delay);
  void resetStuckCalculations();
  void open();
  void close();
  int getPosition();

private:
  static const uint8_t POTENTIOMETER_PIN = A0;
  static const int SERVO_OPEN = 1000; // us
  static const int SERVO_CLOSE = 2000; // us
  static const int SERVO_STOP = 1490; // us
  static const int OPEN_POSITION = 700; // ticks
  static const int CLOSED_POSITION = 200; // ticks
  static const int IS_AT_POSITION_TOLERANCE = 2; // ticks
  static const int MIN_DISTANCE_COVERED_BEFORE_STUCK = 3; // ticks
  static const int SERVO_ACCELERATION_TIME = 2000; // ms
  static const int DISTANCE_COVERED_TIME_FRAME = 500; // ms
  static const int MAX_NUM_FAILED_MOVEMENTS = 5;
  enum State { OPEN, CLOSED, OPENING, CLOSING };
  State state;
  Servo32U4Pin5 servo;
  long lastTime;
  int lastPosition;
  int distanceCovered;
  int numFailedMovements;
  bool isAtPosition(int position);
  bool isOpen();
  bool isClosed();
  bool isStuck();
};