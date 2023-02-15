#include "ClawGripper.h"

ClawGripper::ClawGripper() {
}

void ClawGripper::setup() {
  servo.attach();
  pinMode(ENCODER_PIN, INPUT);
  reset();
}

void ClawGripper::update() {
  switch (state) {
    case OPENING:
      if (isOpen()) {
        state = OPEN;
      } else if (isStuck()) {
        close();
      } else {
        servo.writeMicroseconds(SERVO_OPEN);
      }
      break;
    case CLOSING:
      if (isClosed()) {
        state = CLOSED;
      } else if (isStuck()) {
        open();
      } else {
        servo.writeMicroseconds(SERVO_CLOSE);
      }
      break;
    default:
      break;
  }
}

void ClawGripper::reset() {
  state = CLOSED;
  lastTimeBeforeMoving = 0;
}

void ClawGripper::open() {
  if (state != OPEN) {
    state = OPENING;
    lastTimeBeforeMoving = millis();
  }
}

void ClawGripper::close() {
  if (state != CLOSED) {
    state = CLOSING;
    lastTimeBeforeMoving = millis();
  }
}

int ClawGripper::getPosition() {
  return analogRead(ENCODER_PIN);
}

bool ClawGripper::isAtPosition(int position) {
  int error = position - getPosition();
  return abs(error) <= IS_AT_POSITION_TOLERANCE;
}

bool ClawGripper::isOpen() {
  return isAtPosition(OPEN_POSITION);
}

bool ClawGripper::isClosed() {
  return isAtPosition(CLOSED_POSITION);
}

bool ClawGripper::isStuck() {
  double timeSpentMoving = millis() - lastTimeBeforeMoving;
  return timeSpentMoving > MAX_STUCK_TIME;
}